// nodo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "../Encrypt/encrypt.h"
#include "procesamiento.h"

void run_node(int rank, unsigned char *alicesk, unsigned char *bobpk) {
    int chunk_size;
    MPI_Recv(&chunk_size, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    unsigned char *cipher_chunk = malloc(chunk_size);
    MPI_Recv(cipher_chunk, chunk_size, MPI_CHAR, 0, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    unsigned char iv[12], tag[16];
    MPI_Recv(iv, 12, MPI_UNSIGNED_CHAR, 0, 102, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(tag, 16, MPI_UNSIGNED_CHAR, 0, 103, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    unsigned char shared_secret[32], symmetric_key[32];
    generate_shared_secret(shared_secret, alicesk, bobpk);
    derive_symmetric_key(symmetric_key, shared_secret);

    unsigned char *decrypted = malloc(chunk_size + 1);
    if (!decrypt_message(symmetric_key, iv, tag, cipher_chunk, chunk_size, decrypted)) {
        fprintf(stderr, "[Nodo %d] Error al descifrar el bloque\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    decrypted[chunk_size] = '\0';
    char local_words[NUM_WORDS][WORD_LENGTH] = {0};
    int local_counts[NUM_WORDS] = {0};
    countWords((char*)decrypted, local_words, local_counts);

    MPI_Send(local_words, NUM_WORDS * WORD_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    MPI_Send(local_counts, NUM_WORDS, MPI_INT, 0, 0, MPI_COMM_WORLD);

    free(cipher_chunk);
    free(decrypted);

    printf("[Nodo %d] Conteo de palabras enviado al servidor.\n", rank);
}
