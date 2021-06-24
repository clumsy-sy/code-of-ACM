#include <bits/stdc++.h>
using namespace std;

int lowbit(int x)
{
    return x & -x;
}

void dfs(int k)
{
    if(k == 1)
    {
        cout << "2(0)";
        return ;
    }
    if(k <= 2)
    {
        cout << k;
        return;
    }
    stack<int> sta;
    int idx = -1;
    while( ++ idx <= 31)
    {
        if(k >> idx & 1)
        {
            sta.push(idx);
        }
    }
    bool flag = 0;
    cout << "2(";
    while(sta.size())
    {
        int x = sta.top(); sta.pop();
        if(x)
        {
            if(flag)cout << "+";
            dfs(x);
            flag = 1;
        }
    }
    cout << ")";
}

int main()
{
    int n;
    cin >> n;
    dfs(n);

    return 0;
}
