/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Check if two trees are isomorphic or not by rooting the trees
 * at their centroids. Vertices are 0-indexed.
 * Time: $O(N \log N)$
 * Status: stress-tested
 */
#pragma once

struct Ahu {
  int n, cnt = 0;
  vector<vi> g1, g2;
  map<vi, int> mp;
  int findCentroid(vector<vi> &g, int u, int p, vi& c) {
    bool ok = true; int nChild = 1;
    for (int v: g[u]) if (v != p) {
      int t = findCentroid(g, v, u, c);
      if (t > (n >> 1)) ok = false;
      nChild += t;
    }
    if (ok && (n - nChild) <= (n >> 1)) c.emb(u);
    return nChild;
  }
  int dfs(vector<vi> &g, int u, int p = -1) {
    vi id;
    for (int v: g[u])
      if (v != p) id.emb(dfs(g, v, u));
    sort(all(id));
    if (!mp.count(id)) mp[id] = ++cnt;
    return mp[id];
  }
  bool check() {
    vi c1, c2;
    findCentroid(g1, 0, -1, c1);
    findCentroid(g2, 0, -1, c2);
    if (c1.size() != c2.size()) return false;
    int f = dfs(g1, c1[0]);
    for (int r2: c2)
      if (dfs(g2, r2) == f) return true;
    return false;
  }
};
