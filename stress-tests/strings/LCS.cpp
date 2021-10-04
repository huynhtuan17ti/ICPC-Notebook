#include "../utilities/template.h"

#include "../../content/strings/LCS.h"

string lcs2(const string &s, const string &t) {
  int bestpos = 0, best = 0;
  rep(j,0,sz(t)) rep(i,0,sz(s)) {
    int mx = min(sz(s) - i, sz(t) - j);
    int cur = 0;
    rep(k,0,mx) {
      if (s[i + k] != t[j + k]) break;
      ++cur;
    }
    if (cur > best) bestpos = i, best = cur;
  }
  return s.substr(bestpos, best);
}

int main() {
  srand(8);
  rep(N,5,1000) {
    string s = "";
    rep(i,0,N) s.pb(rand() % 26 + 'a');

    int len = rand() % N + 1;
    int pos = rand() % (N - len + 1);
    string pret = "", suft = "";
    rep(i,0,N-len) {
      if (rand() % 2 == 0) {
        pret.pb(rand() % 26 + 'a');
      } else {
        suft.pb(rand() % 26 + 'a');
      }
    }
    string t = pret + s.substr(pos, len) + suft;

    assert(lcs(s, t) == lcs2(s, t));
  }
  cout << "Tests passed!" << endl;
}
