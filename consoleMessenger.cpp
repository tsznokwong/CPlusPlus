#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<fstream>
#ifdef  __APPLE__
    #include<termios.h>
    #include<unistd.h>
    #include<sys/stat.h>
#elif _WIN32
    #define _WIN32_WINNT 0x0500
    #include<Windows.h>
    #include<conio.h>
#endif
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 27
#define ENTER 13
#define HOME 71
#define END 79
#define F5 63
#define BACKSPACE 8
char version[50]={"0.1.6 alpha"};
using namespace std;
//Profile Data
char name[255],targetName[255],msg[255]={""},drive[8];
int id,targetId,cnt=0;
bool help=true;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

/*Z:\\CM\\*/
struct message{
    char content[255];
    time_t time;
};
message msgList[10];
int msgCnt=0,msgStart=0;
bool first=true;
void clear(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void delay(int interval){
    time_t start;
    start=time(NULL);
    while(time(NULL)<(start+interval));
}
void welcome(){
    for(int i=0;i<9;++i){
        for(int j=0;j<40;++j){
            if(i!=4)printf(".");
            else{
                printf("......Welcome to Console Messenger......");
                j+=40;
            }
        }
        printf("\n");
    }
    printf("Version: %s\n",version);
    delay(3);
    printf("Put the application on your Desktop\n");
    delay(1);
    printf("Do not create or remove any file\n");
    delay(1);
    printf("Use arrow keys to make choice\n");
    delay(1);
    printf("By Wong Tsz Nok Joshua\n");
    delay(2);
    clear();
}
bool fileExist(char* filePath){
    bool file=false;
#ifdef _WIN32
    DWORD fileAtt = GetFileAttributesA(filePath);
    file = (fileAtt&FILE_ATTRIBUTE_DIRECTORY)== 0;
#else
    struct stat st;
    file = stat(filePath,&st) == 0;
#endif
    if(file)return true;
    return false;
}
void testDrive(){
    DWORD drives = GetLogicalDrives();
    char filepath[4]={"A:\\"},driveAvailable[27][6];
    int y=0,j=0;
    for(int i=0;i<26;++i){
        if(drives & (1 << i))
            strcpy(driveAvailable[j++],filepath);
        ++filepath[0];
    }
    strcpy(driveAvailable[j++],"Local");
    printf("Press ENTER to select\nAvailable Drive(s):\n");
    for(int i=0;i<j;++i){
        if(y==i)SetConsoleTextAttribute(color,240);
        printf("%s\n",driveAvailable[i]);
        SetConsoleTextAttribute(color,15);
    }
    while(true){
        if(kbhit!=0){
            char c=getch();
            if(c==ENTER){
                if(strcmp(driveAvailable[y],"Local")!=0)
                    strcpy(drive,strcat(driveAvailable[y],"CM\\"));
                else
                    strcpy(drive,"CM\\");
                break;
            }
            switch(c){
                case UP:
                    if(y>0)--y;
                    break;
                case DOWN:
                    if(y<j-1)++y;
                    break;
            }
            clear();
            printf("Press ENTER to select\nAvailable Drive(s):\n");
            for(int i=0;i<j;++i){
                if(y==i)SetConsoleTextAttribute(color,240);
                printf("%s\n",driveAvailable[i]);
                SetConsoleTextAttribute(color,15);
            }
        }
    }
    clear();
}

void importProfile(){
    FILE *profile;
    FILE *content;
    FILE *accessContent;
    char nameContent[100][255],filepath[255];
    int idContent[100],i=0;

    if(fileExist("CMProfile.txt")){
        profile=fopen("CMProfile.txt","r");
        fscanf(profile,"%d %[^\n]s",&id,name);
    }
    else{
        strcpy(filepath,drive);
        strcat(filepath,"CMContentAccessing.txt");
        while(fileExist(filepath)){//destination
            /*printf("CMContent.txt is accessing by others\n");
            delay(1);
            clear();*/
        }
        accessContent=fopen(filepath,"w");//destination
        strcpy(filepath,drive);
        strcat(filepath,"CMContent.txt");
        if(fileExist(filepath)){//destination
            content=fopen(filepath,"r");//destination
            while(fscanf(content,"%d %[^\n]s",&idContent[i],nameContent[i])!=EOF)++i;
            fclose(content);
        }
        fclose(accessContent);
        strcpy(filepath,drive);
        strcat(filepath,"CMContentAccessing.txt");
        remove(filepath);
        profile=fopen("CMProfile.txt","w");
        bool loop;
        do{
            loop=false;
            printf("Enter your name:\n");
            scanf("%[^\n]s",name);getchar();
            int l=strlen(name);
            for(int j=l-1;j>=0;--j)
                if(name[j]==' '||name[j]=='\t')
                    name[j]='\0';
                else break;
            if(strcmp(name,"")==0)printf("Invalid name!\n");
            //system("pause");
            for(int j=0;j<i;++j)
                if(strcmp(name,nameContent[j])==0){
                    loop=true;
                    clear();
                    printf("Name duplicated!\n");
                    break;
                }
        }while(loop);
        do{
            loop=false;
            id=rand();
            for(int j=0;j<i;++j)
                if(id==idContent[j]){
                    loop=true;
                    break;
                }
        }while(loop);
        fprintf(profile,"%d %s\n",id,name);
        strcpy(filepath,drive);
        strcat(filepath,"CMContentAccessing.txt");
        while(fileExist(filepath)){//destination
        /*printf("CMContent.txt is accessing by others\n");
        delay(1);
        clear();*/
        }
        accessContent=fopen(filepath,"w");//destination
        strcpy(filepath,drive);
        strcat(filepath,"CMContent.txt");
        content=fopen(filepath,"a");//destination
        fprintf(content,"%d %s\n",id,name);
        fclose(content);
        fclose(accessContent);
        strcpy(filepath,drive);
        strcat(filepath,"CMContentAccessing.txt");
        remove(filepath);//destination
    }
    fclose(profile);
}

void updateOnline(){
    FILE *online;
    FILE *accessOnline;
    char filepath[255],tmpName[255];
    int onlineId[255],cntId=0;
    strcpy(filepath,drive);
    strcat(filepath,"CMOnlineAccessing.txt");
    while(fileExist(filepath)){//destination
        /*printf("CMOnline.txt is accessing by others\n");
        delay(1);
        clear();*/
    }
    accessOnline=fopen(filepath,"w");//destination
    strcpy(filepath,drive);
    strcat(filepath,"CMOnline.txt");
    if(fileExist(filepath)){
        online=fopen(filepath,"r");
        while(fscanf(online,"%d %[^\n]s",&onlineId[cntId],tmpName)!=EOF){
            if(onlineId[cntId]==id){
                fclose(online);
                fclose(accessOnline);
                strcpy(filepath,drive);
                strcat(filepath,"CMOnlineAccessing.txt");
                remove(filepath);
                return;
            }
            ++cntId;
        }
        fclose(online);
    }
    strcpy(filepath,drive);
    strcat(filepath,"CMOnline.txt");
    online=fopen(filepath,"a");//destination
    fprintf(online,"%d %s\n",id,name);
    fclose(online);
    fclose(accessOnline);
    strcpy(filepath,drive);
    strcat(filepath,"CMOnlineAccessing.txt");
    remove(filepath);//destination
}
void offline(){
    FILE *online;
    FILE *accessOnline;
    char filepath[255];
    strcpy(filepath,drive);
    strcat(filepath,"CMOnlineAccessing.txt");
    while(fileExist(filepath)){//destination
        /*printf("CMOnline.txt is accessing by others\n");
        delay(1);
        clear();*/
    }
    accessOnline=fopen(filepath,"w");//destination
    strcpy(filepath,drive);
    strcat(filepath,"CMOnline.txt");
    online=fopen(filepath,"r");//destination
    char nameOnline[100][255];
    int idOnline[100],i=0;
    while(fscanf(online,"%d %[^\n]s",&idOnline[i],nameOnline[i])!=EOF)++i;
    fclose(online);
    online=fopen(filepath,"w");//destination
    for(int j=0;j<i;++j)
        if(id!=idOnline[j])fprintf(online,"%d %s\n",idOnline[j],nameOnline[j]);
    fclose(online);
    fclose(accessOnline);
    strcpy(filepath,drive);
    strcat(filepath,"CMOnlineAccessing.txt");
    remove(filepath);//destination
}
void printOnline(int *idOnline,char *nameOnline,int totalOnline,int y){
     clear();
     printf("Press Enter to select.\n");
     printf("Number of People Online: %d\n",totalOnline);
     printf("  ID         Name\n");
     for(int i=0;i<totalOnline;++i){
         printf("%c|%10d %s\n",y==i?'*':' ',idOnline[i],nameOnline[i]);
     }
}
void openOnline(){
    FILE *online;
    FILE *accessOnline;
    char filepath[255];
    strcpy(filepath,drive);
    strcat(filepath,"CMOnlineAccessing.txt");
    while(fileExist(filepath)){//destination
        /*printf("CMOnline.txt is accessing by others\n");
        delay(1);
        clear();*/
    }
    accessOnline=fopen(filepath,"w");//destination
    strcpy(filepath,drive);
    strcat(filepath,"CMOnline.txt");
    online=fopen(filepath,"r");//destination
    char nameOnline[100][255];
    int idOnline[100],i=0;
    while(fscanf(online,"%d %[^\n]s",&idOnline[i],nameOnline[i])!=EOF){
        if(idOnline[i]==id)--i;
        ++i;
    }
    fclose(online);
    fclose(accessOnline);
    strcpy(filepath,drive);
    strcat(filepath,"CMOnlineAccessing.txt");
    remove(filepath);//destination
    int y=0;
    /*for(int j=0;j<i;++j){
        printf("%d %s\n",idOnline[j],nameOnline[j]);
    }*/
    clear();
     printf("Press Enter to select.\n");
     printf("Number of People Online: %d\n",i);
     printf("  ID         Name\n");
     for(int j=0;j<i;++j){
        if(y==j)SetConsoleTextAttribute(color,240);
        printf("%10d %s\n",idOnline[j],nameOnline[j]);
        SetConsoleTextAttribute(color,15);
     }
    time_t start=time(NULL);
    while(true){
        if(kbhit()!=0||time(NULL)>start+2){
            char c;
            if(time(NULL)>start+2){
                c='r';
                start=time(NULL);
            }
            else c=getch();
            start=time(NULL);
            if(c==ENTER){
                targetId=idOnline[y];
                strcpy(targetName,nameOnline[y]);
                break;
            }
            switch(c){
                case UP:
                    if(y>0)--y;
                    break;
                case DOWN:
                    if(y<i-1)++y;
                    break;
                case 'r':case F5:
                    delete[] nameOnline;
                    delete[] idOnline;
                    openOnline();
                    return;
                    break;
            }
            clear();
             printf("Press Enter to select.\n");
             printf("Number of People Online: %d\n",i);
             printf("  ID         Name\n");
             for(int j=0;j<i;++j){
                if(y==j)SetConsoleTextAttribute(color,240);
                printf("%10d %s\n",idOnline[j],nameOnline[j]);
                SetConsoleTextAttribute(color,15);
             }
        }
    }
    clear();
}
void printChatroom(){
    clear();
    printf("I am %s\n",name);
    printf("Target: %s ID: %d\n",targetName,targetId);
    if(help)printf("Press HOME/h open online contact\nPress END/q to offline\nPress F5/r to reload\nPress ESC to change mode\n");
    printf("Press I to %s help.\n",help?"disable":"enable");
    /*for(int i=0;i<10;++i)
        printf("%s\n",msgList[i].content);
    printf("--- %d %d\n",msgStart,msgCnt);*/
    for(int i=msgStart;(i<10&&!first)||(i<msgCnt&&first);++i)
        printf("%s\n",msgList[i].content);
    for(int i=0;i<msgStart;++i)
        printf("%s\n",msgList[i].content);
}
void sendMSG(){
    FILE *target, *msgContent, *accessTarget;
    char filepath[255],targetFilepath[25],num[3];
    //printf("You are sending: %s\n",msg);
    itoa(targetId,targetFilepath,10);
    strcpy(filepath,drive);
    strcat(filepath,"CM");
    strcat(filepath,targetFilepath);
    strcat(filepath,"mainAccessing.txt");
    while(fileExist(filepath)){//destination
        ;
    }
    accessTarget=fopen(filepath,"w");
    strcpy(filepath,drive);
    strcat(filepath,"CM");
    strcat(filepath,targetFilepath);
    strcat(filepath,"main.txt");
    if(fileExist(filepath)){//destination
        target=fopen(filepath,"r");
        fscanf(target,"%s",num);
        fclose(target);
        char tmp[3];
        target=fopen(filepath,"w");
        strcpy(tmp,num);
        tmp[1]++;
        if(tmp[1]>'9'){
            tmp[1]='0';
            tmp[0]++;
            if(tmp[0]>'9')tmp[0]='0';
        }
        fprintf(target,"%s",tmp);
        fclose(target);
    }
    else{
        target=fopen(filepath,"w");
        fprintf(target,"01");
        strcpy(num,"00");
        fclose(target);
    }
    fclose(accessTarget);
    strcpy(filepath,drive);
    strcat(filepath,"CM");
    strcat(filepath,targetFilepath);
    strcat(filepath,"mainAccessing.txt");
    remove(filepath);
    strcpy(filepath,drive);
    strcat(filepath,"CM");
    strcat(filepath,targetFilepath);
    strcat(filepath,num);
    strcat(filepath,".txt");
    msgContent=fopen(filepath,"w");//destination
    char content[255];
    strcpy(content,"Me: ");
    strcat(content,msg);
    fprintf(msgContent,"%s: %s\n%ld",name,msg,time(NULL));
    strcpy(msgList[msgCnt].content,content);
    msgList[msgCnt].time=time(NULL);
    msgCnt=(msgCnt+1)%10;
    if(first){
        if(msgCnt==0)
            first=false;
    }
    else
        msgStart=(msgStart+1)%10;
    fclose(msgContent);
    cnt=0;
    strcpy(msg,"");
}
void checkMSG(){
    FILE *msgContent;
    char filepath[255],num[3]={"00"},myFilepath[25];
    itoa(id,myFilepath,10);
    for(int i=0;i<100;++i){
        strcpy(filepath,drive);
        strcat(filepath,"CM");
        strcat(filepath,myFilepath);
        strcat(filepath,num);
        strcat(filepath,".txt");
        if(fileExist(filepath)){
            msgContent=fopen(filepath,"r");
            fscanf(msgContent,"%[^\n]s%ld",msgList[msgCnt].content,&msgList[msgCnt].time);
            msgCnt=(msgCnt+1)%10;
            if(first){
                if(msgCnt==0)
                    first=false;
            }
            else
                msgStart=(msgStart+1)%10;
            fclose(msgContent);
            remove(filepath);
        }
        num[1]++;
        if(num[1]>'9'){
            num[1]='0';
            num[0]++;
            if(num[0]>'9')num[0]='0';
        }
    }
}
int main(){
    srand(time(NULL));
    SetConsoleTextAttribute(color,15);
    HWND window=GetConsoleWindow();
    RECT r;
    GetWindowRect(window,&r);
    MoveWindow(window,r.left,r.top,370,500,true);
    clear();
    welcome();
    testDrive();
    importProfile();
    updateOnline();
    char cmd;
    bool cmdmode=true,end=false;
    clear();
    printf("Start Application\n");
    openOnline();
    while(!end){
       printChatroom();
       printf("Mode: %s\n",cmdmode?"cmd":"typing");
       printf("%s\n",msg);

#ifdef __APPLE__
       scanf("%c",&cmd);
#else
       time_t start=time(NULL);
       while(true){
           if(time(NULL)>start+2){
               cmd='r';
               break;
           }
           if(kbhit()!=0){
               char c=getch();
               if(c==ESC){
                   cmdmode=!cmdmode;
                   printChatroom();
                   printf("Mode: %s\n",cmdmode?"cmd":"typing");
                   printf("%s\n",msg);
                   continue;
               }
               if(c==HOME||c==END||c==F5||(cmdmode&&(c=='r'||c=='q'||c=='h'||c=='i'))){
                   cmd=c;
                   break;
               }
               if(!cmdmode){
                   if(c==ENTER){
                        clear();
                        printChatroom();
                        printf("Mode: %s\n",cmdmode?"cmd":"typing");
                        printf("%s\n",msg);
                        int l=strlen(msg);
                        for(int j=l-1;j>=0;--j)
                            if(msg[j]==' ')
                                msg[j]='\0';
                            else break;
                        if(strcmp(msg,"")!=0){
                            sendMSG();
                            break;
                        }
                   }
                   else{
                        if(c==BACKSPACE){
                            if(cnt>0)--cnt;
                        }
                        else
                            msg[cnt++]=c;
                        msg[cnt]='\0';
                        clear();
                        printChatroom();
                        printf("Mode: %s\n",cmdmode?"cmd":"typing");
                        printf("%s",msg);
                   }
               }
           }
       }
#endif
        //if(cmdmode)
       // printf("%ld %ld %c\n",time(NULL),start,cmd);

            switch(cmd){
                case END:case 'q':
                    end=true;
                    break;
                case HOME:case 'h':
                    openOnline();
                    break;
                case 'i':
                    help=!help;
                    break;
                case 'r':case F5:
                    checkMSG();
                    break;
            }
    }
    offline();
    return 0;
}



