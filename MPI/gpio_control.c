#include "gpio_control.h"
#include <stdio.h>
#include <unistd.h>

void gpio_init() {
    // Aquí inicializarías pines reales (con sysfs o libgpiod)
    printf("[GPIO] Inicializando pines...\n");
}

void gpio_write_char(char c) {
    // Simulación: imprimir y esperar
    printf("[GPIO] Presionando tecla '%c'\n", c);
    usleep(200000); // Esperar 200ms
}

void gpio_write_string(const char* str) {
    printf("[GPIO] Escribiendo: \"%s\"\n", str);
    for (int i = 0; str[i] != '\0'; i++) {
        gpio_write_char(str[i]);
    }
}

void gpio_signal_done() {
    printf("[GPIO] Señal de finalización (LED encendido)\n");
}
