#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void SIGINT_handler(int sig)
{
    int s;
    waitpid(-1,&s,0);
    printf("The signal recived %d\n",WEXITSTATUS(s));
}


int main()
{
    int ret,pid,sgn;

    printf("Enter signal Number : ");
    scanf("%d",&sgn);
    printf("Enter Process Id : ");
    scanf("%d",&pid);

    signal(sgn,SIGINT_handler);
    kill(pid,sgn);
    return 0;
}
