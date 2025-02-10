#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define BTN_A 5
#define BTN_B 6

typedef void (*button_callback_t)(uint gpio, uint32_t events);

void init_buttons(button_callback_t button_a_cb, button_callback_t button_b_cb);

#endif // BUTTONS_H