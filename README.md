# Temporizador de um disparo (One Shot)

## Descrição do Projeto

Este projeto implementa um temporizador para controle de LEDs em um microcontrolador Raspberry Pi Pico W utilizando a função add_alarm_in_ms() da biblioteca Pico SDK. O sistema aciona três LEDs (azul, vermelho e verde) com base no clique de um botão (pushbutton) e altera seu estado após intervalos de 3 segundos, simulando um temporizador de um disparo (One Shot).

## Funcionalidades

- Quando o botão é pressionado, três LEDs (azul, vermelho e verde) são acionados simultaneamente.
- O sistema altera o estado dos LEDs de acordo com um temporizador de 3 segundos:
  - Primeiro, os três LEDs permanecem acesos.
  - Após 3 segundos, dois LEDs são desligados, deixando apenas um aceso.
  - Após mais 3 segundos, o último LED é desligado.
- Durante a execução dos timers, o botão não pode reiniciar o ciclo até que o último LED seja desligado, evitando múltiplas ativações.
- Implementação de debounce de software para garantir a estabilidade da leitura do botão e evitar acionamentos errôneos.

## Componentes Utilizados

- Microcontrolador Raspberry Pi Pico W
- 03 LEDs (Azul, Vermelho e Verde)
- 03 Resistores
- Botão (Pushbutton)
- Software de simulação Wokwi
- Pico SDK

## Requisitos

- **Pico SDK:** Pico SDK instalado e devidamente configurado para desenvolvimento no Raspberry Pi Pico W.
- **Ambiente de Desenvolvimento:** É necessário ter o CMake e o Ninja instalados para compilar e carregar o código na placa do Raspberry Pi Pico W.
- **Wokwi:** Simulador para realizar testes do circuito e do funcionamento do código.

## Instrução de Uso

1. Clone o repositório do projeto:
https://github.com/FilipeVBF/EmbarcaTech_tarefa_one_shot.git
2. Importe a pasta do projeto para o ambiente de desenvolvimento do Pico SDK.
3. Carregue o programa no Raspberry Pi Pico W
4. Compile o código
5. Para execução na simulação do Wokwi, abra o arquivo diagram.json e inicie a simulação
6. Conecte o hardware conforme a configuração sugerida.
7. Observe o ciclo de transição dos LEDs: Ao clicar no botão, os três LEDs (azul, vermelho e verde) são acesos simultaneamente. A cada 3 segundos, um LED é desligado, seguindo a sequência: azul -> vermelho -> verde.
