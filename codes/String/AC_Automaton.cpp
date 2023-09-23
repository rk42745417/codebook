// Remember to call init then compile
class AhoCorasick {
 private:
    static constexpr int Z = 26;
    struct node {
      node *nxt[Z], *fail;
      vector<int> data;
      node(): fail(nullptr) {
        memset(nxt, 0, sizeof(nxt));
        data.clear();
      }
    } *rt;
    inline int Idx(char c) { return c - 'a'; }
 public:
    void init() { rt = new node(); }
    void add(const string &s, int d) {  // index, etc
      node* cur = rt;
      for (auto c : s) {
        if (!cur->nxt[Idx(c)])
          cur->nxt[Idx(c)] = new node();
        cur = cur->nxt[Idx(c)];
      }
      cur->data.push_back(d);
    }
    void compile() {
      vector<node*> bfs;
      size_t ptr = 0;
      for (int i = 0; i < Z; i++) {
        if (!rt->nxt[i]) {
          // uncomment 2 lines to make it DFA
          // rt->nxt[i] = rt;
          continue;
        }
        rt->nxt[i]->fail = rt;
        bfs.push_back(rt->nxt[i]);
      }
      while (ptr < bfs.size()) {
        node* u = bfs[ptr++];
        // More code here to record information...
        for (int i = 0; i < Z; i++) {
          if (!u->nxt[i]) {
            // u->nxt[i] = u->fail->nxt[i];
            continue;
          }
          node* u_f = u->fail;
          while (u_f) {
            if (!u_f->nxt[i]) {
                u_f = u_f->fail;
                continue;
            }
            u->nxt[i]->fail = u_f->nxt[i];
            break;
          }
          if (!u_f) u->nxt[i]->fail = rt;
          bfs.push_back(u->nxt[i]);
        }
      }
    }
    void match(const string &s, vector<int> &ret) {
      node* u = rt;
      for (auto c : s) {
        while (u != rt && !u->nxt[Idx(c)])
          u = u->fail;
        u = u->nxt[Idx(c)];
        if (!u) u = rt;
        node* tmp = u;
        while (tmp != rt) {
          for (auto d : tmp->data)
            ret.push_back(d);
          tmp = tmp->fail;
        }
      }
    }
} ac;
