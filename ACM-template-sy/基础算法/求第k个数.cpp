int kth_element(int l, int r, int k) {
    if(l == r) return num[r];
    int mid = (num[l] + num[r]) >> 1, i = l - 1, j = r + 1;
    while(i < j) {
        do i ++; while(num[i] < mid);
        do j --; while(num[j] > mid);
        if(i < j) swap(num[i], num[j]);
    }
    if(k <= j) return kth_element(l, j, k);
    return kth_element(j + 1, r, k);
}
// 与快排相比，求第K个数每次只需要递归一半，所以复杂度为 O(N)；
// STL函数：nth_element(begin(), begin()+k-1, end());