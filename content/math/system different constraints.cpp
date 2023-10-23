/* http://poj.org/problem?id=2983 */
/*
## Problem
Given a system of inequations of the form x_j - x_i <= w_ij. 
Find any solution x_1, x_2, ..., x_n or show that the system has no solution.

## Solution
We construct a n-vertex graph (vertext i represents variable x_i). For each inequation x_j - x_i <= w_ij, 
we add an edge from i to j with weight w_ij.

If the graph has negative cycle, there's no solution. 
Else, create a virtual vertex s, add edge with weight 0 from s to every x_i, 
the solution is the shortest path from s to n vertices.
*/
typedef long long ll;

struct edge {
  int u, v, c;
};

/*
    check if negative cycle
*/
bool bellman_ford(int n, vector<edge> edges) {
  int m = (int)edges.size();
  vector<ll> dist(n + 1);
  for (int i = 1; i < n; i++)
    for (int j = 0; j < m; j++) {
      int u = edges[j].u;
      int v = edges[j].v;
      int c = edges[j].c;
      if (dist[v] > dist[u] + c)
        dist[v] = dist[u] + c;
    }

  for (int j = 0; j < m; j++) {
    int u = edges[j].u;
    int v = edges[j].v;
    int c = edges[j].c;
    if (dist[v] > dist[u] + c)
      return true;
  }
  return false;
}

void solve(int n, int m) {
  vector<edge> edges;
  while (m--) {
    char t;
    cin >> t;
    if (t == 'P') {
      int u, v, c;
      cin >> u >> v >> c;
      edges.push_back({u, v, c});
      edges.push_back({v, u, -c});
    } else {
      int u, v;
      cin >> u >> v;
      edges.push_back({v, u, -1});
    }
  }
  if (bellman_ford(n, edges))
    cout << "Unreliable" << '\n';
  else
    cout << "Reliable" << '\n';
}