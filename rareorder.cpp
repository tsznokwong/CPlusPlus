#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

int main(){
    int n,i=0;
    char dict[101][21],c[101][2];
    bool a[26],b[26];
    for(int i=0;i<26;++i)a[i]=false;
 //   scanf("%d",&n);
    
    
    int len,plen,k=0;
    scanf("%s",&dict[i]);
    while(dict[i][0]!='#'){
//    for(int i=0;i<n;++i){
//        scanf("%s",&dict[i]);
        len=strlen(dict[i]);
        for(int j=0;j<len;++j)
            a[dict[i][j]-65]=true;
        for(int j=0;i && j<len && j<plen;++j)
            if(dict[i-1][j]!=dict[i][j]){
                c[k][0]=dict[i-1][j];
                c[k][1]=dict[i][j];
                ++k;
                break;
            }
        plen=len;
        scanf("%s",&dict[++i]);
    }
    

    
    int cnt=0;
    for(int i=0;i<26;++i){
        if(a[i])
            ++cnt;
        b[i]=a[i];
    }
    for(int i=0;i<cnt;++i){
        int m=0;
        for(int j=0;j<k;++j)
            b[c[j][1]-65]=false;
        for(int j=0;j<26;++j)
            if(b[j]){
                printf("%c",j+65);
                
                for(int z=0;z<k;++z){
                    if(z<k-1-m && c[z][0]==j+65){
                        ++m;
                        swap(c[z][0],c[k-m][0]);
                        swap(c[z][1],c[k-m][1]);
                    }
                }
                k=k-m;
                a[j]=false;
                break;
            }
        for(int j=0;j<26;++j)
            b[j]=a[j];
        
    }
    for(int j=0;j<26;++j)
        if(b[j])printf("%c",j+65);
    printf("\n");
    return 0;
}