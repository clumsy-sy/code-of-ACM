//以斐波那契数列为模板
const int M = 2;
struct ma{
    int a[M][M];//含有一个M*M的矩阵
    ma(){ memset(a,0,sizeof(a));}
    void unit(){
        a[0][0]=a[1][1]=1;//需符合矩阵乘法与递推关系
        a[0][1]=a[1][0]=0;
    }
    ma operator*(const ma &b)const {//定义矩阵乘法，并给操作符*
        ma ans;
        for(int i=0; i<M; i++)
            for(int j=0; j<M; j++)
                for(int k=0; k<M; k++)
                    ans .a[i][j]+=a[i][k]*b.a[k][j];
        return ans;
    }
    ma operator^(int n)const {//定义矩阵幂，并给操作符^
        ma ans; ans.unit();
        ma A=*this;
        while(n) {
            if(n&1)ans = ans*A;
            A = A*A;
            n>>=1;
        }
        return ans;
    }
    void show() {//打印
        for(int i=0; i<M; i++){
            for(int j=0; j<M; j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
    }
};
int main() {
    ma A;
    A.a[0][0]= 0;
    A.a[0][1]=A.a[1][0]=A.a[1][1]=1;

    ma F;
    F.a[0][0]=F.a[1][0]=1;
    F.a[0][1]=F.a[1][1]=0;

    int n = 8;
    ma ans=(A^n)*F;//矩阵快速幂
    ans.show();
    return 0;
}