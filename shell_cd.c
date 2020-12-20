#include <stdio.h>
#include <string.h>
#include <unistd.h>

int shell_cd(int argc,char *argv[],char **r[])
{
    if(argc==2)
    {
        if(strcmp(argv[1],"-")==0)
        {
            chdir((*r)[1]);
        }
        else if(strcmp(argv[1],"~")==0)
        {
            chdir("/home/stu2330/");
        }
        else
        {
            if(chdir(argv[1]))
            {
                printf("No such path!");
                return 1;
            }
        }
    }
    if(argc==1)
    {
        chdir("/home/stu2330/");
    }
    printf("当前工作目录:%s\n",getcwd(NULL,NULL));
    (*r)[1]=(*r)[0];
    (*r)[0]=getcwd(NULL,NULL);
    return 0;
}