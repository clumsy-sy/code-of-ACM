vector<int> add(vector<int> &a, vector<int> &b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) t += a[i];
        if (i < b.size()) t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if (t) c.push_back(t);
    return c;
}
bool cmp(vector<int> &a, vector<int> &b) {
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] > b[i];
    return true;
}
vector<int> sub(vector<int> &a, vector<int> &b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < (int)a.size(); i++) { //保证a > b
        t = a[i] - t;
        if (i < (int)b.size()) t -= b[i];
        c.push_back((t + 10) % 10); //同时覆盖t>=0, t<0两种情况
        if (t < 0) t = 1;
        else t = 0;
    }
    while (c.size() > 1 && c.back() == 0) 
        c.pop_back(); //去掉前导0；
    return c;
}
vector<int> mul(vector<int> &a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < (int)a.size() || t; i++) {
        if (i < (int)a.size())
            t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}
vector<int> div(vector<int> &a, int b, int &mod) {// r为余数
    vector<int> c;
    mod = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        mod = mod * 10 + a[i];
        c.push_back(mod / b);
        mod %= b;
    }
    reverse(c.begin(), c.end());
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}
void print_vec(vector<int> now) { //倒着输出vector
    for (int i = now.size() - 1; ~i; i--)
        cout << now[i];
    cout << endl;
}
vector<int> read() {//读入字符串，转化为vector类型（里面是逆序）
    string s; cin >> s;
    vector<int> a;
    for (int i = s.size() - 1; ~i; i--)
        a.push_back(s[i] - '0');
    return a;
}
int main() {
    int op, num, mod;
    cin >> op;
    if (op == 1) {
        vector<int> a = read(), b = read();
        vector<int> c = add(a, b);
        print_vec(c);
    } else if (op == 2) {
        vector<int> a = read(), b = read();
        if (!cmp(a, b)) { //减法情况需要先判断两个数的大小，决定符号
            swap(a, b);
            printf("-");
        }
        vector<int> c = sub(a, b);
        print_vec(c);
    } else if (op == 3) {
        vector<int> a = read();
        cin >> num;
        vector<int> c = mul(a, num);
        print_vec(c);
    } else if (op == 4) {
        vector<int> a = read();
        cin >> num;
        vector<int> c = div(a, num, mod);//mod 为 余数
        cout << mod << endl;
        print_vec(c);
    }
    return 0;
}