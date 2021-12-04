int n;
string a[6], b[6];
int extend(queue<string> &now, unordered_map<string, int> &da, unordered_map<string, int> &db, string a[], string b[]){
    for(int cnt = now.size(), c = 0; c < cnt; c ++) {//只扩展一遍当前队列中已存在的元素，否则退化为普通bfs，会TLE
        string k = now.front();
        now.pop();
        for(int i = 0; i < k.size(); i ++) {
            for(int j = 0; j < n; j ++) {
                if(k.substr(i, a[j].size()) == a[j]) {
                    string change = k.substr(0, i) + b[j] + k.substr(i + a[j].size());
                    if(da.count(change)) continue;
                    if(db.count(change)) return da[k] + db[change] + 1;
                    da[change] = da[k] + 1;
                    now.push(change);
                }
            }
        }
    }
    return INF;
}
int bfs(string start, string end) {
unordered_map<string, int> permp, sufmp; //头、尾
    queue<string> per, suf; //头尾队列
    per.push(start);
    suf.push(end);
    permp[start] = 0;
    sufmp[end]   = 0;
    while(per.size() && suf.size()) {// 如果有对列空了，说明不
        int ans;       //双向广搜，每次扩展的队列是当前个数比较少的
        if(per.size() <= suf.size()) ans = extend(per, permp, sufmp, a, b);
        else ans = extend(suf, sufmp, permp, b, a);
        if(ans != INF) return ans; //起点与终点第一次相遇便是最小值，直接返回
    }
    return INF;
}
int main() {
    string A, B;
    cin >> A >> B;
    while(cin >> a[n] >> b[n]) n ++;
    int ans = bfs(A, B);
    if(ans > 10) puts("NO ANSWER!");
    else printf("%d\n", ans);
    return 0;
}