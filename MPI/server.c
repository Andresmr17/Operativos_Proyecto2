// servidor.c actualizado
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "../Encrypt/encrypt.h"
#include "gpio_control.h"
#include "procesamiento.h"

void run_server(unsigned char *alicesk, unsigned char *bobpk) {
    for (int i = 0; i < 3; i++) {
        int ciphertext_len, chunk_len;
        unsigned char iv[12], tag[16];

        MPI_Recv(&ciphertext_len, 1, MPI_INT, 1, 10 + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&chunk_len, 1, MPI_INT, 1, 20 + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(iv, 12, MPI_UNSIGNED_CHAR, 1, 30 + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(tag, 16, MPI_UNSIGNED_CHAR, 1, 40 + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        unsigned char *ciphertext = malloc(ciphertext_len);
        MPI_Recv(ciphertext, ciphertext_len, MPI_CHAR, 1, 50 + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int dest = i + 2; // Nodos 2, 3, 4
        MPI_Send(&chunk_len, 1, MPI_INT, dest, 100, MPI_COMM_WORLD);
        MPI_Send(ciphertext, ciphertext_len, MPI_CHAR, dest, 101, MPI_COMM_WORLD);
        MPI_Send(iv, 12, MPI_UNSIGNED_CHAR, dest, 102, MPI_COMM_WORLD);
        MPI_Send(tag, 16, MPI_UNSIGNED_CHAR, dest, 103, MPI_COMM_WORLD);

        free(ciphertext);
    }

    char global_words[NUM_WORDS][WORD_LENGTH] = {0};
    int global_counts[NUM_WORDS] = {0};

    for (int i = 2; i <= 4; i++) {
        char recv_words[NUM_WORDS][WORD_LENGTH];
        int recv_counts[NUM_WORDS];
        MPI_Recv(recv_words, NUM_WORDS * WORD_LENGTH, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(recv_counts, NUM_WORDS, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        mergeCounts(global_words, global_counts, recv_words, recv_counts);
    }

    char most_frequent[WORD_LENGTH];
    int max_count;
    findMostFrequent(global_words, global_counts, most_frequent, &max_count);

    printf("[Servidor] Palabra más frecuente: '%s' (%d veces)\n", most_frequent, max_count);
    gpio_init();
    gpio_write_string(most_frequent);
    gpio_write_char(' ');
    char count_str[10];
    sprintf(count_str, "%d", max_count);
    gpio_write_string(count_str);
    gpio_signal_done();
}
