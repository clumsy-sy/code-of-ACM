int pi[M];
void prefix_function(char s[]) {
    for(int i = 1; s[i]; i ++) {
        int j = pi[i - 1];
        while(j > 0 && s[j] != s[i]) j = pi[j - 1];
        if(s[i] == s[j]) j ++;
        pi[i] = j;
    }
}