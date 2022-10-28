/*
    Find distinct numbers in a range (online query with persistent array)
*/
struct Node{
    int lnode, rnode;
    int sum;
    Node(){
        lnode = rnode = sum = 0;
    }
}ver[MAXN * 120];
int sz = 0;

int build_new_node(int l, int r){
    int next = ++sz;
    if(l != r){
        int mid = (l+r) >> 1;
        ver[next].lnode = build_new_node(l, mid);
        ver[next].rnode = build_new_node(mid+1, r);
    }
    return next;
}

int update(int cur, int l, int r, int pos, int val){
    int next = ++sz;
    ver[next] = ver[cur];
    if(l == r){
        ver[next].sum = val;
        return next;
    }
    else{
        int mid = (l+r) >> 1;
        if(pos <= mid)
            ver[next].lnode = update(ver[cur].lnode, l, mid, pos, val);
        else
            ver[next].rnode = update(ver[cur].rnode , mid+1, r, pos, val);
    }
    ver[next].sum = ver[ver[next].lnode].sum + ver[ver[next].rnode].sum;
    return next;
}

int get(int cur, int l, int r, int u, int v){
    if(r < u ||v < l)
        return 0;
    if(u <= l && r <= v){
        return ver[cur].sum;
    }
    int mid = (l+r) >> 1;
    return get(ver[cur].lnode, l, mid, u, v) + 
           get(ver[cur].rnode, mid+1, r, u, v);
}
