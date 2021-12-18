#include<cstdio>
#include<cmath>
#include<slgorithm>
using namespace std;
int main(){
    int n,m,maxx,maxy,maxs=0;
    double maxl=0;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i){
        int tx,ty;
        scanf("%d%d",&tx,&ty);
        double sq=sqrt(tx*tx+ty*ty);
        if(sq>maxl){
            maxl=sq;
            maxx=tx;
            maxy=ty;
            maxs=i+1;
        }
    }
    
    printf("%d %d %d %lf\n",maxx,maxy,maxs,maxl);
    int r[1000][2];
    for(int i=0;i<m;++i){
        scanf("%d%d",r[i][0],r[i][1]);
        for(j=i;j>0;--j){
            if(r[j][0]<r[j-1][0]){
                swap(r[j][0],r[j-1][0]);
                swap(r[j][1],r[j-1][1]);
            }
            if(r[j][1]<r[j-1][1]){
                swap(r[j][0],r[j-1][0]);
                swap(r[j][1],r[j-1][1]);
            }
        }
    }
    
    return 0;
}