/**
 * Given N piles, Alice and Bod play the game. Each step, one of them can chooes 1 pile and split that pile into 2 smaller piles with the same size.
 * Alice goes first, player who cannot make a move is a fucking loser.
*/

vector<int> f;
int grundy(int n) {
  if (f[n] != -1)
    return f[n];
  unordered_set<int> mex;
  for (int i = 1; i * 2 < n; i++) {
    int sub = grundy(i) ^ grundy(n - i);
    mex.insert(sub);
  }
  int g = 0;
  while (mex.count(g))
    g++;
  return f[n] = g;
}