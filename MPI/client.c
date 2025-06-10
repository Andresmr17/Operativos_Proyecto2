#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void getName(char *nombreArchivo) {
    printf("Ingrese el nombre del archivo a leer: ");
    if (fgets(nombreArchivo, MAX_FILENAME_LENGTH, stdin) != NULL) {
        // Eliminar el salto de línea al final, si lo hay
        size_t len = strlen(nombreArchivo);
        if (len > 0 && nombreArchivo[len - 1] == '\n') {
            nombreArchivo[len - 1] = '\0';
        }
    }
}

int main() {
    char name[MAX_FILENAME_LENGTH];
    getName(name);

    printf("Nombre del archivo ingresado: %s\n", name);

    return 0;
}
