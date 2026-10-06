#include <stdlib.h>
#include <string.h>
typedef struct TrieNode {
    int id;
    struct TrieNode* children[26];
} TrieNode;
TrieNode* createNode(TrieNode* pool, int* poolPtr) {
    TrieNode* node = &pool[(*poolPtr)++];
    node->id = -1;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}
int getWordId(TrieNode* root, const char* s, int start, int len) {
    TrieNode* curr = root;
    for (int i = 0; i < len; i++) {
        int idx = s[start + i] - 'a';
        if (!curr->children[idx]) return -1;
        curr = curr->children[idx];
    }
    return curr->id;
}
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    *returnSize = 0;
    if (!s || wordsSize == 0) return NULL;
    int sLen = strlen(s);
    int wordLen = strlen(words[0]);
    int totalWordsLen = wordsSize * wordLen;
    if (sLen < totalWordsLen) return NULL;
    TrieNode* nodePool = (TrieNode*)malloc(sizeof(TrieNode) * 150005);
    int poolPtr = 0;
    TrieNode* root = createNode(nodePool, &poolPtr);
    int* wordCount = (int*)calloc(wordsSize, sizeof(int));
    int numUniqueWords = 0;
    for (int i = 0; i < wordsSize; i++) {
        TrieNode* curr = root;
        for (int j = 0; j < wordLen; j++) {
            int idx = words[i][j] - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = createNode(nodePool, &poolPtr);
            }
            curr = curr->children[idx];
        }
        if (curr->id == -1) {
            curr->id = numUniqueWords++;
        }
        wordCount[curr->id]++;
    }
    int* result = (int*)malloc(sizeof(int) * sLen);
    int* currCount = (int*)malloc(sizeof(int) * numUniqueWords);
    for (int i = 0; i < wordLen; i++) {
        int left = i;
        int right = i;
        int matchedWords = 0;
        memset(currCount, 0, sizeof(int) * numUniqueWords);
        while (right + wordLen <= sLen) {
            int id = getWordId(root, s, right, wordLen);
            right += wordLen;
            if (id != -1) {
                currCount[id]++;
                matchedWords++;
                while (currCount[id] > wordCount[id]) {
                    int leftId = getWordId(root, s, left, wordLen);
                    currCount[leftId]--;
                    matchedWords--;
                    left += wordLen;
                }
                if (matchedWords == wordsSize) {
                    result[(*returnSize)++] = left;
                }
            } else {
                memset(currCount, 0, sizeof(int) * numUniqueWords);
                matchedWords = 0;
                left = right;
            }
        }
    }
    free(wordCount);
    free(currCount);
    free(nodePool);

    return result;
}
