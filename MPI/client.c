#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "../Encrypt/encrypt.h"

#define MAX_FILE_SIZE 65536

// Cliente (en este caso rank != 0) usará la misma clave secreta que Bob
unsigned char bobsk[32] = {
 0x5d,0xab,0x08,0x7e,0x62,0x4a,0x8a,0x4b,
 0x79,0xe1,0x7f,0x8b,0x83,0x80,0x0e,0xe6,
 0x6f,0x3b,0xb1,0x29,0x26,0x18,0xb6,0xfd,
 0x1c,0x2f,0x8b,0x27,0xff,0x88,0xe0,0xeb
};

unsigned char alicepk[32] = {
 0x85,0x20,0xf0,0x09,0x89,0x30,0xa7,0x54,
 0x74,0x8b,0x7d,0xdc,0xb4,0x3e,0xf7,0x5a,
 0x0d,0xbf,0x3a,0x0d,0x26,0x38,0x1a,0xf4,
 0xeb,0xa4,0xa9,0x8e,0xaa,0x9b,0x4e,0x6a
};

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 1) {
        printf("Este cliente está diseñado para ejecutarse como el proceso 1 (rank 1)\n");
        MPI_Finalize();
        return 1;
    }

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_a_cifrar>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    const char *filename = argv[1];

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("No se pudo abrir el archivo");
        MPI_Finalize();
        return 1;
    }

    // Leer el archivo completo
    unsigned char buffer[MAX_FILE_SIZE];
    size_t len = fread(buffer, 1, MAX_FILE_SIZE, file);
    fclose(file);

    if (len == 0) {
        fprintf(stderr, "Archivo vacío\n");
        MPI_Finalize();
        return 1;
    }

    // Generar secreto compartido y clave simétrica
    unsigned char shared_secret[32];
    unsigned char symmetric_key[32];
    generate_shared_secret(shared_secret, bobsk, alicepk);
    derive_symmetric_key(symmetric_key, shared_secret);

    // Cifrar mensaje
    unsigned char *ciphertext = malloc(len + 64); // espacio extra por seguridad
    unsigned char iv[12], tag[16];
    int ciphertext_len;

    encrypt_message(symmetric_key, buffer, len, iv, tag, ciphertext, &ciphertext_len);

    // Enviar al servidor (rank 0)
    MPI_Send(&ciphertext_len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&len, 1, MPI_INT, 0, 4, MPI_COMM_WORLD); // tamaño original sin cifrar
    MPI_Send(iv, 12, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
    MPI_Send(tag, 16, MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD);
    MPI_Send(ciphertext, ciphertext_len, MPI_CHAR, 0, 3, MPI_COMM_WORLD);

    printf("Cliente: Enviado archivo cifrado al servidor\n");

    free(ciphertext);
    MPI_Finalize();
    return 0;
}
