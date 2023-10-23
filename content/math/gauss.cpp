const int inf = 1e9;
const double eps = 1e-6;

/*
 * Input:
 *      a: the coefficients of the system
 *      ans: storing answer
 * Output:
 *      The number of roots
*/
int gauss(vector<vector<double>> a, vector<double>& ans) {
  int n = (int)a.size();
  int m = (int)a[0].size() - 1;

  vector<int> where(m, -1);

  for (int col = 0, row = 0; col < m && row < n; col++) {
    // Choosing the pivot row is done with heuristic:
    // choosing maximum value in the current column
    int pivot = row;
    for (int i = row; i < n; i++)
      if (abs(a[i][col]) > abs(a[pivot][col]))
        pivot = i;

    for (int i = col; i <= m; i++)
      swap(a[pivot][i], a[row][i]);
    where[col] = row;

    for (int i = 0; i < n; i++)
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; j++)
          a[i][j] -= a[row][j] * c;
      }
    row++;
  }

  ans.assign(m, 0);
  for (int i = 0; i < m; i++)
    if (where[i] != -1)
      ans[i] = a[where[i]][m] / a[where[i]][i];

  // calculate the number of roots by re-checking the system of equations.
  for (int i = 0; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < m; j++)
      sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > eps)
      return 0;
  }

  for (int i = 0; i < m; i++)
    if (where[i] == -1)
      return inf;

  return 1;
}
