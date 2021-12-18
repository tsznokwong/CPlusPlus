#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
//globe variables
char board[8][8];
bool player=false,comf=false;
char p1[10]="Player 1",p2[10]="Player 2",comp[2]="N";
int rex=-1,rey=-1,cnt=0;
int level=0;
//initialize
void initialize(){
    player=false;
    cnt=0;
    strcpy(p1,"Player 1");
    strcpy(p2,"Player 2");
    for(int i=0;i<7;++i)
        for(int j=0;j<7;++j)
            if(i%2 && j%2)board[i][j]=i/2*3+j/2+49;
            else board[i][j]=43;
    printf("Welcome tic-tac-toe\n");
    printf("vs computer?(y/n)\n");
    //system("cls");
    scanf("%s",comp);
    comp[0]=comp[0]%32+64;
    if(comp[0]=='Y'){
        strcpy(p2,"Computer");
        comf=rand()%2;
        if(comf){
            swap(p1,p2);
            player=true;
        }
        printf("Level: 1 kid   2 beginner   3 intermediate   4 expert\n");
        scanf("%d",&level);
    }
}
//print board
void print(){
    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j)
            printf("%c%c",board[i][j]>97?board[i][j]-32:board[i][j],j<7?' ':'\n');
}
//check win condition
char check(){
    for(int i=1;i<7;i+=2){
        bool same1=true,same2=true;
        int x=board[i][1],y=board[1][i];
        for(int j=3;j<7;j+=2){
            if(board[i][j]!=x)same1 = false;
            if(board[j][i]!=y)same2 = false;
        }      
        if(same1||same2){
            if(same1)return x;
            else return y;
        }
    }
    int x=board[1][1],y=board[5][1];
    bool same1=true,same2=true;
    for(int i=3;i<6;i+=2){ 
        if(board[i][i]!=x)same1=false;
        if(board[6-i][i]!=y)same2=false;
    }
    if(same1||same2){
        if(same1)return x;
        else return y;
    }
    else return 0;
}
//ai algorithm
void ai(){
    bool block=false,fork=false;
    rex=rey=-1;
    //win/block/fork/blockfork
    if(level>1)
    for(int i=1;i<7;i+=2)
        for(int j=1;j<7;j+=2){
            if(board[i][j]>97)continue;        
            for(int t=0;t<2;t+=1){
                if(t==0)board[i][j]=111;
                else board[i][j]=120;
                char win=check();
                if(win){
                    board[i][j]=i/2*3+j/2+49;
                    rex=i/2;
                    rey=j/2;
                    block=true;
                    if(win==120)
                        return;
                }
                //fork/blockfork
                if(level<4||block){
                    board[i][j]=i/2*3+j/2+49;
                    continue;
                }
                int count=0;
                for(int k=1;k<7;k+=2)
                    for(int l=1;l<7;l+=2){
                        if(board[k][l]>97)continue;
                        board[k][l]=board[i][j];
                        if(check()==board[i][j])
                            ++count;
                        board[k][l]=k/2*3+l/2+49;
                    }
                if(count>=2){
                    if(!fork){
                        rex=i/2;
                        rey=j/2;
                    }
                    if(board[i][j]==120)
                        fork=true;
                }
                board[i][j]=i/2*3+j/2+49;
            }
        }
    if(rex!=-1&&level>2)
        return;
    //emptycenter
    if(level>1)
    if(board[3][3]<97){
        rex=rey=1;
        return;
    }
    //opposite corner
    if(level>2)
    for(int i=1;i<7;i+=4)
        for(int j=1;j<7;j+=4){
            if(board[i][j]==111&&board[(i+4)%8][(j+4)%8]<97){
                rex=((i+4)%8==5?2:0);
                rey=((j+4)%8==5?2:0);
                return;
            }
        }
    //emptycorner
    if(level>2)
    for(int i=1;i<7;i+=4)
        for(int j=1;j<7;j+=4){
            if(board[i][j]<97){
                rex=i/2;
                rey=j/2;
                return;
            }
        }
    //emptyside
    if(level>2)
    for(int i=1;i<4;i+=2)
        for(int j=3;j<6;j+=2,i+=2){
            if(board[i][j]<97){
                rex=i/2;
                rey=j/2;
                return;
            }
            if(board[j][i]<97){
                rex=j/2;
                rey=i/2;
                return;
            }
        }
    int r=rand()%9+1;
    while(board[r/3*2+1][r%3*2+1]>=97)
        r=rand()%9+1;
    --r;
    rex=r/3;rey=r%3;
}
//play
void input(){
    int n,x,y;
    if((!player&&comp[0]=='Y')||comp[0]!='Y'){
        printf("Round %d :\n",cnt+1);
        printf("player %d enter:\n",player+1);
        scanf("%d",&n);
        --n;
        x=n/3;y=n%3;
    }
    else if(comp[0]=='Y'){
        ai();
        x=rex;
        y=rey;
    }
    if(board[x*2+1][y*2+1]<111){
        player=!player;
        ++cnt;
        board[x*2+1][y*2+1]=player?111:120;
    }
    else printf("Error! Please try again\n");
}
int main(){
    srand(time(NULL));
    char again[2]="Y";
    while(again[0]!='N'){
        again[0]='N';
        initialize();
        char win=0;
        while(cnt!=9&&!win){
            //system("cls");
            print();
            input();
            win=check();
            if(win){
                if(comp[0]=='Y'&&comf)printf("%s Win!\n",win==120?p1:p2);
                else printf("%s Win!\n",win==111?p1:p2);
            }
        }
        if(!win)printf("Tie\n");
        print();
        printf("Play again?\n");
        scanf("%s",again);
        again[0]=again[0]%32+64;
    }
    return 0;   
}
