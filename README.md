# Projeto: Controle de LEDs e Display com Raspberry Pi Pico <https://youtube.com/shorts/P9nojlRcTdI?si=13s5Y8KpzW38lmeU>

## Descrição
Este projeto utiliza um Raspberry Pi Pico para controlar LEDs RGB, uma matriz de LEDs WS2812 e um display OLED SSD1306. Ele também recebe entradas via UART e botões físicos para interagir com os componentes.

## Funcionalidades
- Exibição de caracteres recebidos via UART no display SSD1306
- Controle de LEDs RGB através dos botões A e B
- Exibição de números na matriz de LEDs WS2812
- Saída de informações no Serial Monitor

## Hardware Utilizado
- Raspberry Pi Pico
- Display OLED SSD1306 (I2C)
- Matriz de LEDs WS2812 (Neopixel)
- LEDs RGB individuais (Vermelho, Verde e Azul)
- Botões físicos (A e B)
- Interface UART para comunicação

## Bibliotecas Utilizadas
- `pico/stdlib.h` (Funções padrão do Raspberry Pi Pico)
- `hardware/i2c.h` (Comunicação I2C)
- `hardware/irq.h` (Interrupções)
- `hardware/uart.h` (Comunicação UART)
- `hardware/gpio.h` (Manipulação de GPIO)
- `ws2812.h` (Controle dos LEDs WS2812)
- `ssd1306.h` (Controle do display OLED)

## Configuração dos Pinos
| Componente    | Pino no Pico |
|--------------|-------------|
| LED RGB Vermelho | 11 |
| LED RGB Verde    | 12 |
| LED RGB Azul     | 13 |
| Botão A         | 5  |
| Botão B         | 6  |
| WS2812 (Neopixel) | 7  |
| I2C SDA (SSD1306) | 14 |
| I2C SCL (SSD1306) | 15 |
| UART TX          | 0  |
| UART RX          | 1  |

## Como Compilar e Executar
1. Instale o **Pico SDK** e configure o ambiente de desenvolvimento.
2. Clone o repositório e entre no diretório do projeto:
   ```sh
   git clone https://github.com/Samir21203/serial.git
   cd serial
   ```
3. Importe o projeto pelo plugin do Pico SDK
4. Faça a compilação
5. Envie o arquivo `.uf2` gerado para o Raspberry Pi Pico.

## Uso
- Enviar caracteres via UART exibe-os no display OLED.
- Pressionar o **botão A** alterna o estado do LED Verde.
- Pressionar o **botão B** alterna o estado do LED Azul.
- Enviar números de `0` a `9` via UART exibe os números na matriz WS2812 (**Em revisão**).

