int son[N][26]; // 其中存放的是：子节点对应的idx。其中son数组的第一维是：父节点对应的idx，第第二维计数是：其直接子节点('a' - '0')的值为二维下标。
int cnt [N];    // 以“abc”字符串为例，最后一个字符---‘c’对应的idx作为cnt数组的下标。数组的值是该idx对应的个数。
int idx = 0;    // 将该字符串分配的一个树结构中，以下标来记录每一个字符的位置。方便之后的插入和查找。
char str[N];
void insert(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }// 此时的p就是str中最后一个字符对应的trie树的位置idx。
    cnt[p]++;//结尾标记
}
int query(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];//如果没有单词在此结尾过依旧会返回0
}
int main() {
    int n;
    scanf("%d", &n);
    char op[2];
    while (n--) {
        scanf("%s%s", op, str);
        if (op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }
    return 0;
}
//用时间换取空间的动态实现（跑的更慢空间更小）
int N,M,K;
struct node{
    node* nxt[26];
    int val;
}*root;
char str[100];
node* newnode(){
    node *p = new node();
    p->val = 0;
    for(int i = 0 ; i < 26; i ++) p->nxt[i] = NULL;
    return p;
}
void insert(char *s) {
    node* p = root;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(p->nxt[id] == NULL) p->nxt[id] = newnode();
        p = p->nxt[id];
    }
    p->val = 1;
}
void query(char *s) {
    node* p = root;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(p->nxt[id] == NULL){
            puts("WRONG");
            return; 
        }
        p = p->nxt[id];
    }
    if(p->val == 0) puts("WRONG");
    else if(p->val == 1){
        puts("OK"); p->val = 2;
    }else{
        puts("REPEAT");
    }
}
void deal(node *p){
    for(int i = 0 ; i < 26; i ++) if(p->nxt[i]) deal(p->nxt[i]);
    free(p);
}