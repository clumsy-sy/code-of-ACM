#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
map<ll, ll> top, down;
bool check_top(ll x, ll y) {
    auto i = top.lower_bound(x);
    if (i == top.end()) return 0;
    if (i->first == x) return y <= i->second;
    if (i == top.begin()) return 0;
    auto j = i; j--;
    return (i->first - j->first) * (y - j->second) - (i->second - j->second) * (x - j->first) <=0;
}
bool check_down(ll x, ll y) {
    auto i = down.lower_bound(x);
    if (i == down.end()) return 0;
    if (i->first == x) return y >= i->second;
    if (i == down.begin()) return 0;
    auto j = i;
    j--;
    return (i->first - j->first) * (y - j->second) -(i->second - j->second) * (x - j->first) >= 0;
}
bool delete_top(map<ll,ll>::iterator i) {
    if (i == top.begin()) return 0;
    auto j = i, k = i;
    j--, k++;
    if (k == top.end()) return 0;
    if ((i->first - j->first) * (k->second - j->second) - (i->second - j->second) * (k->first - j->first) >= 0) {
        top.erase(i);
        return 1;
    }
    return 0;
}
bool delete_down(map<ll,ll>::iterator i) {
    if (i == down.begin()) return 0;
    auto j = i, k = i;
    j--, k++;
    if (k == down.end()) return 0;
    if ((i->first - j->first) * (k->second - j->second) - (i->second - j->second) * (k->first - j->first) <= 0) {
        down.erase(i);
        return 1;
    }
    return 0;
}
void insert_top(ll x, ll y) {
    if (check_top(x, y)) return;
    top[x] = y;
    auto i = top.find(x), j = i;
    if (i != top.begin()) {
        j--;
        while (delete_top(j++)) j--;
    }
    if (++j != top.end())
        while (delete_top(j--)) j++;
}
void insert_down(ll x, ll y) {
    if (check_down(x, y)) return;
    down[x] = y;
    auto i = down.find(x), j = i;
    if (i != down.begin()) {
        j--;
        while (delete_down(j++)) j--;
    }
    if (++j != down.end())
        while (delete_down(j--)) j++;
}
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        ll op , x , y ;
        scanf("%lld%lld%lld", &op, &x, &y);
        if (op == 1) {
            insert_top(x, y); //插入上凸包
            insert_down(x, y); //插入下凸包
        } else {
            if (check_top(x, y) && check_down(x, y))
                puts("YES");
            else
                puts("NO");
        }
    }
    return 0;
}