#include <iostream>
#include <vector>
using namespace std;
const int N = 5010;
int sum[N]; //每一个质数的次数
int primes[N], cnt;
bool st[N];
void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
vector<int> mul(vector<int> a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) { c.push_back(t % 10); t /= 10; }
    return c;
}
int get(int n, int p) {
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    get_primes(n);
    //遍历每一个质数,求每个质数的次数
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        sum[i] = get(n, p) - get(n - m, p) - get(m, p); //约掉因子
    }
    vector<int> res;
    res.push_back(1);
    for (int i = 0; i < cnt; i++)        //遍历每一个质数因子
        for (int j = 0; j < sum[i]; j++) //开始乘以它的个数
            res = mul(res, primes[i]);
    for (int i = res.size() - 1; i >= 0; i--)
        printf("%d", res[i]);
    return 0;
}