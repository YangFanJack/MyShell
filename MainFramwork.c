#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "head.h"

char *argv[50];
int argc = 0;
int falg;
char **route;
char hist[10][100];
int count=0;

void do_exec(void);

void analysis(char* str, int size)
{
    if(str == NULL)
        return ;
    int i = 0;
    char *ptr = str;
    while(str[size - 1] == ' '){
            str[size - 1] = '\0';
            size--;
    }

    while(i < size - 1){
        if((str[i] == ' ') && (i != 0) && (str[i+1] != ' '))
        {
            str[i] = '\0';
            i++;
            argv[argc++] = ptr;
            ptr = str + i;
        }
        else
            i++;
    }

    argv[argc++] = ptr;
    argv[argc] = NULL;

    do_exec();
}

void do_exec(void)
{
    if(strcmp(argv[0],"ls")==0)
    {
        shell_ls(argc,argv);
    }
    else if(strcmp(argv[0],"echo")==0)
    {
        shell_echo(argc,argv);
    }
    else if(strcmp(argv[0],"cat")==0)
    {
        shell_cat(argc,argv);   
    }
    else if(strcmp(argv[0],"mkdir")==0)
    {
        shell_mkdir(argc,argv);
    }
    else if(strcmp(argv[0],"rm")==0)
    {
        shell_rm(argc,argv);
    }
    else if(strcmp(argv[0],"cd")==0)
    {
        char ***a=&route;
        shell_cd(argc,argv,a);
    }
    else if(strcmp(argv[0],"pwd")==0)
    {
        shell_pwd(argc,argv);
    }
    else if(strcmp(argv[0],"wc")==0)
    {
        shell_wc(argc,argv);
    }
    else if(strcmp(argv[0],"help")==0)
    {
        shell_help(argc,argv);
    }
    else if(strcmp(argv[0],"history")==0)
    {
        for(int i=0;i<count;i++)
        {
            printf("%d: %s\n",i+1,hist[i]);
        }
    }
    else
    {
        printf("No such command!\n");
    }
    
    
}

int main(void)
{
    int falg = 0;
    route = (char**)malloc(sizeof(char*)*2);//为二维数组分配3行
    for (int i = 0; i < 2; ++i){//为每列分配4个大小空间
        route[i] = (char*)malloc(sizeof(char)*100);
    }
    strcpy(route[0],getcwd(NULL,0));
    strcpy(route[1],getcwd(NULL,0));
    while(1)
    {
        int len = 0;
        char buff[1024] = {0};
        printf("MyShell>");
        scanf("%[^\n]%*c", buff);
        if(count<10)
        {
            strcpy(hist[count],buff);
            count++;
        }
        else
        {
            for(int i=0;i<10;i++)
            {
                strcpy(hist[i],hist[i+1]);
            }    
            strcpy(hist[9],buff);
        }
        analysis(buff, strlen(buff));
        argc = 0;
    }
    return 0;
}