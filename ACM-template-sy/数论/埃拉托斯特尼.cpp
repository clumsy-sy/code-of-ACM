void get_primes(int n) {
    for(int i = 2; i <= n; i++) {
        if(!st[i]){ 
            prime[cnt++] = i;
            for(int j = i; j <= n; j += i)
                st[j] = true;
        }
    } 
}