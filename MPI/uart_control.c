// uart_control.c
#include "../Driver-Biblioteca/uart_interface.h"
#include "uart_control.h"

void uart_control_init() {
    uart_open();
}

void uart_control_write_char(char c) {
    uart_write_char(c);
}

void uart_control_write_string(const char *str) {
    uart_write_string(str);
}

void uart_control_signal_done() {
    uart_write_string("\nEND\n");  // Para que el arduino sepa que terminó
}

void uart_control_close() {
    uart_close();
}
