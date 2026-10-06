#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define HASH_SIZE 16384
typedef struct {
    char* word;
    int idx;
} HashEntry;
static unsigned int hash_func(const char* str) {
    unsigned int h = 5381;
    while (*str) {
        h = ((h << 5) + h) + (unsigned char)(*str++);
    }
    return h;
}
static void hash_insert(HashEntry* table, char* word, int idx) {
    unsigned int h = hash_func(word) % HASH_SIZE;
    while (table[h].word != NULL) {
        h = (h + 1) % HASH_SIZE;
    }
    table[h].word = word;
    table[h].idx = idx;
}
static int hash_find(HashEntry* table, const char* word) {
    unsigned int h = hash_func(word) % HASH_SIZE;
    while (table[h].word != NULL) {
        if (strcmp(table[h].word, word) == 0) {
            return table[h].idx;
        }
        h = (h + 1) % HASH_SIZE;
    }
    return -1;
}
int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize) {
    int endWordIdx = -1;
    HashEntry* table = (HashEntry*)calloc(HASH_SIZE, sizeof(HashEntry));
    if (!table) return 0;
    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(wordList[i], endWord) == 0) {
            endWordIdx = i;
        }
        hash_insert(table, wordList[i], i);
    }
    if (endWordIdx == -1) {
        free(table);
        return 0;
    }
    bool* visited = (bool*)calloc(wordListSize + 5, sizeof(bool));
    int* q_idx = (int*)malloc((wordListSize + 5) * sizeof(int));
    int* q_dist = (int*)malloc((wordListSize + 5) * sizeof(int));
    int head = 0, tail = 0;
    int start_idx = hash_find(table, beginWord);
    if (start_idx != -1) {
        visited[start_idx] = true;
    }
    q_idx[tail] = -1;
    q_dist[tail] = 1;
    tail++;
    int wordLen = strlen(beginWord);
    char temp[32];
    int result = 0;
    while (head < tail) {
        int curr_idx = q_idx[head];
        int dist = q_dist[head++];
        char* curr_word = (curr_idx == -1) ? beginWord : wordList[curr_idx];
        strcpy(temp, curr_word);
        for (int j = 0; j < wordLen; j++) {
            char orig = temp[j];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == orig) continue;
                temp[j] = c;
                int found_idx = hash_find(table, temp);
                if (found_idx != -1 && !visited[found_idx]) {
                    if (found_idx == endWordIdx) {
                        result = dist + 1;
                        goto cleanup;
                    }
                    visited[found_idx] = true;
                    q_idx[tail] = found_idx;
                    q_dist[tail] = dist + 1;
                    tail++;
                }
            }
            temp[j] = orig;
        }
    }
cleanup:
    free(table);
    free(visited);
    free(q_idx);
    free(q_dist);
    return result;
}