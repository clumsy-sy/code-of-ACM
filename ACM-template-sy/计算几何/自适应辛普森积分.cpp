double simpson(double l,double r){
	double mid = ( l + r ) / 2;
	return (r-l) * (f(l) + 4 * f(mid) + f(r)) / 6;
} // f 为被积函数
double asr(double l, double r, double s){
	double mid = ( l + r ) / 2;
	double L = simpson(l, mid), R = simpson(mid, r);
	if(fabs(s - L - R ) < eps) return L + R; // 根据设置的 eps 自适应拟合精度
	return asr(l, mid, L) + asr(mid, r, R);
}
printf("%.6lf\n", asr(l, r, simpson(l, r)));