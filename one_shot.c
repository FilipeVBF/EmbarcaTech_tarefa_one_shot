#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

// Define os pinos GPIO para os LEDs azul, vermelho e verde.
const uint LED_PIN_BLUE = 11;
const uint LED_PIN_RED = 12;
const uint LED_PIN_GREEN = 13;
const uint BUTTON_PIN = 5;  // Define o pino GPIO 5 para ler o estado do botão.

bool led_on = false;        // Variável global para armazenar o estado do LED (não utilizada neste código).
bool led_active = false;    // Indica se o LED está atualmente aceso (para evitar múltiplas ativações).
absolute_time_t turn_off_time;  // Variável para armazenar o tempo em que o LED deve ser desligado (não utilizada neste código).

// Função para inicializar o pino do LED
void init_gpio_led(int led_pin, bool is_output, bool state) {
    gpio_init(led_pin);                                         // Inicializa o pino do LED
    gpio_set_dir(led_pin, is_output ? GPIO_OUT : GPIO_IN);      // Configura o pino como saída ou entrada
    gpio_put(led_pin, state);                                   // Garante que o LED inicie apagado
}
// Função de callback para desligar o LED após o tempo programado.
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {

    gpio_put(LED_PIN_GREEN, false);

    // Atualiza o estado de 'led_active' para falso, indicando que o LED está desligado.
    led_active = false;

    return 0;
}

int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {

    gpio_put(LED_PIN_RED, false);

    add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);

    return 0;
}

int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {

    // Desliga o LED configurando o pino LED_PIN para nível baixo.
    gpio_put(LED_PIN_BLUE, false);

    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);

    // Retorna 0 para indicar que o alarme não deve se repetir.
    return 0;
}

int main() {
    stdio_init_all();

    // Inicializando pino do LED RGB
    init_gpio_led(LED_PIN_BLUE, true, false);
    init_gpio_led(LED_PIN_RED, true, false);
    init_gpio_led(LED_PIN_GREEN, true, false);

    // Configura o pino BUTTON_PIN (5) como entrada digital.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Habilita o resistor pull-up interno para o pino do botão.
    gpio_pull_up(BUTTON_PIN);

    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true) {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                // Acende o LED configurando o pino LED_PIN para nível alto.
                gpio_put(LED_PIN_BLUE, true);
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_GREEN, true);

                // Define 'led_active' como true para indicar que o LED está aceso.
                led_active = true;

                // Agenda um alarme para desligar o LED após 3 segundos (3000 ms).
                add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);
            }
        }

        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
        sleep_ms(10);
    }

    // Retorno de 0, que nunca será alcançado devido ao loop infinito.
    return 0;
}
