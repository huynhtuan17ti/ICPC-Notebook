#include "../utilities/template.h"

#include "../../content/graph/Ahu.h"

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

int main() {
  srand(8);
  rep(N,2,3000) {
    vi perm(N); iota(all(perm), 0); random_shuffle(all(perm));
    auto edges = generateTree(N);
    Ahu ahu;
    ahu.n = N;
    ahu.g1.resize(N);
    ahu.g2.resize(N);
    for (auto e: edges) {
      ahu.g1[e.first].emb(e.second);
      ahu.g1[e.second].emb(e.first);
      ahu.g2[perm[e.first]].emb(perm[e.second]);
      ahu.g2[perm[e.second]].emb(perm[e.first]);
    }
    assert(ahu.check());
  }
  rep(N,100,3000) {
    Ahu ahu;
    ahu.n = N;
    ahu.g1.resize(N);
    ahu.g2.resize(N);
    auto edges = generateTree(N);
    for (auto e: edges) {
      ahu.g1[e.first].emb(e.second);
      ahu.g1[e.second].emb(e.first);
    }
    edges = generateTree(N);
    for (auto e: edges) {
      ahu.g2[e.first].emb(e.second);
      ahu.g2[e.second].emb(e.first);
    }
    assert(!ahu.check());
  }
  cout << "Tests passed!" << endl;
}
