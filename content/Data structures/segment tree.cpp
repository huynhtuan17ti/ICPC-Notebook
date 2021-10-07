// Problem: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B
struct SegmentTree {
#define m ((l + r) >> 1)
#define lc (i << 1)
#define rc (i << 1 | 1)
    vector<int> mn;
    int n;

    SegmentTree(int n = 0) : n(n){    
        mn.resize(4 * n + 1, 0);
    }

    SegmentTree(const vector<int> &a) : n(a.size()) {
        mn.resize(4 * n + 1, 0);
        function<void(int, int, int)> build = [&](int i, int l, int r){
            if (l == r){
                mn[i] = a[l - 1];
                return;
            }
            build(lc, l, m); build(rc, m + 1, r);
            mn[i] = min(mn[lc], mn[rc]);
        };
        build(1, 1, n);
    }

    void update(int i, int l, int r, int p, long val){
        if (l == r){
            mn[i] = val;
            return;
        }  
        if (p <= m) update(lc, l, m, p, val); 
        else update(rc, m + 1, r, p, val);
        mn[i] = min(mn[lc], mn[rc]);
    }
    
    int get(int i, int l, int r, int u, int v){
        if (v < l || r < u) return INF;
        if (u <= l && r <= v) return mn[i];
        return min(get(lc, l, m, u, v), get(rc, m + 1, r, u, v));
    }

    void update(int p, long val){
        update(1, 1, n, p, val);
    }

    int get(int l, int r){
        return get(1, 1, n, l, r);
    }
#undef m
#undef lc
#undef rc  
};


// Problem: There are two operations:
// 1 l r val: add the value val to the segment from l to r
// 2 l v: calculate the minimum of elements from l to r
struct LazySegmentTree {
#define m ((l + r) >> 1)
#define lc (i << 1)
#define rc (i << 1 | 1)
    vector<int> mn, lazy;
    int n;

    LazySegmentTree(int n = 0) : n(n){
        mn.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, 0);    
    }

    void push(int i, int l, int r){
        if (lazy[i] == 0) return;
        mn[i] += lazy[i];
        if (l != r){
            lazy[lc] += lazy[i];
            lazy[rc] += lazy[i];
        }  
        lazy[i] = 0;
    }

    void update(int i, int l, int r, int u, int v, int val){
        push(i, l, r);
        if (v < l || r < u) return;
        if (u <= l && r <= v){
            lazy[i] += val;
            push(i, l, r);
            return;
        }  
        update(lc, l, m, u, v, val); update(rc, m + 1, r, u, v, val);
        mn[i] = min(mn[lc], mn[rc]);
    }

    int get(int i, int l, int r, int u, int v){
        push(i, l, r);
        if (v < l || r < u) return INF;
        if (u <= l && r <= v) return mn[i];
        return min(get(lc, l, m, u, v), get(rc, m + 1, r, u, v));
    }

    void update(int l, int r, int val){
        update(1, 1, n, l, r, val);
    }

    int get(int l, int r){
        return get(1, 1, n, l, r);
    }
#undef m
#undef lc
#undef rc  
};