typedef unsigned long long ull;
const ull base = 131, M = 1e5 + 7, mod = 1e9 + 7;
char s[M];
ull myhash[M], power[M]; //myhash 里面存算到某位时的 Hash 值，power 存 base 的幂次（子串查询才需要）
ull get_hash(char *s) {
    ull value = 0;
    power[0] = 1;
    for (int i = 1; s[i]; i++) {
        value = (value * base + s[i]) % mod;
        myhash[i] = value;
        power[i] = power[i - 1] * base % mod;
    }
    return value;//返回最终字符串的 Hash 值
}
//计算某段的 Hash 值
ull get_sub_hash(int l, int r) {
    return (myhash[r] - (myhash[l - 1] * power[r - l + 1]) % mod + mod) % mod;
}
/*扩展
字符串hash其实和进制进位有一些相似，我们想到了这一点就可以线性的时间正着求前缀字符串的hash值和前缀字符串的倒转的hash值
当我们求正序前缀的hash的时候，每一次操作就相当于在字符串的最前面插入一个值，所以我们要首先处理出每一位的指数级ans,然后f[i] = f[i - 1] + str[i] * ans;
当我们求逆序前缀的hash值的时候，每一次操作就相当于在字符串的最后插入一个值，整个字符串就要左移一位然后把这个位塞进去 也就是f [i]= f[i - 1] * tmp + str[i];
*/
//例题 判断一个字符串的每一个前缀是否相等, abaehjsd -> aba(正反)
ULL ans = 1;
ULL f1[maxn],f2[maxn];
char str[maxn];
for(int i = 1 ; i <= l; i ++){
    if (str[i] >= '0' && str[i] <= '9')str[i] = str[i] - '0';
    else if (str[i] >= 'a' && str[i] <= 'z')str[i] = str[i] - 'a' + 10;
    else str[i] = str[i] - 'A' + 36;
    f1[i] = f1[i - 1] * 131 + str[i];
    f2[i] = (f2[i - 1] + str[i] * ans);
    ans *= 131;
    if (f1[i] == f2[i]){
        puts("i is equal");
    }
}