#ifndef WS2812B_H
#define WS2812B_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

#define OUT_PIN 7
#define NUM_PIXELS 25

extern int mapeamento[25];
extern double *NUMBERS[10];

// void ws2812b_init(PIO pio, uint sm);
void ws2812b_draw(PIO pio, uint sm, int num);

#endif // WS2812B_H