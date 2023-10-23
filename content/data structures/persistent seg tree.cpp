/* Problem: https://cses.fi/problemset/task/1737/
 * Your task is to maintain a list of arrays which initially has a single array. You have to process the following types of queries:
 * Query 1: Set the value a in array k to x.
 * Query 2: Calculate the sum of values in range [a,b] in array k.
 * Query 3: Create a copy of array k and add it to the end of the list.
 * Idea to create a persistent segment tree to save all version of array.
*/

vector<int> a;

struct Node {
  int val;
  Node *left, *right;
  Node() {
    left = right = NULL;
    val = 0;
  }
  Node(Node* l, Node* r, int v) {
    left = l;
    right = r;
    val = v;
  }
};

void build(Node*& cur, int l, int r) {
  if (l == r) {
    cur->val = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  cur->left = new Node();
  cur->right = new Node();
  build(cur->left, l, mid);
  build(cur->right, mid + 1, r);
  cur->val = cur->left->val + cur->right->val;
}

void update(Node* prev, Node*& cur, int l, int r, int i, int val) {
  if (i < l || r < i)
    return;
  if (l == r && l == i) {
    cur->val = val;
    return;
  }
  int mid = (l + r) >> 1;
  if (i <= mid) {
    cur->right = prev->right;
    cur->left = new Node();
    update(prev->left, cur->left, l, mid, i, val);
  } else {
    cur->left = prev->left;
    cur->right = new Node();
    update(prev->right, cur->right, mid + 1, r, i, val);
  }
  cur->val = cur->left->val + cur->right->val;
}

int get(Node* cur, int l, int r, int u, int v) {
  if (v < l || r < u)
    return 0;
  if (u <= l && r <= v) {
    return cur->val;
  }
  int mid = (l + r) >> 1;
  int L = get(cur->left, l, mid, u, v);
  int R = get(cur->right, mid + 1, r, u, v);
  return L + R;
}

Node* ver[MAXN];
