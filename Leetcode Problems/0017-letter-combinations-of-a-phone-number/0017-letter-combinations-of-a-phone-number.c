#include <stdlib.h>
#include <string.h>
const char* phoneMap[] = {
    "",     
    "",     
    "abc",  
    "def",  
    "ghi",  
    "jkl",  
    "mno",  
    "pqrs", 
    "tuv",  
    "wxyz"  
};
void backtrack(char* digits, int index, int len, char* current, int* resultIndex, char** result) {
    if (index == len) {
        current[len] = '\0';
        strcpy(result[*resultIndex], current);
        (*resultIndex)++;
        return;
    }
    int digit = digits[index] - '0';
    const char* letters = phoneMap[digit];
    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i];
        backtrack(digits, index + 1, len, current, resultIndex, result);
    }
}
char** letterCombinations(char* digits, int* returnSize) {
    int len = strlen(digits);
    if (len == 0) {
        *returnSize = 0;
        return NULL;
    }
    int totalCombinations = 1;
    for (int i = 0; i < len; i++) {
        int d = digits[i] - '0';
        totalCombinations *= strlen(phoneMap[d]);
    }
    *returnSize = totalCombinations;
    char** result = (char**)malloc(totalCombinations * sizeof(char*));
    for (int i = 0; i < totalCombinations; i++) {
        result[i] = (char*)malloc((len + 1) * sizeof(char));
    }
    char* current = (char*)malloc((len + 1) * sizeof(char));
    int resultIndex = 0;
    backtrack(digits, 0, len, current, &resultIndex, result);
    free(current);
    return result;
}
