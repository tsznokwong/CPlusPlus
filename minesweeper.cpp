#include<cstdio>
#include<cstdlib>
#include<ctime>
#ifdef  __APPLE__
    #include<termios.h>
    #include<unistd.h>
    #include<sys/stat.h>
#elif _WIN32
    #include<Windows.h>
    #include<conio.h>
#endif
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
int MAX=99654;
using namespace std;
short dx[8]={-1,0,1,-1,1,-1,0,1};
short dy[8]={-1,-1,-1,0,0,1,1,1};
#ifdef _WIN32
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
#endif
void print(char *board,bool *show,bool *flag,int width,int height,bool cheat,bool arrow, int x, int y){
    printf("   ");
    for(int j=0;j<width;++j)
        printf("%d",(j+1)%10);
    printf("\n");
    for(int i=0;i<height;++i){
        printf("%2d|",i+1);
        for(int j=0;j<width;++j){
#ifdef _WIN32
            if(arrow&&i==y&&j==x)SetConsoleTextAttribute(color,240);
#endif
            if(show[i*width+j]||cheat)
                printf("%c",board[i*width+j]);
            else if(flag[i*width+j])
                printf("F");
            else printf("-");
#ifdef _WIN32
            SetConsoleTextAttribute(color,15);
#endif
        }
        printf("\n");
    }
}
void initialize(int *width,int *height,int *bomb){
    do{
        printf("Enter board size(10 to 40):\nEg. 25 10\n");
        scanf("%d%d",width,height);
        if(*width<10||*width>40)*width=0;
        if(*height<10||*height>40)*height=0;
    }while(!*width||!*height);
    int max=*width * *height/4,min=*width * *height/10;
    do{
        printf("Enter number of bombs(%d to %d):\nEg. %d\n",min,max,(max+min)/2);
        scanf("%d",bomb);
        if(*bomb<min||*bomb>max)*bomb=0;
    }while(!*bomb);
}
void add(char *board,int width,int height,int i,int j){
    bool t[8]={true,true,true,true,true,true,true,true};
    if(i==0)
        t[0]=t[1]=t[2]=false;
    if(i==height-1)
        t[5]=t[6]=t[7]=false;
    if(j==0)
        t[0]=t[3]=t[5]=false;
    if(j==width-1)
        t[2]=t[4]=t[7]=false;
    for(int k=0;k<8;++k){
        int tmp=i*width+dy[k]*width+j+dx[k];
        if(t[k]&&board[tmp]!='*'){
            if(board[tmp]==-80)
                board[tmp]='1';
            else ++board[tmp];
        }
    }
}
void generate(char *board,int width,int height,int bomb,bool *show,bool *flag){
    for(int i=0;i<height;++i)
        for(int j=0;j<width;++j){
            int r=rand()%(width*height-i*width-j);
            if(r<bomb){
                board[i*width+j]='*';
                --bomb;
            }
            else board[i*width+j]=176;
            flag[i*width+j]=show[i*width+j]=false;
        }
    for(int i=0;i<height;++i)
        for(int j=0;j<width;++j){
            if(board[i*width+j]=='*')
                add(board,width,height,i,j);
        }
}
void expand(char *board,int x,int y,int width,int height,int *cnt, bool *show,bool *flag,int *cntf){
    if(flag[y*width+x]){
        --*cntf;
        flag[y*width+x]=false;
    }
    if(!show[y*width+x])++*cnt;
    show[y*width+x]=true;
    if(board[y*width+x]==-80){
        bool t[8]={true,true,true,true,true,true,true,true};
        if(y==0)
            t[0]=t[1]=t[2]=false;
        if(y==height-1)
            t[5]=t[6]=t[7]=false;
        if(x==0)
            t[0]=t[3]=t[5]=false;
        if(x==width-1)
            t[2]=t[4]=t[7]=false;
        for(int k=0;k<8;++k)
            if(t[k]&&!show[(y+dy[k])*width+x+dx[k]])
                expand(board,x+dx[k],y+dy[k],width,height,cnt,show,flag,cntf);
    }
}
bool win(char *board,bool *flag,int width,int height){
    for(int i=0;i<height;++i)
        for(int j=0;j<width;++j){
            if(board[i*width+j]=='*'&&!flag[i*width+j])
                return false;
            if(board[i*width+j]!='*'&&flag[i*width+j])
                return false;
        }
    return true;
}
int main(){
    FILE *savefile;
    char replay='y',load='n';
    srand(time(NULL));
    int width=10,height=10,bomb=10;
    bool save=false;
#ifdef _WIN32
    DWORD fileAtt = GetFileAttributesA("minesweeperSaveDoc.txt");
    save = (fileAtt&FILE_ATTRIBUTE_DIRECTORY)== 0;
#else
    struct stat st;
    save = stat("minesweeperSaveDoc.txt",&st) == 0;
#endif
    if(save){
        printf("save exist. Load(y/n)? ");
        scanf("%c",&load);getchar();
        if(load=='y')savefile=fopen("minesweeperSaveDoc.txt","r");
    }
    while(replay=='y'){
        replay='n';
        if(load=='y')
            fscanf(savefile,"%d %d %d",&width,&height,&bomb);
        else
            initialize(&width,&height,&bomb);
        char board[height][width];
        bool show[height][width],flag[height][width];

        if(load=='y'){
            char tmp;
            for(int i=0;i<height;++i){
                fscanf(savefile,"%c",&tmp);
                for(int j=0;j<width;++j)
                    fscanf(savefile,"%c",&board[i][j]);
            }
            for(int i=0;i<height;++i){
                fscanf(savefile,"%c",&tmp);
                for(int j=0;j<width;++j){
                    fscanf(savefile,"%c",&tmp);
                    show[i][j]=(tmp=='1')?1:0;
                }
            }
            for(int i=0;i<height;++i){
                fscanf(savefile,"%c",&tmp);
                for(int j=0;j<width;++j){
                    fscanf(savefile,"%c",&tmp);
                    flag[i][j]=(tmp=='1')?1:0;
                }
            }
        }
        else generate(&board[0][0],width,height,bomb,&show[0][0],&flag[0][0]);
        int cnt=0,cntf=0;
        if(load=='y'){
            fscanf(savefile,"%d %d",&cnt,&cntf);
            fclose(savefile);
        }
        int x=width/2,y=height/2;
        while(cnt+cntf<width*height&&!win(&board[0][0],&flag[0][0],width,height)){

            char cmd;
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
#ifdef __APPLE__
            x=width/2;y=height/2;
            print(&board[0][0],&show[0][0],&flag[0][0],width,height,0,0,0,0);
            printf("Block: %d Flag: %d Bomb: %d\n",cnt,cntf,bomb);
            printf("Enter Instruction:\nEg. f 5 3\t-flag\n    c 9 2\t-choose\n    s\t\t-save\n");
            if(load!='y')
                getchar();
            else load='n';

            scanf("%c",&cmd);getchar();
            if(cmd=='f'||cmd=='c'){
                do{
                    if(!y||!x)printf("Error!\n");
                    scanf("%d %d",&y,&x);
                    if(y<1||y>height)y=0;
                    if(x<1||x>width)x=0;
                }while(!y||!x);
                --x;--y;
            }
#else
            char c;
            print(&board[0][0],&show[0][0],&flag[0][0],width,height,0,1,x,y);
            printf("Block: %d Flag: %d Bomb: %d\n",cnt,cntf,bomb);
            printf("Using Arrow Key to move cursor.\nPress f to flag, c to choose, s to save.\n");
            while(true){
                if(kbhit()!=0){
                    c=getch();
                    if(c=='f'||c=='c'||c=='s'||c=='e'){
                        cmd=c;
                        break;
                    }
                    else{
                        switch(c){
                            case UP:
                                if(y-1>=0)--y;
			                    break;
                            case LEFT:
			                    if(x-1>=0)--x;
			                    break;
                            case RIGHT:
	                            if(x+1<width)++x;
			                    break;
                            case DOWN:
			                    if(y+1<height)++y;
                         }
                         system("cls");
                         print(&board[0][0],&show[0][0],&flag[0][0],width,height,0,1,x,y);
                         printf("Block: %d Flag: %d Bomb: %d\n",cnt,cntf,bomb);
                         printf("Using Arrow Key to move cursor.\nPress f to flag, c to choose, s to save.\n");
                    }
                }
            }

#endif

            switch(cmd){
                case 'f':
                    if(show[y][x])break;
                    if(flag[y][x])--cntf;
                    else ++cntf;
                    flag[y][x]=!flag[y][x];
                    break;
                case 'c':
                    if(flag[y][x]){
                        --cntf;
                        flag[y][x]=false;
                    }
                    if(board[y][x]=='*'){
                        cnt=MAX;
                        show[y][x]=true;
                    }
                    else
                        expand(&board[0][0],x,y,width,height,&cnt,&show[0][0],&flag[0][0],&cntf);
                    break;
                case 'e':
                    cnt=MAX;
                    break;
                case 's':
                    savefile=fopen("minesweeperSaveDoc.txt","w");
                    fprintf(savefile,"%d %d %d\n",width,height,bomb);
                    for(int i=0;i<height;++i){
                        for(int j=0;j<width;++j)
                            fprintf(savefile,"%c",board[i][j]);
                        fprintf(savefile,"\n");
                    }
                    for(int i=0;i<height;++i){
                        for(int j=0;j<width;++j)
                            fprintf(savefile,"%d",show[i][j]);
                        fprintf(savefile,"\n");
                    }
                    for(int i=0;i<height;++i){
                        for(int j=0;j<width;++j)
                            fprintf(savefile,"%d",flag[i][j]);
                        fprintf(savefile,"\n");
                    }
                    fprintf(savefile,"%d %d\n",cnt,cntf);
                    fclose(savefile);
                    printf("save successfully\n");
                    cnt=MAX+1;
                    break;
                default:
                    printf("Error!\n");
            }
        }
        if(cnt==MAX+1)break;
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        print(&board[0][0],&show[0][0],&flag[0][0],width,height,0,0,0,0);
        if(cnt==MAX)printf("You Lose!\n");
        else printf("You Win!\n");
        printf("Replay(y/n)? ");
        if(load=='n')getchar();
#ifdef __APPLE__

#endif
        load='n';
        scanf("%c",&replay);
    }
    return 0;
}
