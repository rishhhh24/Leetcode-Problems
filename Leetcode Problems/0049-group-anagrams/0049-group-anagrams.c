#include <stdlib.h>
#include <string.h>
typedef struct {
    char* original;
    char sorted[105];
} Word;
int compareWords(const void* a, const void* b) {
    return strcmp(((Word*)a)->sorted, ((Word*)b)->sorted);
}
void sortString(char* s, char* d) {
    int count[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    int idx = 0;
    for (int i = 0; i < 26; i++) {
        while (count[i] > 0) {
            d[idx++] = 'a' + i;
            count[i]--;
        }
    }
    d[idx] = '\0';
}
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    Word* words = (Word*)malloc(strsSize * sizeof(Word));
    for (int i = 0; i < strsSize; i++) {
        words[i].original = strs[i];
        sortString(strs[i], words[i].sorted);
    }
    qsort(words, strsSize, sizeof(Word), compareWords);
    int groupsCount = 0;
    for (int i = 0; i < strsSize; i++) {
        if (i == 0 || strcmp(words[i].sorted, words[i - 1].sorted) != 0) {
            groupsCount++;
        }
    }
    *returnSize = groupsCount;
    char*** result = (char***)malloc(groupsCount * sizeof(char**));
    *returnColumnSizes = (int*)malloc(groupsCount * sizeof(int));
    int groupIdx = -1;
    int colIdx = 0;
    for (int i = 0; i < strsSize; i++) {
        if (i == 0 || strcmp(words[i].sorted, words[i - 1].sorted) != 0) {
            groupIdx++;
            int count = 0;
            while (i + count < strsSize && strcmp(words[i + count].sorted, words[i].sorted) == 0) {
                count++;
            }
            (*returnColumnSizes)[groupIdx] = count;
            result[groupIdx] = (char**)malloc(count * sizeof(char*));
            colIdx = 0;
        }
        result[groupIdx][colIdx++] = words[i].original;
    }
    free(words);
    return result;
}
