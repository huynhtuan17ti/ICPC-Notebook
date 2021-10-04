/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: cp-algorithms
 * Description: Builds suffix automaton for a string.
 * Time: $O(N)$
 * Status: stress-tested
 * Usage: SuffixAutomaton sa; for(char c : s) sa.extend(c - 'a');
 *  1. Number of distinct substr:
 *     - Find number of different paths -> DFS on SA
 *     - f[u] = 1 + sum(f[v]) for v in nxt[u]
 *  2. Number of occurrences of a substr:
 *     - Initially, in extend: cnt[cur] = 1; cnt[clone] = 0;
 *     - Sort order by decreasing len
 *     - for (p in order)
 *         cnt[link[p.second]] += cnt[p.second]
 *  3. Find total length of different substrings:
 *     - We have f[u] = number of strings starting from node u
 *     - ans[u] = sum(ans[v] + d[v]) for v in nxt[u]
 *  4. Lexicographically k-th substring
 *     - Based on number of different substring
 *  5. Smallest cyclic shift
 *     - Build SA of S+S, then just follow smallest link
 *  6. Find first occurrence
 *     - firstpos[cur] = len[cur] - 1, firstpos[clone] = firstpos[q]
 */
#pragma once

struct SuffixAutomaton {
  const static int N = 2e6 + 666;
  int sz, last, len[N], link[N], nxt[N][33];
  //vector<pii> order;
  SuffixAutomaton() {
    len[0] = 0;
    link[0] = -1;
    memset(nxt[0], 0, sizeof(nxt[0]));
    sz = 1; last = 0;
  }
  void extend(int c) {
    int cur = sz++, p;
    len[cur] = len[last] + 1;
    memset(nxt[cur], 0, sizeof(nxt[cur]));
    //order.emb(len[cur], cur);
    for (p = last; p != -1 && !nxt[p][c]; p = link[p])
      nxt[p][c] = cur;
    if (p == -1) link[cur] = 0;
    else {
      int q = nxt[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int clone = sz++;
        len[clone] = len[p] + 1;
        link[clone] = link[q];
        memcpy(nxt[clone], nxt[q], sizeof(nxt[q]));
        //order.emb(len[clone], clone);
        for (; p != -1 && nxt[p][c] == q; p = link[p])
          nxt[p][c] = clone;
        link[q] = link[cur] = clone;
      }
    }
    last = cur;
  }
};
