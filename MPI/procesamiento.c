#include <string.h>
#include <stdio.h>
#define WORD_LENGTH 24
#define NUM_WORDS 500

void countWords(char *buffer, char words[][WORD_LENGTH], int counts[]) {
    char word[WORD_LENGTH];
    int index = 0, offset = 0;
    memset(words, 0, sizeof(char) * NUM_WORDS * WORD_LENGTH);
    memset(counts, 0, sizeof(int) * NUM_WORDS);

    while (sscanf(buffer + offset, "%23s%n", word, &index) == 1) {
        for (int i = 0; i < NUM_WORDS; i++) {
            if (strcmp(words[i], word) == 0) {
                counts[i]++;
                break;
            }
            if (strlen(words[i]) == 0) {
                strcpy(words[i], word);
                counts[i] = 1;
                break;
            }
        }
        offset += index;
        if (offset >= strlen(buffer)) break;
    }
}

void mergeCounts(char global_words[][WORD_LENGTH], int global_counts[], char local_words[][WORD_LENGTH], int local_counts[]) {
    for (int i = 0; i < NUM_WORDS; i++) {
        if (strlen(local_words[i]) == 0) continue;
        int found = 0;
        for (int j = 0; j < NUM_WORDS; j++) {
            if (strcmp(global_words[j], local_words[i]) == 0) {
                global_counts[j] += local_counts[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < NUM_WORDS; j++) {
                if (strlen(global_words[j]) == 0) {
                    strcpy(global_words[j], local_words[i]);
                    global_counts[j] = local_counts[i];
                    break;
                }
            }
        }
    }
}

void findMostFrequent(char words[][WORD_LENGTH], int counts[], char *most_frequent, int *max_count) {
    *max_count = 0;
    for (int i = 0; i < NUM_WORDS; i++) {
        if (counts[i] > *max_count) {
            *max_count = counts[i];
            strcpy(most_frequent, words[i]);
        }
    }
}
