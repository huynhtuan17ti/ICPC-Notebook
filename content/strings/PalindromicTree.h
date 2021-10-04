/**
 * Author: adamant
 * Date: 2020-10-28
 * License: CC0
 * Source: https://codeforces.com/blog/entry/13959
 * Description: Builds palindromic tree for a string.
 * Time: $O(N)$
 * Status: untested
 */
#pragma once

struct PalindromicTree {
  const static int N = 1e5, ALPHA = 26;
  int n, last, sz, s[N], len[N], link[N], to[N][ALPHA];
  PalindromicTree() {
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
  }
  int get_link(int v) {
    while (s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
  }
  void extend(int c) {
    s[n++] = c;
    last = get_link(last);
    if (!to[last][c]) {
      len [sz] = len[last] + 2;
      link[sz] = to[get_link(link[last])][c];
      to[last][c] = sz++;
    }
    last = to[last][c];
  }
};
