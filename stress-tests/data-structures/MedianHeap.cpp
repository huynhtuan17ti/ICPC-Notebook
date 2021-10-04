#include "../utilities/template.h"

#include "../../content/data-structures/MedianHeap.h"

int main() {
  srand(8);
  rep(N,0,1000) {
    MedianHeap mh;
    vector<int> a(N), b;
    rep(i,0,N) a[i] = i;
    random_shuffle(all(a));
    rep(i,0,2*N) {
      if (a.size() == 0 || (b.size() > 0 && rand() % 2 == 0)) {
        int ind = (int)b.size() / 2;
        assert(!mh.empty());
        assert(mh.pop() == b[ind]);
        b.erase(b.begin() + ind);
      } else {
        int x = a.back(); a.pop_back();
        mh.push(x);
        b.push_back(x); sort(all(b));
      }
    }
    assert(a.size() == 0);
    assert(b.size() == 0);
    assert(mh.empty());
  }
  cout << "Tests passed!" << endl;
}
