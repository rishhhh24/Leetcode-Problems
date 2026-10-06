#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
bool wordPattern(char* pattern, char* s) {
    char* charToWord[26];
    for (int i = 0; i < 26; i++) {
        charToWord[i] = NULL;
    }
    char* sCopy = malloc(strlen(s) + 1);
    strcpy(sCopy, s);
    int patternLen = strlen(pattern);
    int wordCount = 0;
    char* word = strtok(sCopy, " ");
    while (word != NULL) {
        if (wordCount >= patternLen) {
            free(sCopy);
            return false;
        }
        char c = pattern[wordCount];
        int index = c - 'a';
        if (charToWord[index] != NULL) {
            if (strcmp(charToWord[index], word) != 0) {
                free(sCopy);
                return false;
            }
        } else {
            for (int i = 0; i < 26; i++) {
                if (charToWord[i] != NULL && strcmp(charToWord[i], word) == 0) {
                    free(sCopy);
                    return false;
                }
            }
            charToWord[index] = word;
        }
        word = strtok(NULL, " ");
        wordCount++;
    }
    free(sCopy);
    return wordCount == patternLen;
}
