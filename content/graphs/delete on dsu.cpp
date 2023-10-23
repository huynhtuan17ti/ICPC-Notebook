struct dsu_save {
  int u, v;
  int par_u, par_v;

  dsu_save() {}

  dsu_save(int _v, int _par_v, int _u, int _par_u)
      : v(_v), par_v(_par_v), u(_u), par_u(_par_u) {}
};

class dsu_rollback {
 public:
  vector<int> parent;
  int comps;
  stack<dsu_save> st_op;

  dsu_rollback(){};

  dsu_rollback(int n) {
    parent.resize(n + 1, -1);
    comps = n;
  }

  int find_set(int u) {
    while (parent[u] > 0)
      u = parent[u];
    return u;
  }

  bool Union(int u, int v) {
    int U = find_set(u);
    int V = find_set(v);
    if (U == V)
      return false;
    comps--;
    st_op.push(dsu_save(U, parent[U], V, parent[V]));
    int x = parent[U] + parent[V];
    if (parent[U] > parent[V]) {
      parent[U] = V;
      parent[V] = x;
    } else {
      parent[U] = x;
      parent[V] = U;
    }
    return true;
  }

  void rollback() {
    if (st_op.empty())
      return;
    dsu_save x = st_op.top();
    st_op.pop();
    comps++;
    parent[x.u] = x.par_u;
    parent[x.v] = x.par_v;
  }
};

struct query {
  int u, v;
  bool united;
};

class QueryTree {
  vector<vector<query>> t;
  dsu_rollback dsu;
  int T;

 public:
  QueryTree(int _T, int n) {
    this->T = _T;
    this->dsu = dsu_rollback(n);
    t.resize(4 * T + 4);
  }

  void add_to_tree(int id, int l, int r, int u, int v, query q) {
    if (v < l || r < u || u > v)
      return;
    if (u <= l && r <= v) {
      t[id].push_back(q);
      return;
    }
    int mid = (l + r) >> 1;
    add_to_tree(2 * id, l, mid, u, v, q);
    add_to_tree(2 * id + 1, mid + 1, r, u, v, q);
  }

  void add_query(query q, int l, int r) { add_to_tree(1, 0, T - 1, l, r, q); }

  void DFS(int id, int l, int r, vector<int>& ans) {
    for (query& q : t[id])
      q.united = dsu.Union(q.u, q.v);

    if (l == r) {
      ans[l] = dsu.comps;
    } else {
      int mid = (l + r) >> 1;
      DFS(2 * id, l, mid, ans);
      DFS(2 * id + 1, mid + 1, r, ans);
    }

    for (query& q : t[id])
      if (q.united)
        dsu.rollback();
  }

  vector<int> compute() {
    vector<int> ans(T);  // T query
    DFS(1, 0, T - 1, ans);
    return ans;
  }
};