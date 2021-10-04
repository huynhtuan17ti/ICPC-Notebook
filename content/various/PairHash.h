/**
 * Author: hieplpvip
 * Date: 2020-10-27
 * License: CC0
 * Source: own work
 * Description: Allow using pair with hash-based containers
 * Status: untested
 */
#pragma once

namespace std {
  template<>
  struct hash<pair<int,int>> {
  public:
    size_t operator()(const pair<int,int>& x) const {
      return 1000000009LL * x.first + x.second;
    }
  };
}
