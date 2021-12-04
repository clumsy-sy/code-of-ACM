int n, S[300009];
int Min_show() {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (S[(i + k) % n] == S[(j + k) % n])
            k ++;
        else {
            if (S[(i + k) % n] > S[(j + k) % n])
                i += k + 1;
            else
                j += k + 1;
            if (i == j)
                i++;
            k = 0;
        }
    }
    return min(i, j); //返回最小表示
}