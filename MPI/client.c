// cliente.c actualizado
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "../Encrypt/encrypt.h"

#define CHUNKS 3
#define MAX_SIZE 65536

void run_client(const char *filename, unsigned char *bobsk, unsigned char *alicepk) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("No se pudo abrir el archivo");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    unsigned char buffer[MAX_SIZE];
    size_t len = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    size_t base_len = len / CHUNKS;
    size_t offset = 0;

    for (int i = 0; i < CHUNKS; i++) {
        size_t chunk_len = (i == CHUNKS - 1) ? (len - offset) : base_len;

        unsigned char shared_secret[32], symmetric_key[32];
        generate_shared_secret(shared_secret, bobsk, alicepk);
        derive_symmetric_key(symmetric_key, shared_secret);

        unsigned char iv[12], tag[16];
        unsigned char *ciphertext = malloc(chunk_len + 64);
        int ciphertext_len;

        encrypt_message(symmetric_key, buffer + offset, chunk_len, iv, tag, ciphertext, &ciphertext_len);

        int dest_rank = 0; // El servidor es siempre rank 0
        MPI_Send(&ciphertext_len, 1, MPI_INT, dest_rank, 10 + i, MPI_COMM_WORLD);
        MPI_Send(&chunk_len, 1, MPI_INT, dest_rank, 20 + i, MPI_COMM_WORLD);
        MPI_Send(iv, 12, MPI_UNSIGNED_CHAR, dest_rank, 30 + i, MPI_COMM_WORLD);
        MPI_Send(tag, 16, MPI_UNSIGNED_CHAR, dest_rank, 40 + i, MPI_COMM_WORLD);
        MPI_Send(ciphertext, ciphertext_len, MPI_CHAR, dest_rank, 50 + i, MPI_COMM_WORLD);

        free(ciphertext);
        offset += chunk_len;
    }

    printf("[Cliente] Fragmentos cifrados enviados al servidor.\n");
}
