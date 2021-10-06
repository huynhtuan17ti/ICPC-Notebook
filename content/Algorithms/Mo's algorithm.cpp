/*
    https://www.spoj.com/problems/FREQ2/
*/
vector <int> MoQueries(int n, vector <query> Q){

    block_size = sqrt(n);
    sort(Q.begin(), Q.end(), [](const query &A, const query &B){
        return (A.l/block_size != B.l/block_size)? (A.l/block_size < B.l/block_size) : (A.r < B.r);
    });
    vector <int> res;
    res.resize((int)Q.size());

    int L = 1, R = 0;
    for(query q: Q){
        while (L > q.l) add(--L);
        while (R < q.r) add(++R);

        while (L < q.l) del(L++);
        while (R > q.r) del(R--);
        
        res[q.pos] = calc(1, R-L+1);
    }
    return res;
}
