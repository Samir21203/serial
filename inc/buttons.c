#include "buttons.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

static button_callback_t btn_a_callback = NULL;
static button_callback_t btn_b_callback = NULL;


static void button_callback(uint gpio, uint32_t events) {
    if (gpio == BTN_A && btn_a_callback != NULL) {
        btn_a_callback(gpio, events);
    } else if (gpio == BTN_B && btn_b_callback != NULL) {
        btn_b_callback(gpio, events);
    }
}

void init_buttons(button_callback_t button_a_cb, button_callback_t button_b_cb) {
    btn_a_callback = button_a_cb;
    btn_b_callback = button_b_cb;

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &button_callback);
}
