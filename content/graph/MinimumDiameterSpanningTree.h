/**
 * Author: hieplpvip
 * Date: 2020-10-28
 * License: CC0
 * Source: https://web.archive.org/web/20160309101249/https://adn.botao.hu/adn-backup/blog/attachments/month_0705/32007531153238.pdf
 * Description: Find a minimum diameter spanning tree
 * Usage: Call init() first. Add edge and call findMDST(). Return diameter.
 * Time: $O(n^3)$
 * Status: Tested on https://codeforces.com/contest/266/problem/D
 */
#pragma once

const int N = 500, oo = 1e9;

struct Edge {
  int u, v, w;
};

int n, m, d[N][N], ans = oo;
vector<int> que[N];
vector<Edge> edges;

inline void init() {
  rep(i,1,n+1) rep(j,1,n+1) d[i][j] = (i == j) ? 0 : oo;
}
inline void addEdge(int u, int v, int w) {
  w *= 2; d[u][v] = d[v][u] = min(d[u][v], w);
  edges.pb({u, v, w});
}
int findMDST() {
  rep(k,1,n+1) rep(u,1,n+1) rep(v,1,n+1)
    d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
  rep(i,1,n+1) {
    que[i].resize(n);
    iota(all(que[i]), 1);
    sort(all(que[i]), [&](const int &a, const int &b) {
      return d[i][a] > d[i][b];
    });
  }
  int ans = oo;
  for (auto &e: edges) {
    int &u = e.u, &v = e.v, cur = que[u][0];
    int w = e.w, tans = oo;
    tans = min({tans, d[u][cur], d[v][cur] + w});
    for (int &z: que[u]) {
      if (d[v][cur] < d[v][z]) {
        tans = min(tans, (w + d[v][cur] + d[u][z]) / 2);
        cur = z;
      }
    }
    tans = min({tans, d[v][cur], d[u][cur] + w});
    ans = min(ans, tans);
  }
  return ans;
}
