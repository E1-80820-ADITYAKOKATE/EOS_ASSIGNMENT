#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void ctrlc_hadnler(int sig)
{
    int s;
    waitpid(-1,&s,0);
    printf("Signal Recived : Exit Status : %d\n", WEXITSTATUS(s));
}

int main()
{
    signal(SIGINT, ctrlc_hadnler);

    char *ptr, cmd[512], *args[32];
    int i, ret, s;
while(1)
{
    printf("cmd> ");
    gets(cmd);

    ptr = strtok(cmd, " ");

    args[i++] = ptr;

    do
    {
        ptr = strtok(NULL, " ");
        args[i++] = ptr;
    } while (ptr != NULL);

    if ((strcmp (args[0], "cd")) == 0)
    {
        chdir(args[1]);
    }
    else if ((strcmp (args[0], "exit")) == 0)
    {
        _exit(1);
    }
    else{
            ret = fork();
            if(ret == 0)
        {
            
            execvp(args[0], args);
            _exit(0);
        }   
        else
        {
        waitpid(-1, &s, 0);
        }
    }

    // for(int i=0; args[i]!=NULL; i++)
    //     printf("%s", args[i]);
}   
    return 0;
}