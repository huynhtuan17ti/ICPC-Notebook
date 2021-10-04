/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Add integers and query median
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct MedianHeap {
  priority_queue<int> minPQ, maxPQ;
  bool empty() { return minPQ.empty(); }
  int top() { return -minPQ.top(); }
  int pop() {
    if (minPQ.empty()) return -1;
    int m = -minPQ.top(); minPQ.pop();
    if (minPQ.size() < maxPQ.size()) {
      minPQ.push(-maxPQ.top());
      maxPQ.pop();
    }
    return m;
  }
  void push(int c) {
    if (!minPQ.empty() && c > -minPQ.top()) {
      minPQ.push(-c);
      if (minPQ.size() > maxPQ.size() + 1) {
        maxPQ.push(-minPQ.top());
        minPQ.pop();
      }
    } else {
      maxPQ.push(c);
      if (maxPQ.size() > minPQ.size()) {
        minPQ.push(-maxPQ.top());
        maxPQ.pop();
      }
    }
  }
};
