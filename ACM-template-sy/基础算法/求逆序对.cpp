// 求逆序对 O(nlogn)
int num[M], tmp[M], res;
void merge_sort(int l, int r) {
    if(l >= r)return;
    int mid = (l + r)>>1;
    merge_sort(l, mid), merge_sort(mid+1, r);
    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r) {
        if(num[i] <= num[j]) tmp[k++] = num[i++];
        else {
            tmp[k++] = num[j++];
            res += mid - i + 1; //res的值就是逆序数
        }
    }
    while(i <= mid) tmp[k++] = num[i++];
    while(j <= r)   tmp[k++] = num[j++];
    for(int x = l, y = 0; x <= r;) num[x++] = tmp[y++];
}
// 归并排序可用来求逆序对
// 原理：因为在合并过程中，当num[i] > num[j]，在前半部分中比num[i]大的都 > num[j]，将num[j] 放在 num[i]前面的话，逆序对需要加上 mid - i + 1;
// 相比较于树状数组求逆序对，归并排序不需要离散化。