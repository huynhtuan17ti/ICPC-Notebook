#define long long long
#define pll pair <long, long>
#define all(c) c.begin(), c.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(0)
 
struct line{
    long a, b;
    line() {};
    line(long a, long b) : a(a), b(b) {};
    bool operator < (const line &A) const {
		return pll(a,b) < pll(A.a,A.b);
	}
};
 
bool bad(line A, line B, line C){
    return (C.b - B.b) * (A.a - B.a) <= (B.b - A.b) * (B.a - C.a);
}
 
void addLine(vector<line> &memo, line cur){
    int k = memo.size();
    while (k >= 2 && bad(memo[k - 2], memo[k - 1], cur)){
        memo.pop_back();
        k--;
    }
    memo.push_back(cur);
}
 
long Fn(line A, long x){
    return A.a * x + A.b;
}
 
long query(vector<line> &memo, long x){
    int lo = 0, hi = memo.size() - 1;
    while (lo != hi){
        int mi = (lo + hi) / 2;
        if (Fn(memo[mi], x) > Fn(memo[mi + 1], x)){
            lo = mi + 1;
        }
        else hi = mi;
    }
    return Fn(memo[lo], x);
}
 
const int N = 1e6 + 1;
long dp[N];
 
int main()
{
    fastio;
    int n, c; cin >> n >> c;
    vector<line> memo;
    for (int i = 1; i <= n; i++){
        long val; cin >> val;
        addLine(memo, {-2 * val, val * val + dp[i - 1]});
        dp[i] = query(memo, val) + val * val + c;
    }    
    cout << dp[n] << '\n';
    return 0;
}