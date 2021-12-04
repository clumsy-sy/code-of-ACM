//求出ax + by = c的一组可行解
//有解的前提 gcd(a,b)|c ,否则无解
// (x % b + b) % x 可得最小正整数解
int exgcd(int a, int b, int &x, int &y) {
    if(a == 0 && b == 0) return -1;
    if(!b) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -=  a / b * x;
    return g;
}
