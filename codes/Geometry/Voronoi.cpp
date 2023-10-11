vector<Directed_Line> frame;
vector<vector<ptld>> build_voronoi_cells(const vector<ptll> &p, const vector<Tri*> &res) {
    // O(nlogn)
    vector<vector<int>> adj(p.size());
    map<ptll, int> mp;
    for (size_t i = 0; i < p.size(); ++i)
        mp[p[i]] = i;
    const auto Get = [&](ptll z) {
        auto it = mp.find(z);
        return it == mp.end() ? -1 : it->second;
    };
    for (Tri *t : res) F3 {
        ptll A = t->p[i], B = t->p[R(i)];
        int a = Get(A), b = Get(B);
        if (a == -1 || b == -1) continue;
        adj[a].emplace_back(b);
    }
    // use `adj` and `p` and HPI to build cells
    vector<vector<ptld>> owo;
    for (size_t i = 0; i < p.size(); i++) {
        assert(!frame.empty());
        vector<Directed_Line> ls = frame; // the frame, a rectangle closing all points
        // coordinates of frame should be doubled
        for (int j : adj[i]) {
            point m = p[i] + p[j], d = (p[j] - p[i]).perp();
            assert(d.dis2() != 0);
            ls.emplace_back(m, m + d); // doubled coordinate
        }
        // use HPI(ls) to get the convex hull closing point i
        owo.push_back(HPI(ls));
    }
    return owo;
}
