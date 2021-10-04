/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Find bridges and articulation points (duplicate edges are ok).
 * Time: O(E + V)
 * Status: untested
 */
#pragma once

const int N = 1e6 + 6;

int n, m, Time, num[N], low[N];
unordered_map<int, int> adj[N];
vector<pii> bridges;
bool isCut[N];

inline void addEdge(int u, int v) {
  ++adj[u][v]; ++adj[v][u];
}

void dfs(int u, int p) {
  int nChild = 0;
  num[u] = low[u] = ++Time;
  for (auto &e: adj[u]) {
    int v = e.first;
    if (v == p) continue;
    ++nChild;
    if (num[v]) low[u] = min(low[u], num[v]);
    else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if ((p == -1 && nChild >= 2) || (p != -1 && low[v] >= num[u])) {
        isCut[u] = true;
      }
      if (low[v] >= num[v] && e.second == 1) {
        bridges.emb(u, v);
      }
    }
  }
}

void runTarjan() {
  for (int i = 1; i <= n; ++i) {
    if (!num[i]) dfs(i, -1);
  }
}
