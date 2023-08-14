// Find minimum directed minimum spanning tree in O(Elog V)
// DSU rollback is reuqired
// Return parent of all nodes, -1 for unreachable ones and root
struct dmst_edge { int a, b; ll w; };
struct dmst_node {  // lazy skew heap node
    dmst_edge key;
    dmst_node *l, *r;
    ll delta;
    void prop() {
        key.w += delta;
        if (l) l->delta += delta;
        if (r) r->delta += delta;
        delta = 0;
    }
    dmst_edge top() { prop(); return key; }
};
dmst_node *dmst_merge(dmst_node *a, dmst_node *b) {
    if (!a || !b) return a ?: b;
    a->prop();
    b->prop();
    if (a->key.w > b->key.w) swap(a, b);
    swap(a->l, (a->r = dmst_merge(b, a->r)));
    return a;
}
void dmst_pop(dmst_node*& a) {
    a->prop();
    a = dmst_merge(a->l, a->r);
}
pair<ll, vector<int>> dmst(int n, int r, const vector<dmst_edge>& g) {
    dsu_undo uf(n);
    vector<dmst_node*> heap(n);
    vector<dmst_node*> tmp;
    for (dmst_edge e : g) {
        tmp.push_back(new dmst_node {e});
        heap[e.b] = dmst_merge(heap[e.b], tmp.back());
    }
    ll res = 0;
    vector<int> seen(n, -1), path(n), par(n);
    seen[r] = r;
    vector<dmst_edge> Q(n), in(n, {-1, -1}), comp;
    deque<tuple<int, int, vector<dmst_edge>>> cycs;
    for (int s = 0; s < n; s++) {
        int u = s, qi = 0, w;
        while (seen[u] < 0) {
            if (!heap[u]) return {-1, {}};
            dmst_edge e = heap[u]->top();
            heap[u]->delta -= e.w;
            dmst_pop(heap[u]);
            Q[qi] = e;
            path[qi++] = u;
            seen[u] = s;
            res += e.w;
            u = uf.find(e.a);
            if (seen[u] == s) {  // found cycle, contract
                dmst_node* cyc = 0;
                int end = qi, time = uf.time();
                do  {
                    cyc = dmst_merge(cyc, heap[w = path[--qi]]);
                } while (uf.join(u, w));
                u = uf.find(u);
                heap[u] = cyc;
                seen[u] = -1;
                cycs.push_front({u, time, {&Q[qi], &Q[end]}});
            }
        }
        for (int i = 0; i < qi; i++)
            in[uf.find(Q[i].b)] = Q[i];
    }

    for (auto& [u, t, comp] : cycs) {  // restore sol (optional)
        uf.rollback(t);
        dmst_edge indmst_edge = in[u];
        for (auto& e : comp) in[uf.find(e.b)] = e;
        in[uf.find(indmst_edge.b)] = indmst_edge;
    }
    for (int i = 0; i < n; i++)
        par[i] = in[i].a;
    for (auto &a : tmp)
        delete a;
    return {res, par};
}
