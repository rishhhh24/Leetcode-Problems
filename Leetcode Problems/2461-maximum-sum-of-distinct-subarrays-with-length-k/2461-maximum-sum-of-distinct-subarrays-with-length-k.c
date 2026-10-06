#define MAX_VAL 100005
long long maximumSubarraySum(int* nums, int numsSize, int k) {
    int* freq = (int*)calloc(MAX_VAL, sizeof(int));
    long long current_sum = 0;
    long long max_sum = 0;
    int unique_count = 0;
    for (int i = 0; i < numsSize; i++) {
        int incoming = nums[i];
        if (freq[incoming] == 0) {
            unique_count++;
        }
        freq[incoming]++;
        current_sum += incoming;
        if (i >= k) {
            int outgoing = nums[i - k];
            freq[outgoing]--;
            if (freq[outgoing] == 0) {
                unique_count--;
            }
            current_sum -= outgoing;
        }
        if (i >= k - 1) {
            if (unique_count == k) {
               if (current_sum > max_sum) {
                    max_sum = current_sum;
                }
            }
        }
    }
      free(freq);
    return max_sum;
}