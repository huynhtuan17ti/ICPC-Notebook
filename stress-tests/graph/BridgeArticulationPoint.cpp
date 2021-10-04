#include "../utilities/template.h"

#include "../../content/graph/BridgeArticulationPoint.h"

vector<pii> generateTree(int n) {
  vi p(n); rep(i, 1, n) p[i] = rand() % i;
  vi perm(n); iota(all(perm), 0); random_shuffle(all(perm));
  vector<pii> edges;
  rep(i, 1, n) {
    if (rand() % 2) {
      edges.emb(perm[i], perm[p[i]]);
    } else {
      edges.emb(perm[p[i]], perm[i]);
    }
  }
  random_shuffle(all(edges));
  return edges;
}

vector<pii> generateGraph(int n, int m) {
  auto edges = generateTree(n);
  m -= n - 1;
  rep(i,0,m) {
    int u = rand() % n;
    int v = rand() % n;
    while (v == u) v = rand() % n;
    edges.emb(u, v);
  }
  return edges;
}

struct DSU {
  int n; vector<int> par;
  void init(int _n) { n = _n; par.assign(n + 1, -1); }
  int root(int v) { return (par[v] < 0) ? v : (par[v] = root(par[v])); }
  void join(int x, int y) {
    if ((x = root(x)) == (y = root(y))) return;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
  }
  int countComponents() {
    int cntcmp = 0;
    rep(i,1,n+1) if (par[i] < 0) ++cntcmp;
    return cntcmp;
  }
} dsu;

int main() {
  srand(8);
  for (n = 5; n <= 1000; ++n) {
    m = n + rand() % n;
    auto edges = generateGraph(n, m);
    rep(i,1,n+1) {
      num[i] = low[i] = isCut[i] = 0;
      adj[i].clear();
    }
    bridges.clear();
    for (auto e: edges) {
      addEdge(e.first + 1, e.second + 1);
    }
    runTarjan();

    for (auto &e: bridges) {
      if (e.first > e.second) swap(e.first, e.second);
    }
    sort(all(bridges));

    rep(i,1,n+1) {
      dsu.init(n);
      for (auto e: edges) {
        if (e.first + 1 != i && e.second + 1 != i) {
          dsu.join(e.first + 1, e.second + 1);
        }
      }
      assert(isCut[i] == (dsu.countComponents() > 2));
    }

    vector<pii> realBridges;
    rep(i,0,m) {
      dsu.init(n);
      rep(j,0,m) {
        if (i != j) {
          dsu.join(edges[j].first + 1, edges[j].second + 1);
        }
      }
      if (dsu.countComponents() > 1) {
        realBridges.emb(min(edges[i].first, edges[i].second) + 1,
                        max(edges[i].first, edges[i].second) + 1);
      }
      sort(all(realBridges));
    }
    assert(bridges == realBridges);
  }
  cout << "Tests passed!" << endl;
}
