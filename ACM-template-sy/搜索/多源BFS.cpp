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