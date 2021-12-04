void prework(){
    mu[1] = 1;
    for (int i = 2; i < N; i ++ )
    {
        if (!st[i]) prime[cnt ++ ] = i, mu[i] = -1;
        for (int j = 0; prime[j] * i < N; j ++ )
        {
            st[prime[j] * i] = true;
            if (i % prime[j] == 0) break;
            mu[prime[j] * i] = -mu[i];
        }
    }
}