template <typename T>
class FenwickTree{
  vector <T> fenw;
  int n;
public:
  void initialize(int _n){
    this->n = _n;
    fenw.resize(n+1);
  }

  void update(int id, T val) {
    while (id <= n) {
      fenw[id] += val;
      id += id&(-id);
      }
  }

  T get(int id){
    T ans{};
    while(id >= 1){
      ans += fenw[id];
      id -= id&(-id); 
    }
    return ans;
  }
};