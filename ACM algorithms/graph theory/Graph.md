# 图论
## 最短路算法
### Dijkstra 算法
适用于：稠密图（边>>点）复杂度O（n^2）//也可求任一点，只需改dist[i] = 0,并返回dist[j];
```cpp
const int M = 507;
int g[M][M], dist[M], n, m, idx;
bool st[M]; //存是否判断过该
int Dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for (int i = 1; i <= n; i++) {
        idx = -1;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (idx == -1 || dist[idx] > dist[j]))
                idx = j;
        }
        st[idx] = 1; //标记
        for (int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], dist[idx] + g[idx][j]);
        }
    }
    if (dist[n] == INF) return -1;
    else return dist[n];
}
int main() {
    memset(g, 0x3f, sizeof g);
    cin >> n >> m;
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        g[x][y] = min(g[x][y], w); //重边取最小权重
    }
    cout << Dijkstra() << endl;
    return 0;
}
```
适用于：稀疏图，复杂度(STL优先队列)O(mlogm);  手写堆O(mlogn), 
适合边较多的图，基于贪心思想
```cpp
typedef pair<int, int> pll;
const int M = 2510;
const int N = 6300;
int head[M], dist[M], n, c, start, endn, idx;
bool st[N];

struct Edge {
    int to, w, nxt;
    Edge(int to = 0, int w = 0, int nxt = 0) : to(to), w(w), nxt(nxt) {
    }
} edge[N * 2];

void init() {
    memset(dist, 0x3f, sizeof dist);
    memset(head, -1, sizeof head);
    idx = 0;
}
void add(int u, int v, int w) {
    edge[idx] = Edge(v, w, head[u]);
    head[u] = idx++;
}
int Dijkstra() {
    priority_queue<pll, vector<pll>, greater<pll>> heap;
    heap.push({0, start}); // first 存路径长度， second 存点（默认按first排序）
    while (heap.size()) {
        pll t = heap.top(); //每次只取最小的边
        heap.pop();
        int dis = t.first, ver = t.second;
        if (st[ver]) continue;
        st[ver] = 1;
        for (int i = head[ver]; i != -1; i = edge[i].nxt) {
            int j = edge[i].to;
            if (dist[j] > edge[i].w + dis) {
                dist[j] = edge[i].w + dis;
                heap.push({dist[j], j});
            }
        }
    }
    return dist[endn];
}
int main() {
    init();
    cin >> n >> c >> start >> endn;
    while (c--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    cout << Dijkstra() << endl;
    return 0;
}
```

小根堆 `priority_queue<>` 的重载
```cpp
struct cmp {
    bool operator()(P a, P b) { // 重载()运算符，使其成为一个仿函数
        return a.dist > b.dist; // 这里是大于，使得距离短的先出队
    }
};
```
### Bellman-ford算法

适用于有边数限制的最短路，复杂度O(n^2);非常暴力
```cpp
const int N = 510, M = 10010;
int n, m, k;
int dist[N], backup[N];
struct Edge {
    int a, b, w;
} edges[M];
int bellman_ford() {
    memset(dist, 0x3f, sizeof dist); //初始化
    dist[1] = 0;
    for (int i = 0; i < k; i++) {// k次更新
        memcpy(backup, dist, sizeof dist); //复制数组，防止串联效应
        for (int j = 0; j < m; j++) {      //遍历所有边
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            dist[b] = min(dist[b], backup[a] + w); //更新最短路径
        }
    }
    if (dist[n] > 0x3f3f3f3f / 2)
        return -1; //防止在某些情况下因为更新导致最后一点不能到达但可能略小于0x3f3f3f3f
    return dist[n];
}
int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }
    int t = bellman_ford();
    if (t == -1)
        cout << "impossible" << endl;
    else
        cout << t << endl;
    return 0;
}
```
### SPFA 求最短路
SPFA 已死！
复杂度（最坏）O（n^m）效率较高且可解决所有单源最短路问题，可求负环。
```cpp
typedef pair<int, int> pll;
const int M = 2510;
const int N = 6300;
int head[M], dist[M], n, c, start, endn, idx;
bool st[N];

struct Edge {
    int to, w, nxt;
    Edge(int to = 0, int w = 0, int nxt = 0) 
    : to(to), w(w), nxt(nxt) {}
} edge[N * 2];

void init() {
    memset(dist, 0x3f, sizeof dist);
    memset(head, -1, sizeof head);
}
void add(int u, int v, int w) {
    edge[idx] = Edge(v, w, head[u]);
    head[u] = idx++;
}
void SPFA() {
    queue<int> q;
    q.push(start);
    st[start] = 0;
    dist[start] = 0; //初始化，必须要把起点的dist定义为0
    while (q.size()) {
        int t = q.front();
        q.pop();
        st[t] = 0;
        for (int i = head[t]; i != -1; i = edge[i].nxt) {
            int k = edge[i].to;
            if (dist[k] > dist[t] + edge[i].w) {
                dist[k] = dist[t] + edge[i].w; //寻找最短路
                if (!st[k]) { //仅仅代表可以走向这条边，在此处判断了重边
                 //防止串联效应，可以走到就置1，但路径只存最短路
                    q.push(k);
                    st[k] = 1;
                }
            }
        }
    } //有可能走不到该点
}
int main() {
    init();
    cin >> n >> c >> start >> endn;
    while (c--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    SPFA();
    cout << dist[endn] << endl;
    return 0;
}
```
### SPFA 判负环
通过抽屉原理用SPFA判负环（任意路线的负环不一定过1）

```cpp
const int M = 1e5 + 7;
struct Edge {
    int to, w, nxt;
    Edge(int to = 0, int w = 0, int nxt = 0) 
    : to(to), w(w), nxt(nxt) {}
} edge[M * 2];
// cnt数组记录到当前点最短路的边数
int head[M], dist[M], cnt[M], n, m, idx; 
bool st[M];
void add(int u, int v, int w) {
    edge[idx] = Edge(v, w, head[u]);
    head[u] = idx++;
}
void init() {
    memset(head, -1, sizeof head);
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
}
bool spfa() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        st[i] = 1;
        q.push(i);
    } //判整个图的负环要将每个节点都加入
    while (q.size()) {
        int t = q.front();
        q.pop();
        st[t] = 0;
        for (int i = head[t]; ~i; i = edge[i].nxt) {
            int k = edge[i].to;
            if (dist[k] > dist[t] + edge[i].w) {
                dist[k] = dist[t] + edge[i].w;
                cnt[k] = cnt[t] + 1; //边数更新
                if (cnt[k] >= n)
                    return 1; //根据抽屉原理，当经过的边数等于点数时一定出现负环
                if (!st[k]) {
                    q.push(k);
                    st[k] = 1;
                }
            }
        }
    }
    return 0;
}
int main() {
    cin >> n >> m;
    init();
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    if (spfa())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
```

### Floyd 算法
适用于多源最短路问题，任意点之间的最短询问。复杂度O(n^3),基于动态规划算法

```cpp
const int N = 210;
int n, m, k, x, y, w;
int d[N][N];
void Floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main() {
    cin >> n >> m >> k;
    memset(d, 0x3f, sizeof d);   //初始化
    for (int i = 1; i <= n; i ++) //自环为路长度0
        d[i][i] = 0;
    while (m--) {
        cin >> x >> y >> w;
        d[x][y] = min(d[x][y], w); //只保留最小的边
    }
    Floyd();
    while (k--) {
        cin >> x >> y;
        //状态改变时，由于存在负权路，所以可能使路径长度小于INF
        if (d[x][y] > INF / 2) cout << "impossible" << endl; 
        else cout << d[x][y] << endl;
    }
    return 0;
}
```

### 最短路算法小结
Dijkstra-朴素 $O(n^2)$
1. 初始化距离数组, dist[1] = 0, dist[i] = inf;
2. for n次循环每次循环确定一个min加入S集合中，n次之后就得出所有的最短距离
3. 将不在S中dist_min的点->t
4. t->S加入最短路集合
5. 用t更新到其他点的距离

Dijkstra-堆优化 $O(mlogm)$
1．利用邻接表，优先队列
2. 在priority_queue中将返回堆顶
3. 利用堆顶来更新其他点，并加入堆中类似宽搜

Bellman_ford $O(n\times n)$
1. 注意连锁想象需要备份, struct Edge{inta,b,c} Edge[M];
2. 初始化dist, 松弛dist[x.b] = min(dist[x.b], backup[x.a]+x.w);
3. 松弛k次，每次访问m条边

Spfa $O(n) ~ O(nm)$
1．利用队列优化仅加入修改过的地方
2.for k次
3.for 所有边利用宽搜模型去优化bellman_ford算法
4.更新队列中当前点的所有出边

Floyd $O(n^3)$
1.初始化 d
2.k, i, j 去更新 d

## 最小生成树算法
### Prim 算法
将无向图变成一个最小生成树（集合）适用于稠密图

```cpp
const int M = 510;
int g[M][M], dist[M], n, m;
bool st[M];
int Prim() {
    memset(dist, 0x3f, sizeof dist);
    int res = 0;
    dist[1] = 0;
    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (idx == -1 || dist[idx] > dist[j]))
                idx = j; //每次选取离集合最近的点
        }
        if (i && dist[idx] == INF)
            return INF; //如果这个点最小值是INF那说明是不连通的，说明没有最小生成树
        if (i) res += dist[idx]; //最小生成树的总长
        st[idx] = 1;
        for (int j = 1; j <= n; j++)
            if (!st[j])
                dist[j] = min(dist[j], g[idx][j]); //更新到现存树的最短距离（权重）
    }
    return res;
}
int main() {
    memset(g, 0x3f, sizeof g);
    cin >> n >> m;
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        g[x][y] = g[y][x] = min(g[x][y], w);
    }
    int ans = Prim();
    if (ans == INF)
        cout << "impossible" << endl;
    else
        cout << ans << endl;
    return 0;
}
```

### Kruskal 算法
适用于稀疏图求最小生成树
```cpp
const int N = 1e5 + 10, M = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m;
int p[N]; //祖宗节点
struct Edge {
    int u, v, w;
    bool operator<(const Edge &T) const { //重载方便排序
        return w < T.w;
    }
} edges[M];
int find(int x) { //并查集核心
    return p[x] != x ?  p[x] = find(p[x]) : x;
}

int kruskal() {
    sort(edges, edges + m);
    for (int i = 1; i <= n; i++) p[i] = i; //初始化并查集
    int res = 0, cnt = 0; // res 最小生成树中的权重之和   //cnt 当前加了多少条边
    for (int i = 0; i < m; i++) {
        auto t = edges[i];
        t.u = find(t.u), t.v = find(t.v);
        if (t.u != t.v) { // 如果不在同一个集合
            p[t.u] = t.v;
            res += t.w;
            cnt++;
        }
    }
    if (cnt < n - 1) return INF;
    return res;
}
int main() {
    cin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    int x = kruskal();
    if (x > INF / 2)
        puts("impossible");
    else
        cout << x << endl;
}
```

## 二分图
### 二分图染色算法
用于判断是否位二分图，（如果出现奇数环一定不是二分图）

```cpp
const int M = 1e5 + 10;
int head[M], col[M], idx;

struct Edge {
    int to, nxt;
    Edge(int to=0, int nxt=0) :to(to),nxt(nxt){}
} edge[M * 2]; //无向图，点数*2

void add(int u, int v) {
    edge[idx] = Edge(v, head[u]);
    head[u] = idx++;
}

bool dfs(int n, int color) {// 0：未染色，1、2分别代表两种颜色
    col[n] = color; //染色
    for (int i = head[n]; i != -1; i = edge[i].nxt) {
        int j = edge[i].to;
        if (!col[j]) {//如果还没蓝色过则染色
            if (!dfs(j, 3 - color)) return false;
        } else if (col[j] == color)
            return false; //如果发生冲突代表不是二分图，返回false
    }
    return true;
}

int main() {
    memset(head, -1, sizeof head);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) { //确保每个点都被染色到
        if (!col[i]) {
            if (!dfs(i, 1)) {
                flag = false;
                break;
            }
        }
    }
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
```
### 匈牙利算法
二分图匹配算法
```cpp
const int M = 1e5 + 7;
int head[M], match[M], idx;
bool st[M];
struct Edge {
    int to, nxt;
    Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {
    }
} edge[M];
void add(int u, int v) {
    edge[idx] = Edge(v, head[u]);
    head[u] = idx++;
}
int find(int x) {
    for (int i = head[x]; i != -1; i = edge[i].nxt){//遍历相连bian（相连边不同色）
        int j = edge[i].to;
        if (!st[j]) {//如果没有被预定
            st[j] = true;                     //预定它
            if (!match[j] || find(match[j])) {//没有匹配或者查找其他匹配对象
                match[j] = x; //选中
                return true;
            }
        }
    }
    return false; //实在找不到
}
int main() {
    memset(head, -1, sizeof head);
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    int res = 0;
    for (int i = 1; i <= n1; i++) {
        //因为每次模拟匹配的预定情况都是不一样的所以每轮模拟都要初始化
        memset( st, 0, sizeof st); 
        if (find(i)) res++;
    }
    cout << res << endl;
    return 0;
}
```

## 树
### 树的重心
重心定义：重心是指树中的一个结点，如果将这个点删除后，剩余各个连通块中点数的最大值最小，那么这个节点被称为树的重心。
```cpp
const int maxn = 1e5 + 7;
struct Edge {
    int to, next;
} edge[maxn * 2];
int head[maxn], tot, ans = maxn, n;
bool node[maxn];
void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}
void add(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int dfs(int m) {
    int sizes = 0, sum = 0;
    node[m] = 1;
    for (int i = head[m]; i != -1; i = edge[i].next) {
        int j = edge[i].to;
        if (!node[j]) {
            int s = dfs(j);
            sizes = max(sizes, s);
            sum += s;
        }
    }
    sizes = max(sizes, n - sum - 1);
    ans = min(ans, sizes);
    return sum + 1;
}
int main() {
    int t;
    memset(head, -1, sizeof(head));
    cin >> t;
    n = t--;
    while (t--) {
        int u, v;
        cin >> u >> v;
        add(u, v)， add(v, u);
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}
```
### 树的直径
树的直径：树上最长长度的链被称作树的直径，求树直径长度的方法有双dfs法和树dp法
双dfs法
```cpp
const int maxn = 1e5 + 10;
int N, M, K;
struct Edge {
    int to, next, dis;
} edge[maxn * 2];
int head[maxn], tot;
int dis[maxn];
void init() {
    for (int i = 0; i <= N; i++) head[i] = -1;
    tot = 0;
}
void add(int u, int v, int w) {
    edge[tot] = {v,head[u], w};
    head[u] = tot++;
}
void dfs(int t, int la) {
    for (int i = head[t]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == la) continue;
        dis[v] = dis[t] + edge[i].dis;
        dfs(v, t);
    }
}
int main() {
    int T;
    scanf("%d", &T);
    int CASE = 1;
    while (T--) {
        scanf("%d", &N);
        init();
        for (int i = 1; i <= N - 1; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w), add(v, u, w);
        }
        int root = 1;
        dis[root] = 0;
        dfs(root, -1);
        for (int i = 1; i <= N; i++)
            if (dis[root] < dis[i])
                root = i;
        dis[root] = 0;
        dfs(root, -1);
        for (int i = 1; i <= N; i++)
            if (dis[root] < dis[i])
                root = i;
        printf("Case %d: ", CASE++);
        Pri(dis[root]);
    }
    return 0;
}
```

## 树的 DFS 序
将一棵树变为一个线性的关系，并且保证这个线性关系的所有连续区间 ($[l to r]$) 中在原本的树上是相连的，所有再配合上树状数组，线段树之类的数据结构，可以对原本的树进行更多的操作，如区间修改，区间查询等
### 树上边的 DFS 序
记录自己和自己的父亲结点
```cpp
void dfs(int now, int fa) {
    edge.push_back({now, fa});
    for(int i = 0; i < (int)tr[now].size(); i ++) {
        if(fa != tr[now][i]) {
            dfs(tr[now][i], now);
        }
    }
}
```
### 树上点的 DFS 序
记录第一次遍历到这个点和这个点结束。
```cpp
void dfs(int now, int fa) {
    in[now] = cnt;
    for(int i = 0; i < (int)tr[now].size(); i ++) {
        if(fa != tr[now][i]) {
            cnt ++;
            dfs(tr[now][i], now);
        }
    }
    out[now] = cnt;
}
```