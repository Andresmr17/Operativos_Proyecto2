// gpio_interface.h
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

void gpio_init();
void gpio_write_char(char c);
void gpio_write_string(const char *str);
void gpio_signal_done();

#endif
