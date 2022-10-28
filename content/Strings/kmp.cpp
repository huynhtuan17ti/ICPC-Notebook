/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends
 * at x, other than s[0...x] itself (abacaba -> 0010123). Can be used to find
 * all occurrences of a string. 
 * Time: O(n) Status:
 */
#pragma once

vi pi(const string &s) {
    vi p(sz(s));
    rep(i, 1, sz(s)) {
        int g = p[i - 1];
        while (g && s[i] != s[g])
            g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}
void compute_automaton(const string &s, vector<vi> &aut) {
    vi p = pi(s);
    aut.assign(sz(s), vi(26));
    rep(i, 0, sz(s)) rep(c, 0, 26) if (i > 0 && s[i] != 'a' + c) aut[i][c] =
        aut[p[i - 1]][c];
    else aut[i][c] = i + (s[i] == 'a' + c);
}
vi match(const string &s, const string &pat) {
    vi p = pi(pat + '\0' + s), res;
    rep(i, sz(p) - sz(s), sz(p)) if (p[i] == sz(pat)) res.emb(i - 2 * sz(pat));
    return res;
}