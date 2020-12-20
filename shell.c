#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *argv[50];
int argc = 0;
int falg;

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
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        falg = 1;
        execvp(argv[0], argv);
        perror("shell_osh");
        exit(EXIT_FAILURE);
    }
    else{
        wait(NULL);
    }
    return;
}

int main(void)
{
    int falg = 0;
    while(1)
    {
        int len = 0;
        char buff[1024] = {0};
        printf("MyShell>");
        scanf("%[^\n]%*c", buff);
        analysis(buff, strlen(buff));
        argc = 0;
    }
    return 0;
}