void quick_sort(int l, int  r) {
    if(l == r) return ;
    int k = (num[l] + num[r]) >> 1, i = l - 1, j = r + 1;
    while(i < j) {
        do i ++ ; while(num[i] < k);
        do j -- ; while(num[j] > k);
        if(i < j) swap(num[i], num[j]);
    }
    quick_sort(l, j); quick_sort(j + 1, r);
}
int num[M], tmp[M];
void merge_sort(int l, int r) {
    if(l >= r)return;
    int mid = (l + r)>>1;
    merge_sort(l, mid), merge_sort(mid+1, r);
    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r) {
        if(num[i] <= num[j]) tmp[k++] = num[i++];
        else tmp[k++] = num[j++];
    }
    while(i <= mid) tmp[k++] = num[i++];
    while(j <= r)   tmp[k++] = num[j++];
    for(int x = l, y = 0; x <= r;) num[x++] = tmp[y++];
}
