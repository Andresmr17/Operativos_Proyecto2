#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "biblioteca.h" // o gpio_interface.h si usás eso

static int serial_port = -1;

int sendToArduino(const char* message) {
    const char* port_name = "/dev/ttyACM0";

    if (serial_port < 0) {
        serial_port = open(port_name, O_RDWR | O_NOCTTY);
        if (serial_port < 0) {
            perror("Error al abrir el puerto serial");
            return 1;
        }

        struct termios tty;
        memset(&tty, 0, sizeof(tty));
        if (tcgetattr(serial_port, &tty) != 0) {
            perror("Error al obtener configuración del puerto");
            return 1;
        }

        cfsetospeed(&tty, B9600);
        cfsetispeed(&tty, B9600);
        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
        tty.c_cflag &= ~PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        tty.c_lflag = 0;
        tty.c_oflag = 0;
        tty.c_cc[VMIN]  = 0;
        tty.c_cc[VTIME] = 10;

        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
            perror("Error al establecer configuración del puerto");
            return 1;
        }
    }

    ssize_t result = write(serial_port, message, strlen(message));
    if (result < 0) {
        perror("Error al escribir en el puerto serial");
        return 1;
    }

    return 0;
}
