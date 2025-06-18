#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

void gpio_init();                         // Inicializa pines GPIO
void gpio_write_char(char c);            // Simula escribir una letra
void gpio_write_string(const char* str); // Escribe palabra completa
void gpio_signal_done();                 // Señal de finalización

#endif
