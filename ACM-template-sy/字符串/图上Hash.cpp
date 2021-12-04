ULL Hash[maxn],id[maxn];
for(int i = 1; i <= N ; i ++ ) Hash[i] = id[i] = id[i - 1] * 3;
for(int i = 1; i <= M ; i ++ ){
    int u,v; Sca2(u,v);
    add(u,v); add(v,u);
    Hash[u] += id[v]; Hash[v] += id[u];
}