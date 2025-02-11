#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"
#include "inc/ssd1306.h"
#include "inc/ws2812b.h"
#include "inc/buttons.h"
#include "ws2812.pio.h"

#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define OUT_PIN 7

#define SDA_PIN 14
#define SCL_PIN 15

// Global variables
ssd1306_t disp;
bool led_green_state = false;
bool led_blue_state = false;

// Variáveis de debounce
#define DEBOUNCE_DELAY_MS 50
absolute_time_t last_button_a_time = 0;
absolute_time_t last_button_b_time = 0;

// Inicializa o I2C e o display OLED
void init_display() {
    i2c_init(i2c1, 400000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    ssd1306_init(&disp, 128, 64, false, 0x3C, i2c1);
    ssd1306_config(&disp);
    ssd1306_fill(&disp, false);
    ssd1306_draw_string(&disp, "Pronto", 0, 0);
    ssd1306_send_data(&disp);
}

// Inicializa o LED RGB
void init_rgb_led() {
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    // Desliga todos os LEDs
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
}

// Callback do BTN_A
void button_a_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_button_a_time, now) >= DEBOUNCE_DELAY_MS * 1000) {
        led_green_state = !led_green_state;
        gpio_put(LED_GREEN, led_green_state);

        // Atualiza display
        ssd1306_fill(&disp, false);
        ssd1306_draw_string(&disp, led_green_state ? "LED Verde: ON" : "LED Verde: OFF", 0, 0);
        ssd1306_send_data(&disp);
        
        // Envia ao serial monitor
        printf("Green LED toggled: %s\n", led_green_state ? "ON" : "OFF");

        last_button_a_time = now;
    }
}

// Callback do BTN_B
void button_b_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_button_b_time, now) >= DEBOUNCE_DELAY_MS * 1000) {
        led_blue_state = !led_blue_state;
        gpio_put(LED_BLUE, led_blue_state);
        
        // Atualiza display
        ssd1306_fill(&disp, false);
        ssd1306_draw_string(&disp, led_blue_state ? "LED Azul: ON" : "LED Azul: OFF", 0, 0);
        ssd1306_send_data(&disp);
        
        // Envia ao serial monitor
        printf("Blue LED toggled: %s\n", led_blue_state ? "ON" : "OFF");
        
        last_button_b_time = now;
    }
}

// Função para ler uma string do terminal serial
void read_input(char *buffer, int buffer_size) {
    int index = 0;
    while (index < buffer_size - 1) {
        int c = getchar_timeout_us(0);
        if (c != PICO_ERROR_TIMEOUT) {
            if (c == '\n' || c == '\r') { // Finaliza a leitura ao pressionar Enter
                buffer[index] = '\0';
                return;
            }
            buffer[index++] = c;
        }
        sleep_ms(10); // Pequeno delay para evitar uso excessivo da CPU
    }
    buffer[buffer_size - 1] = '\0'; // Garante que a string seja terminada corretamente
}

int main() {
    // Inidcializa o clock de sistema
    set_sys_clock_khz(128000, true);
    
    // Inicializa stdio
    stdio_init_all();
    printf("Inicializando...\n");
    
    // Inicializa o display
    init_display();
    printf("Display Inicializado.\n");
    
    // Inicializa o LED RGB
    init_rgb_led();
    printf("LEDs RGB inicializados!\n");
    
    // Inicializa o PIO para WS2812B
    PIO pio = pio0; // Usa o PIO 0
    uint offset = pio_add_program(pio, &ws2812_program); // Adiciona o programa PIO
    uint sm = pio_claim_unused_sm(pio, true); // Usa uma state machine livre
    ws2812_program_init(pio, sm, offset, OUT_PIN, 800000, false); // Inicializa a state machine
    
    // Inicializa os botões
    init_buttons(button_a_callback, button_b_callback);

    // Buffer para entrada do usuário
    char input_buffer[32];
    
    // Loop principal
    while(1) {
        if (stdio_usb_connected()) {
            int c = getchar_timeout_us(0);
            if (c != PICO_ERROR_TIMEOUT) {
                // Mostra caractere no OLED
                ssd1306_fill(&disp, false);
                char str[2] = {c, '\0'};
                ssd1306_draw_string(&disp, str, 0, 0);
                ssd1306_send_data(&disp);
                
                // Se for um número, mostra na matriz de LEDs
                if (c >= '0' && c <= '9') {
                    int num = c - '0';
                    ws2812b_draw(pio, sm, num);
                }
            }
        }
        
        sleep_ms(10); // Delay
    }
}