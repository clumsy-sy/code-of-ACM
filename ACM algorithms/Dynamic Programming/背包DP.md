# 背包 DP
## 0 - 1 背包
$$
    f_{j} = \max (f_{j}, f_{j - w_{i}} + v_{i})
$$

```cpp
const int M = 1e5 + 7;
int w[M], v[M], dp[M];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++) 
        scanf("%d%d", &w[i], &v[i]);

    for(int i = 1; i <= n; i ++)
        for(int j = m; j >= w[i]; j --)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    printf("%d\n", dp[m]);
    return 0;
}
```
## 完全背包
$$
f_{i,j} = \max (f_{i-1,j}, f_{i, j-w_{i}} + v_{i})
$$
```cpp
const int M = 1e7 + 7;
int w[M], v[M];
ll dp[M];

int main() {
    int n, m;
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; i ++) 
        scanf("%d%d", &w[i], &v[i]);

    for(int i = 1; i <= n; i ++)
        for(int j = w[i]; j <= m; j ++)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    printf("%lld\n", dp[m]);
    return 0;
}
```

## 多重背包
$$
f_{i,j} = \max_{k=0}^{k_{i}}(f_{i-1,j-k\times w_{i}} + v_{i}\times k)
$$
### 二进制优化
将一个数 $n$ 二进制分组后，我们可以用这些组之间的组合得到 $1 \dots n$ 之间的任意一个数，那么就转化成了 0 - 1 背包问题
```cpp
const int M = 1e6 + 7;
int w[M], v[M], dp[M], idx = 1;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        int val, wei, x;
        scanf("%d%d%d", &val, &wei, &x);
        for(int j = 1; x >= j; j <<= 1, idx ++) { //二进制拆分
            v[idx] = j * val;
            w[idx] = j * wei;
            x -= j;
        }
        if(x) {
            v[idx] = x * val;
            w[idx ++] = x * wei;
        }
    }
    //0 - 1 背包
    for(int i = 1; i < idx; i ++)
        for(int j = m; j >= w[i]; j --)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    printf("%d\n", dp[m]);
    return 0;
}
```
### 单调队列优化
假设 
$$
d = j \mod w_{i}, s = \left \lfloor \dfrac{j}{w_{i}} \right \rfloor 
$$
得到可单调队列的转移方程
$$
f_{i, j} = \max (f_{i-1, \  d + w_{i} \times k} + v_{i} \times s ), s - k \leqslant c 
$$
```cpp
const int N = 1e4 + 7, M = 2e5 + 7;

int v[N], w[N], s[N];
int dp[2][M], q[M];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) scanf("%d%d%d", &w[i], &v[i], &s[i]);
    for (int i = 1; i <= n; ++ i)
        for (int r = 0; r < v[i]; ++ r)
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= m; j += v[i])
            {
                while (hh <= tt && j - q[hh] > s[i] * v[i]) hh ++ ;
                while (hh <= tt && dp[(i - 1) & 1][q[tt]] + (j - q[tt]) / v[i] * w[i] <= dp[(i - 1) & 1][j]) -- tt;
                q[ ++ tt] = j;
                dp[i & 1][j] = dp[(i - 1) & 1][q[hh]] + (j - q[hh]) / v[i] * w[i];
            }
        }
    printf("%d\n", dp[n & 1][m]);
    return 0;
}
```
## 混合背包
由 0 - 1 背包， 完全背包，多重背包组合而成，只需要根据物品情况不同，分别处理即可
```cpp
const int M = 1e3 + 7;
int dp[M];

int main() {
    int n, m, hh1, mm1, hh2, mm2;
    scanf("%d:%d %d:%d %d", &hh1, &mm1, &hh2, &mm2, &n);
    m = (hh2 - hh1) * 60 + (mm2 - mm1);

    for(int i = 1; i <= n; i ++) {
        int t, v, p;
        scanf("%d%d%d", &t, &v, &p);
        if(p == 0) {
            for(int j = t; j <= m; j ++)
                dp[j] = max(dp[j], dp[j - t] + v);
        } else {
            for(int k = 1; p >= k; k <<= 1) {
                int nowt = k * t, nowv = k * v;
                for(int j = m; j >= nowt; j --)
                    dp[j] = max(dp[j], dp[j - nowt] + nowv);
                p -= k;
            }
            if(p) {
                int nowt = p * t, nowv = p * v;
                for(int j = m; j >= nowt; j --)
                    dp[j] = max(dp[j], dp[j - nowt] + nowv);
            }
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}
```
## 二维费用背包
与 0 - 1 背包相似，只需要多加一维来进行状态转移即可。
```cpp
const int M = 211;

int m[M], t[M], dp[M][M];

int main() {
    int n, M, T;
    scanf("%d%d%d", &n, &M, &T);
    for(int i = 1; i <= n; i ++)
        scanf("%d%d", &m[i], &t[i]);
    
    for(int i = 1; i <= n; i ++)
        for(int j = M; j >= m[i]; j --)
            for(int k = T; k >= t[i]; k --)
                dp[j][k] = max(dp[j][k], dp[j - m[i]][k - t[i]] + 1);
    printf("%d\n", dp[M][T]);
    return 0;
}
```
## 分组背包
相当于每组至多取一个，遍历各组，遍历背包容量（从大到小），再遍历每组物品才能保证每组最多取一个
```cpp
const int M = 1e5 + 7;

vector<int> vec[M];
int w[M], v[M], dp[M];

int main() {
    int n, m, x, cnt = 0;
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d%d", &w[i], &v[i], &x);
        vec[x].push_back(i);
        cnt = max(cnt, x);
    }

    for(int i = 1; i <= cnt; i ++)
        for(int j = m; j >= 0; j --)
            for(int k = 0; k < (int)vec[i].size(); k ++)
                if(j >= w[vec[i][k]])
                    dp[j] = max(dp[j], dp[j - w[vec[i][k]]] + v[vec[i][k]]);
    printf("%d\n", dp[m]);

    return 0;
}
```

## 有依赖的背包
例题[P1064](https://www.luogu.com.cn/problem/P1064)
有依赖就是选某件物品的同时必须要选另外的一件物品，依赖关系就构成了一棵树，树上的每一个结点就是一种符合条件的选择情况，每一棵树又可以看作一组，组内最多只能选取一个结点，这样问题就转换成了分组背包。
```cpp
typedef pair<int, int> PII;
const int M = 1e5 + 7;
 
vector<PII> vec[100];
int dp[M];

int main() {
    int n, m, w, v, x;
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d%d", &w, &v, &x);
        if(x == 0)
            vec[i].push_back({w, w * v}); //树上结点应当直接存后面需要dp的值
        else {
            for(int j = vec[x].size() - 1; j >= 0; j --) { //更新每棵树可行的节点
                PII now = vec[x][j];
                vec[x].push_back({now.first + w, now.second + w * v});
            }
        }
    }
    //分组背包
    for(int i = 1; i <= n; i ++) 
        for(int j = m; j >= 0; j --)
            for(int k = 0; k < (int)vec[i].size(); k ++)
                if(j >= vec[i][k].first)
                    dp[j] = max(dp[j], dp[j - vec[i][k].first] + vec[i][k].second);
    printf("%d\n", dp[m]);

    return 0;
}
```

