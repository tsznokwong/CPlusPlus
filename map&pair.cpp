#include<cstdio>
#include<map>
#include<vector>
using namespace std;
int main(){
    int n,m,x,y;
    scanf("%d %d",&n,&m);
    map<int,pair<vector<int>,vector<int> > > b;
    for(int i=0;i<n;++i){
        scanf("%d %d",&x,&y);
        b[y].first.push_back(x);
    }
    for(int i=0;i<m;++i){
        scanf("%d %d",&x,&y);
        b[y].second.push_back(x);
    }
    
    for(map<int,pair<vector<int>,vector<int> > >::iterator it = b.begin(); it != b.end();++it){
        for(int i=0;i<it->second.first.size();++i){
            if(it->second.second.size()==0)
                printf("%d %d null\n",it->second.first[i],it->first);
            for(int j=0;j< it->second.second.size();++j)
                printf("%d %d %d\n",it->second.first[i],it->first,it->second.second[j]);
            
        }
    }
    return 0;
}