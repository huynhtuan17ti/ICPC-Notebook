/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Container where you can add segment of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: untested
 */
#pragma once

template<typename T, T minX, T maxX, T defVal, bool maxi = true>
struct DynamicLiChaoTree {
private:
  struct Line {
    T a, b;
    inline T calc(T x) const { return a * x + b; }
  };
  struct Node {
    Line line = {0, maxi ? defVal : -defVal};
    Node *lt = nullptr, *rt = nullptr;
  };
  Node* root;
  void update(Node* cur, T l, T r, T u, T v, Line nw) {
    if (v < l || r < u) return;
    T mid = (l + r) >> 1;
    if (u <= l && r <= v) {
      if (cur->line.calc(l) >= nw.calc(l)) swap(cur->line, nw);
      if (cur->line.calc(r) <= nw.calc(r)) {
        cur->line = nw;
        return;
      }
      if (nw.calc(mid) >= cur->line.calc(mid)) {
        if (!cur->rt) cur->rt = new Node();
        update(cur->rt, mid + 1, r, u, v, cur->line);
        cur->line = nw;
      } else {
        if (!cur->lt) cur->lt = new Node();
        update(cur->lt, l, mid, u, v, nw);
      }
    } else {
      if (!cur->rt) cur->rt = new Node();
      if (!cur->lt) cur->lt = new Node();
      update(cur->lt, l, mid, u, v, nw);
      update(cur->rt, mid + 1, r, u, v, nw);
    }
  }
public:
  // change l,r to add segment
  void add(T a, T b, T l = minX, T r = maxX) {
    if (!maxi) a = -a, b = -b;
    update(root, minX, maxX, l, r, {a, b});
  }
  T query(T x) {
    Node* cur = root;
    T res = cur->line.calc(x);
    T l = minX, r = maxX, mid;
    while (cur) {
      res = max(res, cur->line.calc(x));
      mid = (l + r) >> 1;
      if (x <= mid) cur = cur->lt, r = mid;
      else cur = cur->rt, l = mid + 1;
    }
    if (!maxi) res = -res;
    return res;
  }
  void init() {
    root = new Node;
  }
};
