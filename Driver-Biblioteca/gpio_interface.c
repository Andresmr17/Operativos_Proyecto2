// gpio_interface.c
#include <string.h>
#include "gpio_interface.h"
#include "biblioteca.h"  // o biblioteca.h si ahí está enviarMensaje()

void gpio_init() {
    // Aquí podrías enviar un comando de inicio si lo necesitás
}

void gpio_write_char(char c) {
    enviarMensaje(&c, 1);
}

void gpio_write_string(const char *str) {
    enviarMensaje(str, strlen(str));
}

void gpio_signal_done() {
    const char *end = "END\n";
    enviarMensaje(end, strlen(end));
}
