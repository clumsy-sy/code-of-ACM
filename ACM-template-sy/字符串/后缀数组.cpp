/*  后缀数组
(1)将字符串的所有后缀按照字典序从小到大排序
sa[i]表示排名第i的后缀的下标 , rak[i]表示下标为i的后缀的排名
(2)Height数组
lcp(x,y)：字符串x与字符串y的最长公共前缀，在这里指x号后缀与与y号后缀的最长公共前缀
height[i]：lcp(sa[i],sa[i−1])，即排名为i的后缀与排名为i−1的后缀的最长公共前缀
H[i]：height[rak[i]]，即i号后缀与它前一名的后缀的最长公共前缀
应用：
1.两个后缀的最大公共前缀：lcp(x,y)=min(heigh[x−y])， 用rmq维护，O(1)查询
2.可重叠最长重复子串：Height数组里的最大值
3.不可重叠最长重复子串 POJ1743：首先二分答案x，对height数组进行分组，保证每一组的minheight都>=x
依次枚举每一组，记录下最大和最小长度，多sa[mx]−sa[mi]>=x那么可以更新答案
4.本质不同的子串的数量:枚举每一个后缀，第i个后缀对答案的贡献为len−sa[i]+1−height[i]
*/
#include <iostream>
#include <cstring>
using namespace std;
const int M = 1e6 + 7;
int n, m;
char s[M];
int sa[M], rk[M], height[M], x[M], y[M], cnt[M];
//sa 数组存各排名对应的后缀编号，rk 是各后缀编号的排名
//Height 记录相邻排名的最长公共前缀
// x 是第一关键字， y 是第二关键字， cnt 是计数数组
void get_sa() {
    //初始的基数排序
    for(int i = 1; i <= n; i ++) x[i] = s[i], cnt[x[i]] ++;
    for(int i = 2; i <= m; i++) cnt[i] += cnt[i-1];
    for(int i = n; i ; i--) sa[cnt[x[i]]--] = i;

    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++)
            y[++num] = i; //此处不足补充空格的排在前面
        for (int i = 1; i <= n; i++)
            if (sa[i] > k)
                y[++num] = sa[i] - k;
        //前k位被不足的子串占据，所以第二关键字后面排名的是第一关键字排序位置-k
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[x[i]]++;
        for (int i = 2; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) sa[cnt[x[y[i]]]--] = y[i], y[i] = 0;

        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i++) {
            bool due = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]);
            //新的相邻排名，其位置的老排名相同，那它的新排名其实是并列的
            if (!due) num++; //只有不并列，排名才会向前走
            x[sa[i]] = num; //排名i的位置，其连续的排名是num，并列的相同
        }
        if (num == n) break;
        m = num;
    }
}
void get_height() {
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 1) continue; //排名第1的不需计算，
        if (k) k--;               //去掉前面已经比较的一个字符
        int j = sa[rk[i] - 1]; //这个位置也许与前面比较的j位置不同，
                               //但是去掉前面一个字符后,相同部分不会少
        while (i + k <= n && s[i + k] == s[j + k]) k ++;//从k位置开始比较
        height[rk[i]] = k; //排名rk[i]的height
    }
}
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1), m = 'z';
    get_sa();
    get_height();
    for(int i = 1; i <= n; i ++)
        printf("%d%c", sa[i], i == n ? '\n' : ' ');
    for(int i = 1; i <= n; i ++)
        printf("%d%c", height[i], i == n ? '\n' : ' ');
    return 0;
}