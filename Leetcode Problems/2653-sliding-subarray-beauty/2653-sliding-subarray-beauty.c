int* getSubarrayBeauty(int* nums, int numsSize, int k, int x, int* returnSize) {
    int resSize = numsSize - k + 1;
    *returnSize = resSize;
    int* ans = (int*)malloc(resSize * sizeof(int));
    int freq[101] = {0};
    for (int i = 0; i < k - 1; i++) {
        freq[nums[i] + 50]++;
    }
    for (int i = k - 1; i < numsSize; i++) {
        freq[nums[i] + 50]++;
        int count = 0;
        int beauty = 0;
        for (int j = 0; j < 50; j++) {
            count += freq[j];
            if (count >= x) {
                beauty = j - 50; 
                break;
            }
        }
        ans[i - k + 1] = beauty;
        freq[nums[i - k + 1] + 50]--;
    }
    
    return ans;
}