double findMaxAverage(int* nums, int nSize, int k) {
    long c_sum = 0;
    for (int i = 0; i < k; i++) {
        c_sum += nums[i];
    }
    long m_sum = c_sum;
    for (int i = k; i < nSize; i++) {
        c_sum += nums[i] - nums[i - k];
        if (c_sum > m_sum) {
            m_sum = c_sum;
        }
    }
    return (double)m_sum / k;
}
