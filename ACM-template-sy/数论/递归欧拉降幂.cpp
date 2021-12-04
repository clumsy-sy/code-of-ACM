ll dfs(ll mod){
    if(mod == 1) return 0;
    return quick_pow(2, dfs(phi[mod]) + phi[mod], mod);
}