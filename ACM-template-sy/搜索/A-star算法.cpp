// 八数码问题，启发函数哈密顿距离（dist = |x - x0| + |y - y0|）
typedef pair<int, string> PIS;
int f(string now) {// 启发函数
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
    int ni = 0;     //求逆序数，当逆序数为奇数，必然不能转换到原始状态
    for(int i = 0; i < 9; i ++)               
        for(int j = i + 1; j < 9; j ++) {
            if(start[i] == 'x' || start[j] == 'x') continue;
            if(start[i] > start[j]) ni ++;
        }
        
    if(ni & 1) puts("unsolvable");
    else bfs(start, end);
    return 0;
}
//求第 K 短路，启发函数为Dijkstra
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