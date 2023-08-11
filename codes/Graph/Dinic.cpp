// Return max flor from s to t. INF, LINF and maxn required
template<typename T> // maxn: edge/node counts
struct dinic { // T: int or ll, up to range of flow
    const T IN_INF = (is_same_v<T, int>) ? INF : LINF;
    struct E {
        int v; T c; int r;
        E(int v, T c, int r):
            v(v), c(c), r(r){}
    };
    vector<E> adj[maxn];
    pair<int, int> is[maxn]; // counts of edges
    void add_edge(int u, int v, T c, int i = 0) {
        is[i] = {u, adj[u].size()};
        adj[u].push_back(E(v, c, (int) adj[v].size()));
        adj[v].push_back(E(u, 0, (int) adj[u].size() - 1));
    }
    int n, s, t;
    void init(int nn, int ss, int tt) {
        n = nn, s = ss, t = tt;
        for (int i = 0; i <= n; ++i)
            adj[i].clear();
    }
    int le[maxn], it[maxn];
    int bfs() {
        fill(le, le + maxn, -1); le[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, c, r] : adj[u]) {
                if (c > 0 && le[v] == -1)
                    le[v] = le[u] + 1, q.push(v);
            }
        }
        return ~le[t];
    }
    T dfs(int u, T f) {
        if (u == t) return f;
        for (int &i = it[u]; i < (int) adj[u].size(); ++i) {
            auto &[v, c, r] = adj[u][i];
            if (c > 0 && le[v] == le[u] + 1) {
                T d = dfs(v, min(c, f));
                if (d > 0) {
                    c -= d;
                    adj[v][r].c += d;
                    return d;
                }
            }
        }
        return 0;
    }
    T flow() {
        T ans = 0, d;
        while (bfs()) {
            fill(it, it + maxn, 0);
            while ((d = dfs(s, IN_INF)) > 0) ans += d;
        }
        return ans;
    }
    T rest(int i) {
        return adj[is[i].first][is[i].second].c;
    }
};
