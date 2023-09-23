vector<int> kmp(const string &s) {
    int n = s.size();
    vector<int> dp(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j])
            j = dp[j - 1];
        if (s[i] == s[j])
            j++;
        dp[i] = j;
    }
    return dp;
}
