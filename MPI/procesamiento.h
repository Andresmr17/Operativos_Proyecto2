#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#define WORD_LENGTH 24
#define NUM_WORDS 500

void countWords(char *buffer, char words[][WORD_LENGTH], int counts[]);
void mergeCounts(char global_words[][WORD_LENGTH], int global_counts[], char local_words[][WORD_LENGTH], int local_counts[]);
void findMostFrequent(char words[][WORD_LENGTH], int counts[], char *most_frequent, int *max_count);

#endif
