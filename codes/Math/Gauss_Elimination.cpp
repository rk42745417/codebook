// Returns n - rank
int gauss_elimination(vector<vector<double>> &d) {
    int n = d.size(), m = d[0].size();
    for (int i = 0, r = 0; i < m; ++i) {
        int p = -1;
        for (int j = r; j < n; ++j) {
            if (fabs(d[j][i]) < eps) continue;
            if (p == -1 || fabs(d[j][i]) > fabs(d[p][i])) p = j;
        }
        if (p == -1) continue;
        swap(d[p], d[r]);
        for (int j = 0; j < n; ++j) {
            if (r == j) continue;
            double z = d[j][i] / d[r][i];
            for (int k = 0; k < m; ++k) d[j][k] -= z * d[r][k];
        }
        r++;
    }
    return r;
}
