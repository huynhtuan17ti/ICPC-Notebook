/**
 * Author: Le Bao Hiep
 * Date: 2020-10-27
 * License: CC0
 * Description: Generate all primes and calculate Mobius/Euler's totient
 * function for numbers smaller than N
 * Time: $O(N)$
 * Status: untested
 */
#pragma once

const int N = 10000000;
int lp[N + 1], phi[N + 1], mu[N + 1];
vector<int> pr;
void linearSieve() {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      pr.emplace_back(i);
      lp[i] = i; phi[i] = i - 1; mu[i] = -1;
    }
    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] < lp[i]) {
        phi[i * pr[j]] = phi[i] * phi[pr[j]];
        mu[i * pr[j]] = mu[i] * mu[pr[j]];
      } else {
        phi[i * pr[j]] = phi[i] * pr[j];
        mu[i * pr[j]] = 0;
      }
    }
  }
}
