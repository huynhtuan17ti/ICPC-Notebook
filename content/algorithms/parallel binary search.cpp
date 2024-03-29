int lo[N], mid[N], hi[N];
vector<int> vec[N];

// Reset
void clear() {
  memset(bit, 0, sizeof(bit));
}

// Apply ith update/query
void apply(int idx) {
  if (ql[idx] <= qr[idx])
    update(ql[idx], qa[idx]), update(qr[idx] + 1, -qa[idx]);
  else {
    update(1, qa[idx]);
    update(qr[idx] + 1, -qa[idx]);
    update(ql[idx], qa[idx]);
  }
}

// Check if the condition is satisfied
bool check(int idx) {
  int req = reqd[idx];
  for (auto& it : owns[idx]) {
    req -= pref(it);
    if (req < 0)
      break;
  }
  if (req <= 0)
    return 1;
  return 0;
}

void work() {
  for (int i = 1; i <= q; i++)
    vec[i].clear();
  for (int i = 1; i <= n; i++)
    if (mid[i] > 0)
      vec[mid[i]].push_back(i);
  clear();
  for (int i = 1; i <= q; i++) {
    apply(i);
    for (auto& it : vec[i])  // Add appropriate check conditions
    {
      if (check(it))
        hi[it] = i;
      else
        lo[it] = i + 1;
    }
  }
}

void parallel_binary() {
  for (int i = 1; i <= n; i++)
    lo[i] = 1, hi[i] = q + 1;
  bool changed = 1;
  while (changed) {
    changed = 0;
    for (int i = 1; i <= n; i++) {
      if (lo[i] < hi[i]) {
        changed = 1;
        mid[i] = (lo[i] + hi[i]) / 2;
      } else
        mid[i] = -1;
    }
    work();
  }
}