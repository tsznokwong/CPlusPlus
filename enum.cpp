#include<immintrin.h>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<string>
#include<cstddef>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<set>
#include<thread>
#include<locale>
#include<cwchar>
#include<regex>
#include<climits>
#include<termios.h>
#include<unistd.h>
#include<sys/stat.h>


using namespace std;

int main() {
    char s[] = "Hmvigxsvc:CsyGsqtpixihQi";
    int l = strlen(s);
    for(int i = 0 ;i < l;++i){
        if(s[i] >= 'a')
            s[i] -= 32;
    }
    
    
    for(int j= 0;j<26;++j){
        for(int i = 0 ;i < l;++i){
            ++s[i];
            if(s[i]>'Z')
                s[i]='A';
        }
        printf("%s\n", s);
    }
    return 0;
}







