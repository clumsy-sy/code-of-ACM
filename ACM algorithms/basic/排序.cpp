#include <iostream>
#include <algorithm>

using namespace std;

const int M = 1e5 + 7;

int num[M], tmp[M], res;

void quick_sort(int l, int  r)
{
    if(l == r) return ;
    int k = (num[l] + num[r]) >> 1, i = l - 1, j = r + 1;
    while(i < j){
        do i ++ ; while(num[i] < k);
        do j -- ; while(num[j] > k);
        if(i < j) swap(num[i], num[j]);
    }
    quick_sort(l, j); quick_sort(j + 1, r);
}

void merge_sort(int l, int r)
{
    if(l >= r)return;
    int mid = (l + r)>>1;
    merge_sort(l, mid), merge_sort(mid+1, r);
    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r){
        if(num[i] <= num[j]) tmp[k++] = num[i++];
        else    tmp[k++] = num[j++];
    }
    while(i <= mid) tmp[k++] = num[i++];
    while(j <= r)   tmp[k++] = num[j++];
    for(int x = l, y = 0; x <= r;) num[x++] = tmp[y++];
}

int kth_element(int l, int r, int k) // l , r是范围, k是所求第K个数
{
    if(l == r) return num[r];
    int mid = (num[l] + num[r]) >> 1, i = l - 1, j = r + 1;
    while(i < j){
        do i ++; while(num[i] < mid);
        do j --; while(num[j] > mid);
        if(i < j) swap(num[i], num[j]);
    }
    if(k <= j) return kth_element(l, j, k);
    return kth_element(j + 1, r, k);
}

int num[M], tmp[M], res;
void merge_sort(int l, int r)
{
    if(l >= r)return;
    int mid = (l + r)>>1;
    merge_sort(l, mid), merge_sort(mid+1, r);
    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r){
        if(num[i] <= num[j]) tmp[k++] = num[i++];
        else{
            tmp[k++] = num[j++];
            res += mid - i + 1; //res的值就是逆序数
        }
    }
    while(i <= mid) tmp[k++] = num[i++];
    while(j <= r)   tmp[k++] = num[j++];
    for(int x = l, y = 0; x <= r;) num[x++] = tmp[y++];
}

int main()
{
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i ++) cin >> num[i];

    quick_sort(0, n - 1);
    merge_sort(0, n - 1);
    sort(num, num + n); // 推荐，因为写起来快
    printf("%d\n", kth_element(0, n - 1, k));
    {
        merge_sort(0, n - 1); printf("%d\n", res);
    }

    return 0;
}