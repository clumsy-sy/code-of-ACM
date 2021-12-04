# 基础数据结构

## 并查集
### 路径压缩
```cpp
int f[M];
int find(int k) {
    return f[k] != k ? f[k] = find(f[k]) : k;
}
void dsu() {
    for (int i = 1; i <= n; i++) f[i] = i; // 初始化
    if (find(x) == find(y)) // 注意判断原来是否在一个集合中
    f[find(x)] = find(y); // 合并
}
```
### 按秩合并
```cpp
#define MAXN 5005
int fa[MAXN], rank[MAXN];
int find(int x) {
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
void merge(int i, int j) {
    int x = find(i), y = find(j);
    if (rank[x] <= rank[y]) fa[x] = y;
    else fa[y] = x;
    if (rank[x] == rank[y] && x != y) rank[y]++;
}
void init() {
    for (int i = 1; i <= n; ++i)  
        fa[i] = i, rank[i] = 1;
}
```
### 种类并查集
一般的并查集，维护的是具有连通性、传递性的关系，例如亲戚的亲戚是亲戚。但是，有时候，我们要维护另一种关系：敌人的敌人是朋友。种类并查集就是为了解决这个问题而诞生的。
```cpp
const int M = 2e6+7;
int  p[M];
int  find(int k){
    return p[k] != k ? p[k] = find(p[k]) : k;
}
void merge(int x, int y){p[find(x)] = find(y);}

int main()
{
    int  n, k, ans = 0;
    cin >> n >> k;
    for(int i=1; i<=3*n; i++)p[i] = i; // 分成三块，0——同类域，n——捕食域，n+n——天敌域
    while(k--){
        int  d, x, y;
        cin >> d >> x >> y;
        if(x > n || y > n) ans ++;
        else{
            if(d == 1){
                if(find(x) == find(y+n) || find(x) == find(y+n+n)) ans ++;
                else {merge(x,y); merge(x+n,y+n); merge(x+n+n,y+n+n);}
            }
            else{
                if(x ==y || find(x) == find(y) || find(x) == find(y+n)) ans ++;
                else {merge(x,y+n+n); merge(x+n,y); merge(x+n+n,y+n);}
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
## 单调栈
```cpp
int hh = 0; // 头指针
    for (int i = 1; i <= n; i++) {
        cin >> k;
        if (!hh) { // 如果当前栈为空，入栈
            num[++ hh] = k;
        } else {
            while (hh && num[hh] >= k) {hh--;}  //栈顶元素小于当前元素, 出栈
            if (hh) cout << num[hh] << endl; // 栈顶为维护的最值
            else cout << -1 << endl;
            num[++hh] = k; // 元素入栈
        }
    }
```

## 滑动窗口
单调队列，维护区间最值
```cpp
const int N = 1e6 + 7;
int a[N], q[N];
int main() {
    int n, k;
    cin >> n >> k;
    int hh = 0, tt = -1;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) {
        if (i - k + 1 > q[hh]) ++hh;   //控制滑动窗口的大小
        while (hh <= tt && a[i] <= a[q[tt]]) --tt;  //使得最小值一直处于hh所指的位置，且有排序功能
        q[++tt] = i;    //比hh大的数要存在后面，因为窗口移动后可能会用到
        if (i + 1 >= k) cout << a[q[hh]] << " "; //输出hh所指的数
    }
    cout << endl;
    return 0;
}
```
## 树状数组
存储偏序关系
```cpp
int n, tr[M], num[M], ans[M];
int lowbit(int x) {return x & -x;}
void add(int x, int k) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += k;
}
int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
```
O（n）初始化的方法：记录前缀和tr[i] = per[i] - per[i - lowbit(i)];

### 求逆序对
每次求出前面比当前位置大的数。
如果数据较大需要离散化或者使用归并排序。
```cpp
const int N = 1e6 + 7;
int n, m;
int w[N], tr[N];
int lowbit(int x) {return x & -x;}
void add(int x, int v) {
    for (int i = x; i <= N; i += lowbit(i))tr[i] += v;
}
int query(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))sum += tr[i];
    return sum;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);
    LL sum = 0;
    for (int i = 0; i < n; i++) {
        sum += query(N) - query(w[i]); // 求前面比自己大的数
        add(w[i], 1);
    }
    printf("%lld", sum);
    return 0;
}
```

## 线段树
线段树主要维护的是区间满足可加性的一些性质，最值、三角函数、gcd等等
### 基础线段树
可以实现区间查询，单点修改
```cpp
const int M = 2e5 + 7;
struct Tree {
    int l, r;
    int v;
} tr[M * 4]; // 4 倍空间
void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}
void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int ans = 0, mid = (tr[u].l + tr[u].r) >> 1;
    if (l <= mid) ans = max(ans, query(u << 1, l, r)); // 因为是完整区间，所有左右都需要查询
    if (r > mid) ans = max(ans, query(u << 1 | 1, l, r));
    return ans;
}
void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else {
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}
```

### 带懒标记的线段树
支持区间查询，区间修改
```cpp
struct Node
{
    int l, r;
    ll sum, add; // add 为懒标记
}tr[N * 4];
void pushup(int u){
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void pushdown(int u){
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add)
    {
        left.add += root.add, left.sum += (ll)(left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += (ll)(right.r - right.l + 1) * root.add;
        root.add = 0; // 清除懒标记
    }
}
void build(int u, int l, int r){
    if (l == r) tr[u] = {l, r, w[r], 0};
    else{
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int l, int r, int d){
    if (tr[u].l >= l && tr[u].r <= r){
        tr[u].sum += (ll)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }
    else {   // 一定要分裂
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid)  modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}
ll query(int u, int l, int r){
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= mid) sum = query(u << 1, l, r);
    if (r > mid)  sum += query(u << 1 | 1, l, r);
    return sum;
}
```

### 线段树扫描线
可以求部分计算几何问题，如重合矩形面积
```cpp
const int N = 100010;
int n, m;
int w[N];
const int N = 100010;
struct Segment // 用来存线段
{
    double x, y1, y2;
    int d; // 标记它是第一次这一段在前还是在后
    bool operator<(const Segment &A) const {
        return x < A.x; // 按横坐标从小到大排序
    }
} seg[N << 1];
// 线段树的每个节点 保存长度为1的线段
struct Node {
    int l, r;
    int tag;    // 记录这段区间出现了几次
    double len; // 记录这段区间的长度;
} tr[N * 4];
vector<double> ys;
int find(double x) {// 需要返回vector 中第一个 >= x 的数的下标
    return lower_bound(ys.begin(), ys.end(), x) - ys.begin();
}
void pushup(int u) {
    if (tr[u].tag) tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
    else if (tr[u].l != tr[u].r) {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    } else tr[u].len = 0;
}
void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l != r) {
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    }
}
void modify(int u, int l, int r, int d) {
    if (l <= tr[u].l && r >= tr[u].r) {
        tr[u].tag += d;
        pushup(u);
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}
int main() {
    int t = 1, n;
    while (scanf("%d", &n), n) {
        ys.clear();
        for (int i = 1, j = 0; i <= n; i++) {
            double x1, x2, y1, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[j++] = {x1, y1, y2, 1};
            seg[j++] = {x2, y1, y2, -1};
            ys.push_back(y1);
            ys.push_back(y2);
        }
        sort(seg, seg + n * 2);
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        build(1, 0, ys.size() - 2);
// 线段树的每个叶子节点[l, l]， 代表离散化后的y轴上的 [l,l + 1], 所以从零开始初始化;
        double res = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (i)
                res += tr[1].len *(seg[i].x - seg[i - 1].x); 
            modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].d);
        }
    }
    return 0;
}
```

## 分块算法
优美的暴力， $O(N \sqrt{N})$
```cpp
int n, m, len;
ll add[M], sum[M];
int w[N];

int get(int i) { return i / len; }
void change(int l, int r, int d)
{
    if (get(l) == get(r))  // 段内直接暴力
        for (int i = l; i <= r; i ++ ) w[i] += d, sum[get(i)] += d;
    else{
        int i = l, j = r;
        while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, i ++ ;
        while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, j -- ;
        for (int k = get(i); k <= get(j); k ++ ) sum[k] += len * d, add[k] += d;
    }
}
ll query(int l, int r)
{
    ll res = 0;
    if (get(l) == get(r))  // 段内直接暴力
        for (int i = l; i <= r; i ++ ) res += w[i] + add[get(i)];
    else {
        int i = l, j = r;
        while (get(i) == get(l)) res += w[i] + add[get(i)], i ++ ;
        while (get(j) == get(r)) res += w[j] + add[get(j)], j -- ;
        for (int k = get(i); k <= get(j); k ++ ) res += sum[k];
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);len = sqrt(n);
    for (int i = 1; i <= n; i ++ ){
        scanf("%d", &w[i]);
        sum[get(i)] += w[i];
    }
    char op[2];int l, r, d;
    while (m -- ){
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C'){
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", query(l, r));
    }
    return 0;
}
```

### 莫队算法
分块 + 双指针，对离线查询的操作
模板，离线查询一段区间内不同元素的个数
```cpp
const int N = 50010, M = 200010, S = 1000010;
int n, m, len;
int w[N], ans[M];
struct Query {
    int id, l, r;
} q[M];
int cnt[S];
int get(int x) {
    return x / len;
}
bool cmp(const Query &a, const Query &b) //根据分块和右端点先后排序
{
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}
void add(int x, int &res) {
    if (!cnt[x]) res++;
    cnt[x]++;
}
void del(int x, int &res) {
    cnt[x]--;
    if (!cnt[x]) res--;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    scanf("%d", &m);
    len = sqrt((double)n * n / m); //分块
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r}; // 查询（后面排序）
    }
    sort(q, q + m, cmp);
    for (int k = 0, i = 0, j = 1, res = 0; k < m; k++) {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(w[++i], res);
        while (i > r) del(w[i--], res);
        while (j < l) del(w[j++], res);
        while (j > l) add(w[--j], res);
        ans[id] = res;
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
    return 0;
}
```

## 平衡树
### treap
heap + tree，简单好写，功能略少。
```cpp
using namespace std;
const int M = 1e5+7, INF = 0x3f3f3f3f;
int n, root, idx;
//treap树 = tree + heap；
struct Node {
    int l, r;
    int key, val;                    //val为随机函数生成的值，目的是使得整个二叉树根据val成为最大堆；
    int cnt, sizes;                  //cnt 记录 key 值的个数， sizes 记录子树（包含自己）的大小；
}tr[M];

void pushup(int p) {                 //更新已自己为根节点的树的大小
    tr[p].sizes = tr[tr[p].l].sizes + tr[tr[p].r].sizes + tr[p].cnt;
}
int get_node(int key) {              //创建一个新的节点
    tr[ ++ idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].sizes = 1;
    return idx;                      //返回结点编号
}
void zig(int &p) {                   //右旋
    int q = tr[p].l;
    tr[p].l = tr[q].r;
    tr[q].r = p;
    p = q;
    pushup(tr[p].r); pushup(p);      //更新旋转的两个点
}
void zag(int &p) {                   //左旋
    int q = tr[p].r;
    tr[p].r = tr[q].l;
    tr[q].l = p;
    p = q;
    pushup(tr[p].l); pushup(p);      //更新旋转的两个点
}
void build() {
    get_node(-INF); get_node(INF);
    root = 1, tr[1].r = 2;
    pushup(root);
    if(tr[1].val < tr[2].val) zag(root);
}
void insert_node(int &p, int key) {  //插入新的结点

    if(!p) p = get_node(key);        //如果该key值不存在则创建新的结点
    else if(tr[p].key == key){
        tr[p].cnt ++;                //已存在， cnt ++；
    }
    else if(tr[p].key > key){
        insert_node(tr[p].l, key);   //向左递归寻找
        if(tr[tr[p].l].val > tr[p].val) zig(p);  //维护最大堆
    }
    else{
        insert_node(tr[p].r, key);   //向右递归寻找
        if(tr[tr[p].r].val > tr[p].val) zag(p);  //维护最大堆
    }
    pushup(p);                       //更新
}
void remove_node(int &p, int key) {
    if(!p) return;                   //不存在该结点
    if(tr[p].key == key){
        if(tr[p].cnt > 1){
            tr[p].cnt --;
        }
        else if(tr[p].l || tr[p].r) {//key已有数量 == 1（此时必须将该节点旋转为末尾结点才能删除）
        
            if(!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
                zig(p);
                remove_node(tr[p].r, key);
            }
            else {
                zag(p);
                remove_node(tr[p].l, key);
            }
        }
        else p = 0;                 //直接指向tr[0]点（？）
    }
    else if(tr[p].key > key) {
        remove_node(tr[p].l, key);
    }
    else remove_node(tr[p].r, key);
    pushup(p);
}
int get_rank_by_key(int p, int key) { //从key值找排名（+1才是排名）
    if (!p) return -INF;
    if (tr[p].key == key) return tr[tr[p].l].sizes + 1;  //左子树的大小 + 1；
    if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);  //往左走
    return tr[tr[p].l].sizes + tr[p].cnt + get_rank_by_key(tr[p].r, key);   //往右走需要把左边的所有数都加上
}
int get_key_by_rank(int p, int ranks) {//从排名找key值
    if (!p) return INF;
    if (tr[tr[p].l].sizes >= ranks) return get_key_by_rank(tr[p].l, ranks);  //往左走
    if (tr[tr[p].l].sizes + tr[p].cnt >= ranks) return tr[p].key;            //找到
    return get_key_by_rank(tr[p].r, ranks - tr[tr[p].l].sizes - tr[p].cnt);  //往右走需要减去左子树和根节点的大小
}
int get_prev(int p, int key) { //求某数的前驱
    if(!p) return -INF; //终止
    if(tr[p].key >= key) return get_prev(tr[p].l , key);  //往左走
    return max(tr[p].key, get_prev(tr[p].r, key));        //往右走
}
int get_next(int p, int key) { //求某数的后继
    if(!p) return INF; //终止
    if(tr[p].key <= key) return get_next(tr[p].r , key);  //往左走
    return min(tr[p].key, get_next(tr[p].l, key));        //往右走
}
int main() {
    scanf("%d", &n);
    build();
    while(n --) {
        int op, x;   // 1.插入 2.删除 3.通过key求排名 4.通过排名求key 5.求前驱 6.求后继
        scanf("%d%d", &op, &x);
        switch(op){
            case 1 : insert_node(root, x);
                        break;
            case 2 : remove_node(root, x);
                        break;
            case 3 : printf("%d\n", get_rank_by_key(root, x) - 1);
                        break;
            case 4 : printf("%d\n", get_key_by_rank(root, x + 1));
                        break;
            case 5 : printf("%d\n", get_prev(root, x));
                        break;
            default : printf("%d\n", get_next(root, x));
        }
    }
    return 0;
}
```

### Splay
神奇的旋转平衡树，操作略慢，但是操作非常多，支持区间旋转

```cpp
using namespace std;
const int N = 2e5 + 7, INF = 0x3f3f3f3f;
struct splay_tree {
    int ff, cnt, ch[2], val, sizes;//ff:father, ch[0]:left, ch[1].right;
} t[N];

int root, tot, que[30];                     //root当前根节点，tot当前的结点总数
void update(int x) {
    t[x].sizes = t[t[x].ch[0]].sizes + t[t[x].ch[1]].sizes + t[x].cnt;
}
void rotate(int x)
{
    int y = t[x].ff;                  //当前结点的父亲结点
    int z = t[y].ff;                  //当前结点的祖父结点
    int k = (t[y].ch[1] == x);        // k寸的是左右结点
    t[z].ch[(t[z].ch[1] == y)] = x;
    t[x].ff = z;
    t[y].ch[k] = t[x].ch[k ^ 1];
    t[t[x].ch[k ^ 1]].ff = y;
    t[x].ch[k ^ 1] = y;
    t[y].ff = x;
    update(y);
    update(x);      //旋转完后更新
}
void splay(int x, int s)                //将结点x旋转到s结点
{
    while(t[x].ff != s){
        int y = t[x].ff , z = t[y].ff;  //y：当前点的父亲结点，z：当前点的祖宗结点
        if (z != s)
            (t[z].ch[0] == y) ^ (t[y].ch[0] == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (s == 0)
        root = x;                        //根节点更新
}
void find(int x)
{
    int u = root;
    if (!u)
        return ;
    while(t[u].ch[x > t[u].val] && x != t[u].val)
        u = t[u].ch[x > t[u].val];
    splay(u, 0);
}
void insert(int x) {
    int u = root, ff = 0;                 //从根节点开始寻找并记录父亲结点
    while(u && t[u].val != x) {
        ff = u;
        u  = t[u].ch[x > t[u].val];       //根据搜索树的性质来选择迭代方向
    }
    if (u)
        t[u].cnt++;
    else {
        u = ++ tot;
        if (ff)                            //如果不存在该点，则新建一个点
            t[ff].ch[x > t[ff].val] = u;   //如果有父亲结点且该节点不还不存在
        t[u].ch[0] = t[u].ch[1] = 0;       //新建一个结点
        t[tot].ff  = ff;
        t[tot].val = x;
        t[tot].cnt = 1;
        t[tot].sizes = 1;
    }
    splay(u, 0);                           //每次将当前结点旋转到根节点
}
int Next(int x, int f) {                   //f = 0前驱， f = 1后驱
    find(x);
    int u = root;
    if (t[u].val > x && f) return u;
    if (t[u].val < x && !f) return u;
    u = t[u].ch[f];
    while(t[u].ch[f ^ 1]) u = t[u].ch[f ^ 1];
    return u;
}
void Delete(int x) {
    int last = Next(x, 0);
    int Net  = Next(x, 1);
    splay(last, 0);
    splay(Net, last);                 //将这个点转到根节点
    int del = t[Net].ch[0];
    if (t[del].cnt > 1) {
        t[del].cnt--;
        splay(del, 0);
    }
    else t[Net].ch[0]=0;
}
int kth(int x) {                      //求第k大值
    int u = root;
    while(t[u].sizes < x)
        return 0;
    while(1) {
        int y = t[u].ch[0];
        if (x > t[y].sizes + t[u].cnt) {
            x -= t[y].sizes + t[u].cnt;
            u = t[u].ch[1];
        }
        else if (t[y].sizes >= x)
            u = y;
        else
            return t[u].val;
    }
}
void show() {
    int hh = 0, tt = -1;
    que[++ tt] = root;
    while(hh <= tt) {
        int u = que[hh ++];
        if(t[u].ch[0]) que[++ tt] = t[u].ch[0];
        if(t[u].ch[1]) que[++ tt] = t[u].ch[1];
    }
    for(int i = 0; i <= tt; i ++) {
        printf("值：%d  标号：%d 左儿子： %d 右儿子：%d\n", t[que[i]].val, que[i], t[que[i]].ch[0], t[que[i]].ch[1]);
    }
}

int main(){
    int n;  scanf("%d", &n);
    insert(INF) ;insert(-INF);       //插入两个哨兵
    while(n--){
        int opt, x;
        scanf("%d%d", &opt, &x);
        switch(opt) {
            case 1 :    insert(x); //插入数值x。
                        break;
            case 2 :    Delete(x); //删除数值x(若有多个相同的数，应只删除一个)。
                        break;
            case 3 :    find(x);
                        printf("%d\n", t[t[root].ch[0]].sizes); //查询数值x的排名(若有多个相同的数，应输出最小的排名)。
                        break;
            case 4 :    printf("%d\n", kth(x + 1)); //查询排名为x的数值。
                        break;
            case 5 :    printf("%d\n", t[Next(x,0)].val); //求数值x的前驱(前驱定义为小于x的最大的数)。
                        break;
            default:    printf("%d\n", t[Next(x,1)].val); //求数值x的后继(后继定义为大于x的最小的数)。
        }
    }
    return 0;
}
```
#### 区间旋转

```cpp
const int N = 100010;
int n, m;
struct Node
{
    int s[2], p, v;
    int size, flag;
    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1;
    }
}tr[N];
int root, idx;
void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void pushdown(int x) {
    if (tr[x].flag) {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;
        tr[tr[x].s[1]].flag ^= 1;
        tr[x].flag = 0;
    }
}
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}
void insert(int v) {
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
}
int get_k(int k) {
    int u = root;
    while (true) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}
void output(int u) {
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    if (tr[u].s[1]) output(tr[u].s[1]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i ++ ) insert(i);
    while (m -- ){
        int l, r;
        scanf("%d%d",&l,&r); // 旋转区间的左右坐标
        l = get_k(l), r = get_k(r+2);
        //由于我们加了左右边界,要删除的序列应该是[l+1,r+1],
        //所以要处理l和r+2;
        splay(l,0), splay(r,l);//将l转到根节点,r转到l的后继节点
        tr[tr[r].s[0]].flag^=1;//r的左儿子翻转,左儿子就是我们的序列
    }
    output(root);
    return 0;
}
```

### 树套树

```cpp
const int N = 1500007, INF = 0x3f3f3f3f;
int n, m, idx, w[N];
struct Node {// splay

    int s[2], p, v;
    int sizes;
    void init(int _v, int _p) {
        v = _v, p = _p;
        sizes = 1;
    }
}tr[N];
struct segment {//线段树
    int l, r;
    int root;
}segtr[N];
//splay的sizes更新
void pushup(int x) {
    tr[x].sizes = tr[tr[x].s[0]].sizes + tr[tr[x].s[1]].sizes + 1;
}
//spaly的旋转操作
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
//将x旋转为到k的子节点
void splay(int& root, int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}
//插入一个点
void insert(int& root, int v) {
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(root, u, 0);
}
//根据数值查排名
int get_k(int root, int v) {
    int u = root, res = 0;
    while (u) {
        if (tr[u].v < v) res += tr[tr[u].s[0]].sizes + 1, u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}
// 更新原值为x的节点数值为新值y
void update(int& root, int x, int y) {
    int u = root;
    while (u) {
        if (tr[u].v == x) break;
        if (tr[u].v < x) u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    splay(root, u, 0);
    int l = tr[u].s[0], r = tr[u].s[1];
    while (tr[l].s[1]) l = tr[l].s[1];
    while (tr[r].s[0]) r = tr[r].s[0];
    splay(root, l, 0), splay(root, r, l);
    tr[r].s[0] = 0;
    pushup(r), pushup(l);
    insert(root, y);
}
void build(int u, int l, int r) {
    segtr[u] = {l, r};
    insert(segtr[u].root, -INF), insert(segtr[u].root, INF);
    for (int i = l; i <= r; i ++) insert(segtr[u].root, w[i]);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
// 区间[a, b]中小于x的节点数量
int query(int u, int a, int b, int x) {
    if (segtr[u].l >= a && segtr[u].r <= b) return get_k(segtr[u].root, x) - 1;
    int mid = (segtr[u].l + segtr[u].r) >> 1, res = 0;
    if (a <= mid) res += query(u << 1, a, b, x);
    if (b > mid) res += query(u << 1 | 1, a, b, x);
    return res;
}
// 更新p位置数据为x
void change(int u, int p, int x) {
    update(segtr[u].root, w[p], x);
    if (segtr[u].l == segtr[u].r) return;
    int mid = (segtr[u].l + segtr[u].r) >> 1;
    if (p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}
// 获取splay前驱节点， 比v小的最大的节点
int get_pre(int root, int v) {
    int u = root, res = -INF;
    while (u) {
        if (tr[u].v < v) res = max(res, tr[u].v), u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}
// 获取splay后继节点，比v大的最小的节点
int get_suc(int root, int v) {
    int u = root, res = INF;
    while (u) {
        if (tr[u].v > v) res = min(res, tr[u].v), u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}
// 节点u查找区间[a, b]中小于x的最大值
int query_pre(int u, int a, int b, int x) {
    if (segtr[u].l >= a && segtr[u].r <= b) return get_pre(segtr[u].root, x);
    int mid = (segtr[u].l + segtr[u].r) >> 1, res = -INF;
    if (a <= mid) res = max(res, query_pre(u << 1, a, b, x));
    if (b > mid) res = max(res, query_pre(u << 1 | 1, a, b, x));
    return res;
}
// 节点u查找区间[a, b]中大于x的最小值
int query_suc(int u, int a, int b, int x) {
    if (segtr[u].l >= a && segtr[u].r <= b) return get_suc(segtr[u].root, x);
    int mid = (segtr[u].l + segtr[u].r) >> 1, res = INF;
    if (a <= mid) res = min(res, query_suc(u << 1, a, b, x));
    if (b > mid) res = min(res, query_suc(u << 1 | 1, a, b, x));
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    build(1, 1, n);
    while (m -- ) {
        int op, a, b, x;
        scanf("%d", &op);
        switch(op) {
            case 1: //查询整数 x 在区间 [l,r] 内的排名。
                    scanf("%d%d%d", &a, &b, &x);
                    printf("%d\n", query(1, a, b, x) + 1);
                    break;
            case 2: //查询区间 [l,r] 内排名为 k 的值。
                    {
                        scanf("%d%d%d", &a, &b, &x);
                        int l = 0, r = 1e8;
                        while (l < r) {
                            int mid = (l + r + 1) >> 1;
                            if (query(1, a, b, mid) + 1 <= x) l = mid;
                            else r = mid - 1;
                        }
                        printf("%d\n", r);
                    }
                    break;
            case 3: //将 pos 位置的数修改为 x。
                    scanf("%d%d", &a, &x);
                    change(1, a, x);
                    w[a] = x;
                    break;
            case 4: //查询整数 x 在区间 [l,r] 内的前驱(前驱定义为小于 x，且最大的数)。
                    scanf("%d%d%d", &a, &b, &x);
                    printf("%d\n", query_pre(1, a, b, x));
                    break;
            default: //查询整数 x 在区间 [l,r] 内的后继(后继定义为大于 x，且最小的数)。
                    scanf("%d%d%d", &a, &b, &x);
                    printf("%d\n", query_suc(1, a, b, x));
        }
    }
    return 0;
}
```

## 模拟堆

```cpp
const int N = 1e5 + 10;
int h[N], ph[N], hp[N]; //堆、插入顺序、堆对应的插入序
int cur_size;           //堆大小

void heap_swap(int u, int v) {//需要交换三组下标
    swap(h[u], h[v]);
    swap(hp[u], hp[v]);
    swap(ph[hp[u]], ph[hp[v]]);
}
//非常重要的向下调整函数
void down(int u) {
    int t = u;
    if (u * 2 <= cur_size && h[t] > h[u * 2]) t = u * 2;
    if (u * 2 + 1 <= cur_size && h[t] > h[u * 2 + 1]) t = u * 2 + 1;
    if (u != t) {
        heap_swap(u, t);
        down(t); //递归直到合适的位置
    }
}
//向上调整
void up(int u) {
    if (u / 2 > 0 && h[u] < h[u / 2]) {
        heap_swap(u, u / 2);
        up(u >> 1);
    }
}
int main() {
    int n, m = 0;
    cin >> n;
    while (n--) {
        string op;
        int k, x;
        cin >> op;
        if (op == "I") { // 插入一个数
            cin >> x;
            m++;
            h[++cur_size] = x; //放入堆尾
            ph[m] = cur_size;
            hp[cur_size] = m; //记录顺序
            up(cur_size);     //向上调整
        } else if (op == "PM") // 输出集合中的最小值
            cout << h[1] << endl; //堆顶即为
        else if (op == "DM") { // 删除当前集合中的最小值
            heap_swap(1, cur_size); //讲堆的最后一个元素代替第一个元素，在向下调整
            cur_size--;
            down(1);
        } else if (op == "D") { // 删除第 K 个插入的数
            cin >> k;
            int u = ph[k];
            heap_swap(u, cur_size);
            cur_size--;
            up(u),down(u); // up和down其实只会执行其中一个
        } else if (op == "C") { // 修改第 K 个插入的数，将其变成 x
            cin >> k >> x;
            h[ph[k]] = x;
            down(ph[k]), up(ph[k]);
        }
    }
    return 0;
}
```

## Hash
一般情况先可以使用 unorder_map 代替一下
### 拉链法 Hash
```cpp
const int M = 1e5 + 7;
int num[M], link[M], net[M];
int head, idx, N = 100003; // N为取模数，最好为质数，最好是离数组大小最近的质数
void charge(int k) { //讲数字映射到嘻哈表中
    link[idx] = k;   //放入链表中
    int u = (k % N + N) % N; //注意：负数取模为对应相反数取模的负数，所以需要加上N再次取模。
    if (num[u] == -1) {
        num[u] = idx;
        net[idx++] = -1;
    } else {
        net[idx] = num[u];
        num[u] = idx++;
    }
}
bool check(int k) { //查找是否在哈希表中存在此数
    int u = (k % N + N) % N;
    for (int i = num[u];;) {
        if (i == -1) return 0;
        if (link[i] == k) return 1;
        else i = net[i];
    }
}
int main() {
    memset(num, -1, sizeof(num)); //注意初始化
    return 0;
}
```

### 开放寻址法

```cpp
const int M = 2e5 + 7; //开放寻址法中数组要开大2~3倍来减少冲突
int num[M];
int N = 2e5 + 3; //离数组大小最近的质数
void charge(int k) {
    int u = (k % N + N) % N;
    while (num[u] != INF) {
        u++;
        if (u >= N)
            u = 0; //到数组末端之后要从0开始存放
    }
    num[u] = k;
}
bool check(int k) {
    int u = (k % N + N) % N;
    while (num[u] != INF) {
        if (num[u] == k)
            return 1;
        u ++;
        if (u >= N)
            u = 0;
    }
    return 0;
}
int main() {
    memset(num, 0x3f, sizeof(num)); //要比所有可能存的数据大才行
    return 0;
}
```
