/**
 * Author: Arpa
 * Date: 2020-10-28
 * License: CC0
 * Source: https://codeforces.com/blog/entry/43718
 * Description: Iterate bitset in O(n / 32)
 * Status: untested
 */
#pragma once

for (int i = b._Find_first(); i < sz(b); i = b._Find_next(i)) {
  cout << i << endl;
}
