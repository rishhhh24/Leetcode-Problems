#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define HASH_SIZE 32768
typedef struct {
    long long key; 
    int val;       
    bool used;
} RemEntry;
static inline unsigned int hash_rem(long long key) {
    unsigned long k = (unsigned long long)key;
    k = (k ^ (k >> 30)) * 0xbf58476d1ce4e5b9ULL;
    k = (k ^ (k >> 27)) * 0x94d049bb133111ebULL;
    k = k ^ (k >> 31);
    return (unsigned int)(k % HASH_SIZE);
}
static void map_put(RemEntry* table, long long key, int val) {
    unsigned int h = hash_rem(key);
    while (table[h].used) {
        if (table[h].key == key) {
            table[h].val = val;
            return;
        }
        h = (h + 1) % HASH_SIZE;
    }
    table[h].key = key;
    table[h].val = val;
    table[h].used = true;
}
static int map_get(RemEntry* table, long long key) {
    unsigned int h = hash_rem(key);
    while (table[h].used) {
        if (table[h].key == key) {
            return table[h].val;
        }
        h = (h + 1) % HASH_SIZE;
    }
    return -1;
}
char* fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) {
        char* zeroStr = (char*)malloc(2 * sizeof(char));
        strcpy(zeroStr, "0");
        return zeroStr;
    }
    char* res = (char*)malloc(30000 * sizeof(char));
    int len = 0;
    if ((numerator < 0) ^ (denominator < 0)) {
        res[len++] = '-';
    }
    long long num = llabs((long long)numerator);
    long long den = llabs((long long)denominator);
    long long int_part = num / den;
    len += sprintf(res + len, "%lld", int_part);
    long long rem = num % den;
    if (rem == 0) {
        res[len] = '\0';
        return res;
    }
    res[len++] = '.';
    RemEntry* table = (RemEntry*)calloc(HASH_SIZE, sizeof(RemEntry));
    while (rem != 0) {
        int prev_pos = map_get(table, rem);
        if (prev_pos != -1) {
            for (int i = len; i > prev_pos; i--) {
                res[i] = res[i - 1];
            }
            res[prev_pos] = '(';
            len++;
            res[len++] = ')';
            res[len] = '\0';
            free(table);
            return res;
        }
        map_put(table, rem, len);
        rem *= 10;
        res[len++] = (char)('0' + (rem / den));
        rem %= den;
    }
    res[len] = '\0';
    free(table);
    return res;
}