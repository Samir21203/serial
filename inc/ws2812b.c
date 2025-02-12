#include "ws2812b.h"

int mapeamento[25] = {
    24, 23, 22, 21, 20,  
    15, 16, 17, 18, 19,  
    14, 13, 12, 11, 10,  
     5,  6,  7,  8,  9,  
     4,  3,  2,  1,  0  
};

//Numero 0
double NUM_0[25] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0,
};

//Numero 1
double NUM_1[25] = {
    0, 0, 1, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 1, 1, 1, 0
};

//Numero 2
double NUM_2[25] = {
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0
};

//Numero 3
double NUM_3[25] = {
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0
};

//Numero 4
double NUM_4[25] = {
    0, 1, 0, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 0, 1, 0
};

//Numero 5
double NUM_5[25] = {
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0 
};

//Numero 6
double NUM_6[25] = {
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0
};

//Numero 7
double NUM_7[25] = {
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 0, 0,
    0, 1, 0, 0, 0
};

//Numero 8
double NUM_8[25] = {
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0
};

//Numero 9
double NUM_9[25] = {
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0
};

volatile int current_index = 0; 

double *NUMBERS[] = {NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9};

// void ws2812b_init(PIO pio, uint sm) {
//     uint offset = pio_add_program(pio, &ws2812_program); // Adiciona o programa PIO
//     ws2812_program_init(pio, sm, offset, OUT_PIN, 800000, false); // Inicializa a state machine
// }

uint32_t matrix_rgb(double g, double r, double b) {
    unsigned char R = (unsigned char)(r * 255);
    unsigned char G = (unsigned char)(g * 255);
    unsigned char B = (unsigned char)(b * 255);
    return (G << 24) | (R << 16) | (B << 8);
}

void ws2812b_draw(PIO pio, uint sm, int num) {
    current_index = num;
    printf("Numero: %d\n", current_index);
    double *desenho = NUMBERS[current_index];
    
    uint32_t buffer[NUM_PIXELS] = {0};

    // Para cada pixel lógico (de 0 a NUM_PIXELS-1)
    // atribuímos a cor (vermelho com BRIGHTNESS) ao LED na posição física dada por mapeamento[i].
    for (int i = 0; i < NUM_PIXELS; i++) {
        int pos_fisica = mapeamento[i];  // posição física do LED correspondente
        // Se desenho[i] for 1, queremos acender o LED em vermelho (canal vermelho não-zero)
        // Note que usamos o índice lógico 'i' para acessar o padrão
        if (desenho[i] == 1) {
            buffer[pos_fisica] = matrix_rgb(0.0, 1.0 * BRIGHTNESS, 0.0);
        } else {
            buffer[pos_fisica] = 0;
        }
    }

    // Envia os dados para os LEDs na ordem física (do índice 0 até NUM_PIXELS-1)
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}


// void ws2812b_display_number(int num) {
//     if (num < 0 || num > 9) return; // Evita números inválidos
//     double *desenho = NUMBERS[num]; 

//     for (int i = 0; i < 25; i++) {
//         int idx_real = mapeamento[i];
//         uint32_t cor = matrix_rgb(0.0, 0.0, desenho[idx_real] * BRIGHTNESS_FACTOR);
//         pio_sm_put_blocking(pio0, 0, cor);
//     }
// }
