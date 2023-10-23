/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Add line in decreasing slope, query in increasing x
 * Time: O(\log N)
 * Status: untested
 */
#pragma once

template <typename T = long long>
struct MinHull {
  struct Line {
    T a, b;
    Line(T a, T b) : a(a), b(b) {}
    T calc(T x) { return a * x + b; }
  };
  vector<Line> dq;
  size_t seen;
  bool overlap(Line& p1, Line& p2, Line& p3) {
    return 1.0 * (p3.b - p1.b) / (p1.a - p3.a) <=
           1.0 * (p2.b - p1.b) / (p1.a - p2.a);
  }
  void addLine(T a, T b) {
    Line newLine(a, b);
    while (dq.size() > seen + 1 &&
           overlap(dq[(int)dq.size() - 2], dq.back(), newLine))
      dq.pop_back();
    dq.pb(newLine);
  }
  T query(T x) {
    // change >= to <= this to get MaxHull
    while (seen + 1 < dq.size() && dq[seen].calc(x) >= dq[seen + 1].calc(x))
      ++seen;
    return dq[seen].calc(x);
  }
};