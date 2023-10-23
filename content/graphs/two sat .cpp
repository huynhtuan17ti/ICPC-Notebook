/**
 *  Given a set of clauses (a1 v a2)^(a2 v ¬a3)....
 *  this algorithm find a solution to it set of clauses.
 *  test: http://lightoj.com/volume_showproblem.php?problem=1251
 **/

vector<int> G[MAXN];
vector<int> Gv2[MAXN];

int low[MAXN], num[MAXN];
int cntTime = 0, cntSCC = 0, SCC[MAXN];
vector<int> inSCC[MAXN];
stack<int> st;
queue<int> q;
// storing topo order with queue instead of stack
// because we need to go from back to begin of topo order

void DFS(int u) {
    low[u] = num[u] = ++cntTime;
    st.push(u);
    for (int v : G[u])
        if (num[v])
            low[u] = min(low[u], num[v]);
        else {
            DFS(v);
            low[u] = min(low[u], low[v]);
        }
    if (low[u] == num[u]) {
        int v;
        cntSCC++;
        do {
            v = st.top();
            st.pop();
            SCC[v] = cntSCC;
            inSCC[cntSCC].push_back(v);
            low[v] = num[v] = INT_MAX;
        } while (u != v);
    }
}

void DFS_topo(int u) {
    num[u] = 1;
    for (int v : Gv2[u])
        if (!num[v])
            DFS_topo(v);
    q.push(u);
}

int main() {
    int n, m;
    cin >> m >> n;
    auto getNot = [&](int u) -> int {
        if (u > n)
            return u - n;
        return u + n;
    };

    while (m--) {
        char c1, c2;
        int u, v;
        cin >> c1 >> u >> c2 >> v;
        if (c1 == '-')
            u += n;
        if (c2 == '-')
            v += n;
        // add (-v -> u) and (-u -> v)
        G[getNot(u)].push_back(v);
        G[getNot(v)].push_back(u);
    }

    // using tarjan's algorithm to find SCC.
    for (int i = 1; i <= 2 * n; i++)
        if (!num[i])
            DFS(i);

    vector<int> notSCC(2 * n + 1);

    // check if exist u and -u are in the same component
    for (int i = 1; i <= n; i++)
        if (SCC[i] == SCC[i + n])
            return cout << "IMPOSSIBLE", 0;
        else {
            // store the opposite component.
            notSCC[SCC[i]] = SCC[i + n];
            notSCC[SCC[i + n]] = SCC[i];
        }

    // build new graph
    for (int i = 1; i <= 2 * n; i++)
        for (int v : G[i])
            if (SCC[i] != SCC[v]) {
                Gv2[SCC[i]].push_back(SCC[v]);
            }

    // topological sort
    fill(num + 1, num + 1 + 2 * n, 0);
    for (int i = 1; i <= cntSCC; i++)
        if (!num[i])
            DFS_topo(i);

    vector<int> ansSCC(2 * n + 1, -1);
    vector<int> ans(2 * n + 1, 0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (ansSCC[u] == -1) { // not pick
            // if u = 1 then -u must be 0
            ansSCC[u] = 1;
            ansSCC[notSCC[u]] = 0;
        }

        // set value of all nodes in the current SCC
        for (int v : inSCC[u]) {
            ans[v] = ansSCC[u];
        }
    }

    for (int i = 1; i <= n; i++)
        cout << ((ans[i]) ? '+' : '-') << ' ';
}