#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using pll = pair<int64_t, int64_t>;
using ld = long double;
 
#define long int64_t
#define all(c) c.begin(), c.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(0)
 
template <class T> inline void chmin(T &a, const T& val) { if (a > val) a = val; }
template <class T> inline void chmax(T &a, const T& val) { if (a < val) a = val; }
template <class T> long sqr(T a) { return 1ll * a * a; }
template <class T> void compress(T &a) { sort(all(a)); a.resize(unique(all(a)) - a.begin()); }
template <class T> T power(T x, long n){
    T res = 1;
    for (; n; x *= x, n >>= 1){
        if (n & 1) res *= x;
    }
    return res;
}
 
const double pi = acos(-1.00);
const double eps = 1e-6;
const int INF = 2e9;
const int MOD = 1e9 + 7;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
 
struct SegmentTree {
#define m ((l + r) >> 1)
#define lc (i << 1)
#define rc (i << 1 | 1)
    vector<int> mx;
    int n;
 
    SegmentTree(int n = 0) : n(n){    
        mx.resize(4 * n + 1, -INF);
    }
 
    SegmentTree(const vector<int> &a) : n(a.size()) {
        mx.resize(4 * n + 1, 0);
        function<void(int, int, int)> build = [&](int i, int l, int r){
            if (l == r){
                mx[i] = a[l - 1];
                return;
            }
            build(lc, l, m); build(rc, m + 1, r);
            mx[i] = max(mx[lc], mx[rc]);
        };
        build(1, 1, n);
    }
 
    void update(int i, int l, int r, int p, int val){
        if (l == r){
            mx[i] = val;
            return;
        }  
        if (p <= m) update(lc, l, m, p, val); 
        else update(rc, m + 1, r, p, val);
        mx[i] = max(mx[lc], mx[rc]);
    }
 
    int get(int i, int l, int r, int u, int v){
        if (v < l || r < u) return -INF;
        if (u <= l && r <= v) return mx[i];
        return max(get(lc, l, m, u, v), get(rc, m + 1, r, u, v));
    }
 
    void update(int p, int val){
        update(1, 1, n, p, val);
    }
 
    int get(int l, int r){
        return get(1, 1, n, l, r);
    }
#undef m
#undef lc
#undef rc  
};
 
// source: https://g...content-available-to-author-only...b.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
template<bool VALS_IN_EDGS = false> struct HeavyLight{
    int n, ti;
    vector<vector<int>> adj;
    vector<int> par, pos, head, dep, sz;
    SegmentTree tree;
 
    HeavyLight(int n = 0) : n(n), ti(0), tree(n) {    
        par.resize(n + 1); pos.resize(n + 1); sz.resize(n + 1);
        adj.resize(n + 1); head.resize(n + 1); dep.resize(n + 1);
    }
 
    void addEdge(int u, int v){
        adj[u].push_back(v); adj[v].push_back(u);
    }
 
    void dfsSz(int u){
        sz[u] = 1;
        for (int &v : adj[u]){
            par[v] = u; dep[v] = dep[u] + 1;
            adj[v].erase(find(all(adj[v]), u)); // remove parent
            dfsSz(v); 
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);  
        }
    }
 
    void dfsHLD(int u){
        pos[u] = ++ti;
        for (int v : adj[u]){
            head[v] = (v == adj[u][0] ? head[u] : v);
            dfsHLD(v);
        }
    }
 
    void init(int root = 1){
        head[root] = root;
        dfsSz(root); dfsHLD(root);
    }
 
    int lca(int u, int v){
        for (; head[u] != head[v]; v = par[head[v]]){
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
        }
        return (dep[u] < dep[v] ? u : v);
    }
 
    template<class OP> void processPath(int u, int v, OP op){
        for (; head[u] != head[v]; v = par[head[v]]){
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            op(pos[head[v]], pos[v]);
        }
        if (dep[u] > dep[v]) swap(u, v);
        op(pos[u] + VALS_IN_EDGS, pos[v]);
    }
 
    void update(int u, int x){
        tree.update(pos[u], x);
    }
 
    int queryPath(int u, int v){
        int ans = -INF;
        processPath(u, v, [this, &ans](int l, int r){
            chmax(ans, tree.get(l, r));
        });
        return ans;
    }
};
 
void solve(){
    int n, q; cin >> n >> q;
    HeavyLight hld(n);
    vector<int> val(n);
    for (int &x : val) cin >> x;
    for (int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        hld.addEdge(u, v);
    }
    hld.init(1);
    for (int i = 0; i < n; i++){
        hld.update(i + 1, val[i]);
    }
    while (q--){
        int op, x, y; cin >> op >> x >> y;
        if (op == 1) hld.update(x, y);
        else cout << hld.queryPath(x, y) << ' ';
    }
}
 
int main()
{
    fastio;
    int T = 1; //cin >> T;
    while (T--){
        solve();
    }
    return 0;
}