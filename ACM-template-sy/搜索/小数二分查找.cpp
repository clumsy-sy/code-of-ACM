const double esp = 1e-8;
int main() {
    double t;
    scanf("%lf",&t);
    double l = 0, r = t, mid;
    if(t<0)swap(l,r);   //判断一下区间正负
    //法一：
    while(r - l > esp) {
        mid = (l + r)/2;
        if(mid*mid*mid<t) l = mid;
        else if(mid*mid*mid>t) r = mid;
        else break;
    }
    mid = (l + r)/2;
    //法二
    while(r - l > esp) {
        mid = (l + r)/2;
        if(mid*mid*mid <= t) l = mid;
        else r = mid;
    }
    //其他
    int k = 100;
    while(k --)   {  //防止不必要的计算导致超时
        mid = (l + r)/2;
        if(mid*mid*mid <= t) l = mid;
        else r = mid;
    }
    return 0;
}
