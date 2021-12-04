const int M = 1e5+7;
int   p[M];
int main() {
    int    n,t;
    cin>>n>>t;
    for(int i=0; i<n; i++) cin>>p[i];
    //判断左右边界的二分（注意：有可能查找不到）
    //左右边界判断重点，某一边满足某一条件
    int l = 0, r = n-1, mid;
    while(l<r){             //左边界
        mid = (l+r)>>1;
        if(p[mid]<t) l = mid + 1;
        else r = mid;
    }
    l = 0, r = n-1;
    while(l<r){             //右边界
        mid = (l+r+1)>>1;   //注意一定要+1，否则死循环
        if(p[mid]<=t) l = mid;
        else r = mid - 1;
    }
    //二分整数查找
    l = 0, r = n-1;
    while(l<=r) {     //如果取的数组末尾后一位的话是l = r
        mid = (l+r)>>1;   //也可以mid = l+(r-l)/2;(尤其是迭代器的时候)
        if(p[mid]<t){l = mid + 1; continue;}
        else if(p[mid]>t) {r = mid - 1; continue;}
        else break;
    }
    return 0;
}
