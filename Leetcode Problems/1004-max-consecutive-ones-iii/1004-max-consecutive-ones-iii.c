int longestOnes(int* nums, int nSize, int k) {
    int left = 0;
    int z_count = 0;
    int m_length = 0;
    for (int right = 0; right < nSize; right++) {
        if (nums[right] == 0) {
            z_count++;
        }
        while (z_count > k) {
            if (nums[left] == 0) {
                z_count--;
            }
            left++;
        }
        int c_length = right - left + 1;
        if (c_length > m_length) {
            m_length = c_length;
        }
    }
    return m_length;
}
