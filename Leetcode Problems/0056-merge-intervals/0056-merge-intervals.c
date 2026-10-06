int compare(const void *a, const void *b) {
    int *intervalA = *(int **)a;
    int *intervalB = *(int **)b;
    
    if (intervalA[0] < intervalB[0]) return -1;
    if (intervalA[0] > intervalB[0]) return 1;
    return 0;
}
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize <= 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    qsort(intervals, intervalsSize, sizeof(int*), compare);
    int** merged = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    int count = 0;
    merged[count] = (int*)malloc(2 * sizeof(int));
    merged[count][0] = intervals[0][0];
    merged[count][1] = intervals[0][1];
    (*returnColumnSizes)[count] = 2;
    count++;
    for (int i = 1; i < intervalsSize; i++) {
        int currentStart = intervals[i][0];
        int currentEnd = intervals[i][1];
        int lastMergedEnd = merged[count - 1][1];

        if (currentStart <= lastMergedEnd) {
            if (currentEnd > lastMergedEnd) {
                merged[count - 1][1] = currentEnd;
            }
        } else {
            merged[count] = (int*)malloc(2 * sizeof(int));
            merged[count][0] = currentStart;
            merged[count][1] = currentEnd;
            (*returnColumnSizes)[count] = 2;
            count++;
        }
    }
    *returnSize = count;
    return merged;
}
