const int dim = 10;

struct matrix {
    vector<vector<long long>> a;
    matrix() {
        a.resize(dim);
        for (int i = 1; i < dim; i++)
            a[i].resize(dim, 0);
    }
};

matrix Identity() {
    matrix A;
    for (int i = 1; i < dim; i++)
        A.a[i][i] = 1;
    return A;
}

matrix operator*(const matrix &A, const matrix &B) {
    matrix mul;
    for (int k = 1; k < dim; k++)
        for (int i = 1; i < dim; i++)
            for (int j = 1; j < dim; j++)
                mul.a[i][j] += A.a[i][k] * B.a[k][j];
    return mul;
}

matrix fastPow(matrix A, long long b) {
    if (b == 0)
        return Identity();
    if (b == 1)
        return A;
    matrix t = fastPow(A, b / 2);
    t = t * t;
    if (b % 2 == 1)
        t = t * A;
    return t;
}