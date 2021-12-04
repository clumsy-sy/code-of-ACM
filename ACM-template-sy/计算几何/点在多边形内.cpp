//winding number 算法判断点是否在多边形内，若点在多边形(内 : 1，外 ： 0，上 ： -1）
int isPointInPolygon(Point p, vector<Point> poly){
    int wn = 0;
    int n = poly.size();
    for(int i = 0; i < n; ++i){
        if(on(p, Seg(poly[i], poly[(i+1)%n]))) return -1;
        int k = sign((poly[(i+1)%n] - poly[i]) ^  (p - poly[i]));
        int d1 = sign(poly[i].y - p.y), d2 = sign(poly[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn ++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn --;
    }
    if(wn != 0) return 1;
    return 0;
}
bool judge(Point a,Point L,Point R){//判断AL是否在AR右边
    return sign((L-a) ^ (R-a)) > 0;//必须严格以内
}
//二分判断点是否在凸多边形内，若点在多边形(内 : 1，外 ： 0，上 ： -1）
int isPointInConvexPolygon(Point a, vector<Point> poly){
    int n = poly.size();//点按逆时针给出(一定要满足这个条件)
    if(judge(poly[0], a, poly[1]) || judge(poly[0], poly[n - 1], a))return 0;//在P[0_1]或P[0_n - 1]外
    if(on(a, Seg(poly[0], poly[1])) || on(a, Seg(poly[0], poly[n - 1])))return -1;//在P[0_1]或P[0_n-1]上
    int l = 1,r = n - 2;
    while(l < r){//二分找到一个位置pos使得P[0]_A在P[1_pos],P[1_(pos+1)]之间
        int mid = (l + r) >> 1;
        if(judge(poly[1], poly[mid], a))l = mid;
        else r = mid - 1;
    }
    if(judge(poly[l], a, poly[l + 1]))return 0;//在P[pos_(pos+1)]外
    if(on(a, Seg(poly[l], poly[l + 1])))return -1;//在P[pos_(pos+1)]上
    return 1;
}
//【判断多边形A与多边形B是否相离】 
int judge_PP(vector<Point> A, vector<Point> B){
    for(int i = 0; i < A.size(); ++ i) {
        for(int j = 0; j < B.size(); ++ j) {
            if(seg_intersection(Seg(A[i], A[(i + 1) % A.size()]), Seg(B[j], B[(j + 1) % B.size()])))return 0;//两线段相交
            if(isPointInConvexPolygon(A[i], B) || isPointInConvexPolygon(B[j], A))return 0; //点包含在内
        }
    }
    return 1;
}