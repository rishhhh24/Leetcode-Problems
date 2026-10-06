int maxScore(int* cP, int cPSize, int k) {
    int c_sum = 0;
    for (int i = 0; i < k; i++) {
        c_sum += cP[i];
    }
    int m_points = c_sum;
    for (int i = 0; i < k; i++) {
        c_sum -= cP[k - 1 - i];  
        c_sum += cP[cPSize - 1 - i];
        if (c_sum > m_points) {
            m_points = c_sum;
        }
    }
    return m_points;
}
