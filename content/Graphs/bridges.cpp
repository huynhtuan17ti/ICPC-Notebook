vector<int> G[MAXN];

int cnt = 0;
int low[MAXN], num[MAXN];
int numChild[MAXN], criVertex[MAXN], bridgeCnt = 0;

void DFS(int u, int pre) {
    num[u] = ++cnt;
    low[u] = INT_MAX;

    for(int v: G[u]) {
        if(v == pre) continue;
        if(num[v]) {
            low[u] = min(low[u], num[v]);
        }else {
            numChild[u]++;
            DFS(v, u);
            if(low[v] >= num[u]) criVertex[u] = 1;
            if(low[v] > num[u]) bridgeCnt++;
            low[u] = min(low[u], low[v]);
        }
    }
}

int main(){
    // input
    for(int i = 1; i <= n; i++)
        if(!num[i]) {
            DFS(i, 0);
            if(numChild[i] < 2)
                criVertex[i] = 0;
        }
    int criVertexCnt = 0;
    for(int i = 1; i <= n; i++)
        criVertexCnt += criVertex[i];
    cout << criVertexCnt << ' ' << bridgeCnt << '\n';
}