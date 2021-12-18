#include<cstdio>
#include<cstring>
long long int m=1000000007;
long long int mod(long long int b,long long int p){
    if(p==0)return 1;
    if(p%2) return ((b%m)*(mod(b,p-1)%m))%m;
    else return (mod(b,p/2)%m*(mod(b,p/2)))%m;
}
int main(){
    int n;
    long long s=1;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        int tmp;
        scanf("%d",&tmp);
        s*=tmp;
    }
    printf("%d\n",(int)mod(s,n)%m);
    return 0;
}
/*int main(){
    char s[2101],t[2101];
    scanf("%s%s",s,t);
    int sl=strlen(s),tl=strlen(t);
    int ins[2101][2],size=0;
    bool can=true;
    int ptr=0;
    while(ptr<tl){
        int max=-1,p,p2,pt=-1,dir=0;
        for(int i=0;i<sl;++i){
            //printf("%d\n",i);
            p=ptr;
            p2=i;
            if(s[i]==t[p]){
                bool rev=(i<1||p>=tl)?false:s[i-1]==t[p+1];
                bool asc=(i>=sl||p>=tl)?false:s[i+1]==t[p+1];
                int cnt=0;
                if(cnt>max){
                    pt=i;
                    dir=0;
                    max=cnt;
                }
                if(rev){
                    while((p2>0&&p<tl-1)&&s[p2-1]==t[p+1]){
                        ++cnt;
                        --p2;
                        ++p;
                    }
                    if(cnt>max){
                        pt=i;
                        dir=-1;
                        max=cnt;
                    }
                }
                p=ptr;
                p2=i;
                if(asc){
                    while((p2<sl-1&&p<tl-1)&&s[p2+1]==t[p+1]){
                        //printf("p2:%d %d p:%d %d\n",p2,s[p2],p,t[p]);
                        ++cnt;
                        ++p2;
                        ++p;
                        
                    }
                    if(cnt>max){
                        pt=i;
                        dir=1;
                        max=cnt;
                    }
                }
            }
        }
        //printf("max: %d pt: %d dir: %d\n",max,pt,dir);
        if(max!=-1){
            ins[size][0]=pt+1;
            if(dir==-1)
                ins[size][1]=pt-max+1;
            else
                ins[size][1]=pt+max+1;
            ++size;
            ptr+=max+1;
        }
        else{
            can=false;
            printf("-1\n");
            break;
        }
        //printf("%d\n",ptr);
    }
    if(can){
        printf("%d\n",size);
        for(int i=0;i<size;++i)
            printf("%d %d\n",ins[i][0],ins[i][1]);
    }
    return 0;
}*/