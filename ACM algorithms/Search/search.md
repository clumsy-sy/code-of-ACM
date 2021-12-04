# 搜素

## BFS
### 普通 BFS
一层一层的搜索，普遍 $O(N)$
```cpp
typedef pair<int, int> pll;
const int M = 110;
int n, m;
int p[M][M], d[M][M]; // p为记录数组，d为记录走过的路线

bool check(int x, int y) {//判断是否可行
    if (x>=1&&x<=n&&y>=1&&y<=m&&p[x][y]==0&&d[x][y]==-1) return 1;
    else return 0;
}
int bfs() {
    int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1}; 
    queue<pll> q;                                   
    memset(d, -1, sizeof(d));
    d[1][1] = 0;
    q.push({1, 1}); //初始化
    while (!q.empty()) {
        auto t = q.front();
        q.pop(); //弹出队尾
        for (int i = 0; i < 4; i++) {
            int x = t.first + dx[i], y = t.second + dy[i];
            if (check(x, y)) {
                d[x][y] = d[t.first][t.second] + 1; 
                q.push({x, y});
            }
        }
    }
    return d[n][m];
}
int main() {
    IOS;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> p[i][j];
    cout << bfs() << endl;
    return 0;
}
```

### 多源 BFS
多源 BFS 就是把满足初始条件的点全部塞入队列
```cpp
#define x first
#define y second
typedef pair<int, int> PII;
const int M = 1010;
int n, m, dist[M][M];
char g[M][M];
PII que[M * M];

void bfs()
{
    memset(dist, -1, sizeof dist);   //初始为-1， 用~来判断是否已经走过
    int hh = 0, tt = -1;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            if(g[i][j] == '1'){      //满足条件的点一开始直接全部压入队列
                que[++ tt] = {i, j};
                dist[i][j] = 0;
            }
    int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
    while(hh <= tt){
        PII now = que[hh ++];、
        for(int i = 0; i < 4; i ++){
            int a = now.x + dx[i], b = now.y + dy[i];
            if(a < 0 || a > n || b < 0 || b > n || ~dist[a][b]) continue;
            dist[a][b] = dist[now.x][now.y] + 1;
            que[++ tt] = {a, b};
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i ++)scanf("%s", g[i]);    
    bfs();
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++)
            printf("%d ", dist[i][j]);
        puts("");
    }
    return 0;
}
```

### 双向 BFS
从起始点和目标点同时向中间 BFS ，两端接触算找到方案
```cpp
int n;
string a[6], b[6];
int extend(queue<string> &now, unordered_map<string, int> &da, unordered_map<string, int> &db, string a[], string b[]){
    for(int cnt = now.size(), c = 0; c < cnt; c ++) {//只扩展一遍当前队列中已存在的元素，否则退化为普通bfs，会TLE
        string k = now.front();
        now.pop();
        for(int i = 0; i < k.size(); i ++) {
            for(int j = 0; j < n; j ++) {
                if(k.substr(i, a[j].size()) == a[j]) {
                    string change = k.substr(0, i) + b[j] + k.substr(i + a[j].size());
                    if(da.count(change)) continue;
                    if(db.count(change)) return da[k] + db[change] + 1;
                    da[change] = da[k] + 1;
                    now.push(change);
                }
            }
        }
    }
    return INF;
}
int bfs(string start, string end) {
unordered_map<string, int> permp, sufmp; //头、尾
    queue<string> per, suf; //头尾队列
    per.push(start);
    suf.push(end);
    permp[start] = 0;
    sufmp[end]   = 0;
    while(per.size() && suf.size()) {// 如果有对列空了，说明不
        int ans;       //双向广搜，每次扩展的队列是当前个数比较少的
        if(per.size() <= suf.size()) ans = extend(per, permp, sufmp, a, b);
        else ans = extend(suf, sufmp, permp, b, a);
        if(ans != INF) return ans; //起点与终点第一次相遇便是最小值，直接返回
    }
    return INF;
}
int main() {
    string A, B;
    cin >> A >> B;
    while(cin >> a[n] >> b[n]) n ++;
    int ans = bfs(A, B);
    if(ans > 10) puts("NO ANSWER!");
    else printf("%d\n", ans);
    return 0;
}
```
BFS总结：
	BFS中的队列实际上就是一个简化的堆，可以保证队列内的数据，具有二段性，与单调性，所以第一次搜到的某点，就是最短路径。
双端队列BFS：
	可以解决边权为0，1的最短路问题，遇到边权为0的直接放在队头，为1放在队尾，这样队列依旧保持二段性与单调性。


## A* 算法
通过一个启发函数f（x）， 来预测走到终点的步数，
再用小根堆来排序，保证每次堆顶都是预测最容易走到终点的过程，依据{当前值+预测值}作为排序依据。
需要保证启发函数预测值必须 <= 实际操作值，越接近效果越好，可证明第n次在堆顶出现所需终点，为第n小值，但中间的点不一定为最小值（第n小值）；
在八数码问题中的启发函数便是每个点到它本应该存在点的“哈密顿距离”，K短路问题中的预测值为，通过Dijkstra算出来的，由起点到终点的最短路；
```cpp
typedef pair<int, string> PIS;
int f(string now) {// 启发函数，求哈密顿距离（dist = |x - x0| + |y - y0|）

    int dist = 0;
    for(int i = 0; i < 9; i ++)
        if(now[i] != 'x') {
            int k = now[i] - '1';
            dist += abs(i / 3 - k / 3) + abs(i % 3 - k % 3);
        }
    return dist;
}
void bfs(string st, string end) {
    priority_queue<PIS, vector<PIS>, greater<PIS>> heap; //小根堆
    unordered_map<string, pair<char, string>> road;      //存放路径
    unordered_map<string, int> dist;                     //存放距离
    heap.push({f(st), st});  dist[st] = 0;
    char op[] = {'u', 'r', 'd', 'l'};                    //对应操作符
    int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
    while(heap.size()) {
        PIS t = heap.top();
        heap.pop();
        string now = t.second;
        if(now == end) break;                            //第一次找到终点便为最小操作方法
        int x, y;
        for(int i = 0; i < 9; i ++)
            if(now[i] == 'x') {
                x = i / 3;
                y = i % 3;
            }
        for(int i = 0; i < 4; i ++) {
            int a = x + dx[i], b = y + dy[i];
            if(a < 0 || a >= 3 || b < 0 || b >= 3) continue;
            swap(now[x * 3 + y], now[a * 3 + b]);
            if(!dist[now] || dist[now] > dist[t.second] + 1) {//更新距离
                dist[now] = dist[t.second] + 1;
                road[now] = {op[i], t.second};
                heap.push({dist[now] + f(now), now});
            }
            swap(now[x * 3 + y], now[a * 3 + b]);
        }
    }
    string ans;
    while(end != st) {
        ans += road[end].first;
        end = road[end].second;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
int main() {
    string start, end;
    for(int i = 0; i < 9; i ++) {
        char k;
        cin >> k;
        start += k;
        if(i == 8) end += 'x';
        else end += char(i + '1');
    }

    int ni = 0;                                          //求逆序数，当逆序数为奇数，必然不能转换到原始状态
    for(int i = 0; i < 9; i ++)               
        for(int j = i + 1; j < 9; j ++) {
            if(start[i] == 'x' || start[j] == 'x') continue;
            if(start[i] > start[j]) ni ++;
        }
        
    if(ni & 1) puts("unsolvable");
    else bfs(start, end);
    return 0;
}
```
```cpp
typedef pair<int, int> PII;
typedef pair<int, PII> PIII;
const int M = 1e5 + 7;
int n, m, S, T, K, idx;
int head[M], rhead[M], dist[M], cnt[M];
bool st[M];
struct Edge {
    int to, w, nxt;
}edge[M * 2];
void init() {
    memset(head, -1, sizeof head);
    memset(rhead, -1, sizeof rhead);
    memset(dist, 0x3f, sizeof dist);
}
void add(int head[], int u, int v, int w) {
    edge[idx] = {v, w, head[u]};
    head[u] = idx ++;
}
void Dijkstra() {   //求得是终点的最短路，作为启发函数
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, T});
    dist[T] = 0;
    while(heap.size()) {
        PII now = heap.top();
        heap.pop();
        if(st[now.y]) continue;
        st[now.y] = true;
        for(int i = rhead[now.y]; ~i; i = edge[i].nxt){
            int j = edge[i].to;
            if(dist[j] > edge[i].w + now.x){
                dist[j] = edge[i].w + now.x;
                heap.push({dist[j], j});
            }
        }
    }
}
int astra() {
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    heap.push({dist[S], {0, S}});
    while(heap.size()) {
        PIII now = heap.top();
        heap.pop();
        int distance = now.y.x, ver = now.y.y;
        cnt[ver] ++;
        if(cnt[T] == K)  return distance;      //第K次在堆顶遇到终点便为第K短路
        for(int i = head[ver]; ~i; i = edge[i].nxt) {
            int j = edge[i].to;
            if(cnt[j] < K)
                heap.push({dist[j] + distance + edge[i].w, {distance + edge[i].w, j}});
        }   //{当前距离 + 预计最短距离，{当前距离， 点}}；
    }
    return -1;
}
int main() {
    init();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i ++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        add(head, x, y, w);     //正向建边 + 逆向建边，方便Dijkstra
        add(rhead, y, x, w);    //dist[k]内的值便代表“终点”到k点的最短距离，用作启发函数
    }
    scanf("%d%d%d", &S, &T, &K);
    if(S == T) K ++;            //至少含一条边，所以起点终点相同时要去掉一种情况
    Dijkstra();
    printf("%d\n", astra());
    return 0;
}
```

## 模拟退火 （SA 算法）
玄学算法，一般用在浮点数上，复杂度 $O(N^2)$
```cpp
typedef pair<double, double> PDD;
const int M = 110;
PDD p[M];
int n;
double ans = 1e8; 
double rands(double l, double r){ //随机一个在（l， r）之间的小数
    return (double) rand() / RAND_MAX * (r - l) + l; // rand() / RAND_MAX（生成0，1之间的小数）；
}
double get_dist(PDD a, PDD b) { //求两点距离
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
double calc(PDD k) {//求某点到各各点之间的距离
    double res = 0;
    for(int i = 0; i < n; i ++)
        res += get_dist(k, p[i]);
    ans = min(ans, res);
    return res;
}
void simulate_anneal() {
    PDD point = {rands(0, 10000), rands(0, 10000)};
    double last = calc(point);
    for(double i = 1e4; i > 1e-4; i *= 0.99) {//范围 + 精度 + 退火系数（<=1, 越接近1越精确，但复杂度也越大）
    
        PDD np(rands(point.x - i, point.x + i), rands(point.y - i, point.y + i)); //随机一个范围内的点
        double now = calc(np);
        double dt = now - last;
        if (exp(-dt / i) > rands(0, 1)) {//物理公式，如果这个点比原来的点“差”，一定跳过这个点（范围缩小）
                                         //如果这个点比原来的点“好”，则有一定概率跳过这个点（范围缩小）
            point = np;
            last = now;
        }
    }//通过退火过程，不断缩小范围，最后找到最值（但也有可能找不到，或者找错了）
}

int main() {
    srand(time(0));               //随机函数种子（运气）
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = {x, y};
    }
    for(int i = 0; i <= 10; i ++)  //退火过程多做几遍，使得答案正确可能性大一点
        simulate_anneal();
    printf("%.0lf", ans);          //四舍五入
    return 0;
}
```

## 迭代加深
用 DFS 模仿 BFS 每次只搜索一层，尤其是对于分支特别多的搜索树，重复搜索相对于结果来说影响不大，但是BFS需要非常多的空间，DFS可以节省空间记录下搜索路径
```cpp
const int N = 110;
int n;
int path[N];
bool dfs(int u, int k) {
    if (u == k) return path[u - 1] == n;
    bool st[N] = {0};
    for (int i = u - 1; i >= 0; i -- )
        for (int j = i; j >= 0; j -- ) {
            int s = path[i] + path[j];
            if (s > n || s <= path[u - 1] || st[s]) continue;
            st[s] = true;
            path[u] = s;
            if (dfs(u + 1, k)) return true;
        }
    return false;
}
int main() {
    path[0] = 1;
    while (cin >> n, n) {
        int k = 1;
        while (!dfs(1, k)) k ++ ; // 迭代加深，（如果没有搜到）每次深度 + 1；

        for (int i = 0; i < k; i ++ ) cout << path[i] << ' ';
        cout << endl;
    }
    return 0;
}
```

## 双向 DFS
一般用来处理 “子集和” 问题， 从给定的 $N$ 个数中选几个，使他们的和最接近 $W$，也可以认为是一个大背包问题，最暴力的解法是 $O(2^N)$ 的暴力枚举。
利用双向搜索的思想，把物品分成两半，从前一半中选出若干，可能达到 $0 ~ W$ 之间的所有重量值存到一个数组 $A$ 中，对数组排序，去重。
然后进行第二次搜索，尝试从后一半礼物中选一些，对于每个可能达到的重量 $t$ ，在第一部分得到的素组 A 中二分查找 $\le W - t$ 的最大的一个，更新答案
总复杂度接近 $O(N * x ^{\frac{N}{2}})$ 

```cpp
const int N = 1 << 25; // k最大是25， 因此最多可能有2^25种方案
int n, m, k;
int g[50];      // 存储所有物品的重量
int weights[N]; // weights存储能凑出来的所有的重量
int cnt = 0;
int ans; // 用ans来记录一个全局最大值
// u表示当前枚举到哪个数了， s表示当前的和
void dfs(int u, int s) {
    // 如果我们当前已经枚举完第k个数（下标从0开始的）了， 就把当前的s，
    // 加到weights中去
    if (u == k) {
        weights[cnt++] = s;
        return;
    }
    // 枚举当前不选这个物品
    dfs(u + 1, s);
    // 选这个物品, 做一个可行性剪枝
    if ((ll)s + g[u] <= m) { //计算和的时候转成long long防止溢出
        dfs(u + 1, s + g[u]);
    }
}
void dfs2(int u, int s) {
    if (u == n) { // 如果已经找完了n个节点， 那么需要二分一下
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (weights[mid] <= m - s)
                l = mid;
            else
                r = mid - 1;
        }
        ans = max(ans, weights[l] + s);
        return;
    }
    // 不选择当前这个物品
    dfs2(u + 1, s);
    // 选择当前这个物品
    if ((ll)s + g[u] <= m)
        dfs2(u + 1, s + g[u]);
}
int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> g[i];
    // 优化搜索顺序（从大到小）
    sort(g, g + n);
    reverse(g, g + n);
    k = n / 2 + 2; // 把前k个物品的重量打一个表
    dfs(0, 0);
    // 做完之后， 把weights数组从小到大排序
    sort(weights, weights + cnt);
    // 判重
    int t = 1;
    for (int i = 1; i < cnt; i++)
        if (weights[i] != weights[i - 1])
            weights[t++] = weights[i];
    cnt = t;
    // 从k开始， 当前的和是0
    dfs2(k, 0);
    cout << ans << endl;
    return 0;
}
```

## IDA*
A* + 迭代加深

