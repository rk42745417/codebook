/* Find a edge coloring using at most d+1 colors, where d is the max deg, in O(V^3)
 * mat[i][j] is the color between i, j in 1-based (0 for no edge)
 * use recolor() to add edge. Calculation is done in every recolor */
struct edge_coloring { // 0-based
    int n;
    int mat[maxn][maxn];
    bool vis[maxn], col[maxn];
    void init(int _n) { n = _n; } // remember to init
    int check_conflict(int x, int loc) {
        for (int i = 0; i < n; i++)
            if (mat[x][i] == loc)
                return i;
        return n;
    }
    int get_block(int x) {
        memset(col, 0, sizeof col);
        for (int i = 0; i < n; i++) col[mat[x][i]] = 1;
        for (int i = 1; i < n; i++) if (!col[i]) return i;
        return n;
    }
    void recolor(int x, int y) {
        int pre_mat = get_block(y);
        int conflict = check_conflict(x, pre_mat);
        memset(vis, 0, sizeof vis);
        vis[y] = 1;
        vector<pair<int, int>> mat_line;
        mat_line.push_back({y, pre_mat});
        while (conflict != n && !vis[conflict]) {
            vis[conflict] = 1;
            y = conflict;
            pre_mat = get_block(y);
            mat_line.push_back({y, pre_mat});
            conflict = check_conflict(x, pre_mat);
        }
        if (conflict == n) {
            for (auto t : mat_line) {
                mat[x][t.first] = t.second;
                mat[t.first][x] = t.second;
            }
        }
        else {
            int pre_mat_x = get_block(x);
            int conflict_x = check_conflict(conflict, pre_mat_x);
            mat[x][conflict] = pre_mat_x;
            mat[conflict][x] = pre_mat_x;
            while (conflict_x != n) {
                int tmp = check_conflict(conflict_x, pre_mat);
                mat[conflict][conflict_x] = pre_mat;
                mat[conflict_x][conflict] = pre_mat;
                conflict = conflict_x;
                conflict_x = tmp;
                swap(pre_mat_x, pre_mat);
            }
            recolor(x, mat_line[0].first);
        }
    }
} mg;
