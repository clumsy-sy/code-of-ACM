const int MAXN = 2e5 + 7, MAXBIT = 31;
struct Trietree{
    int tr[MAXN * 31][2], cnt, tag[MAXN * 31];
    void init() {
        fill(tr[0], tr[0] + MAXN * 2, 0);
        fill(tag, tag + MAXN, 0);
        cnt = 0;
    }
    void insert(int num) {
        int idx = 0;     // idx 与 cnt 的起始下标应当相同
        for(int i = MAXBIT; ~i; i--) {
            int bit = (num >> i) & 1;
            if(!tr[idx][bit]) 
                tr[idx][bit] = ++ cnt;
            idx = tr[idx][bit];
        }
        tag[idx] = num;
    }
    int find_max(int num) {
        int idx = 0;
        for(int i = MAXBIT; ~i; i --) {
            int bit = (num >> i) & 1;
            if(tr[idx][bit ^ 1]) // 每一位尽量相反，则异或最大
                idx = tr[idx][bit ^ 1];
            else 
                idx = tr[idx][bit];
        }
        return tag[idx];
    }
}Trie;
------------------------------------------------------------
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 7, MAXBIT = 31;
struct Trietree {
    int tr[MAXN * MAXBIT][2], cnt, tag[MAXN * MAXBIT];
    void init() {  //
        fill(tr[0], tr[0] + MAXN * 2 * MAXBIT, 0);
        fill(tag, tag + MAXN * MAXBIT, 0);
        cnt = 0;
    }
    void insert(int num, int id) {
        int idx = 0;
        for (int i = MAXBIT; ~i; i--) {
            int bit = (num >> i) & 1;
            if (!tr[idx][bit])
                tr[idx][bit] = ++cnt;
            idx = tr[idx][bit];
            tag[idx] = max(tag[idx], id);  // 记录当前节点有值的最右端点
        }
    }
    int find_max(int num, int k) {
        int idx = 0, res = -1;
        for (int i = MAXBIT; ~i; i--) {
            int bit = (num >> i) & 1;
            if ((k >> i) & 1) {         //如果在这位上为0，则 此位异或起来为 1 才行
                idx = tr[idx][bit ^ 1];
            } else {                    //如果在这位上为0，则 此位异或起来为 1 必定满足条件
                if (tr[idx][bit ^ 1])
                    res = max(res, tag[tr[idx][bit ^ 1]]);
                idx = tr[idx][bit];
            }
            if (!idx) break;
        }
        if (idx) res = max(res, tag[idx]);
        return res;
    }
} Trie;
int a[MAXN], pre[MAXN];
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        Trie.init();
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            pre[i] = a[i] ^ pre[i - 1];  //异或前缀和
        }
        int anl = -1, anr = n + 1;
        for (int i = 0; i <= n; i++) { // 从 0 开始
            int now = Trie.find_max(pre[i], k);   // 寻找满图条件的最大的左端点
            if (now >= 0 && i - now < anr - anl)  // 存在符合条件的端点并且长度更小
                anl = now, anr = i;
            Trie.insert(pre[i], i);  // 插入当前的前缀和
        }
        if (anl > -1)
            printf("%d %d\n", anl + 1, anr);
        else
            printf("-1\n");
    }
    return 0;
}