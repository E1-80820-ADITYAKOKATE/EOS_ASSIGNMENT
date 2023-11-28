/*
    From one parent create 5 child processes. Each child should run for 5 seconds and print count along with its pid. Parent should wait for all child processes
to complete and clean all of them. Hint: use loop to fork() multiple child processes.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int arr[5];
int k=0;
void print_pid();

int main()
{
    int count,s,pid,ret,i =0, j=0;

    for(; i<5; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            sleep(5);
            print_pid();
            _exit(0);
        }
    }

    for(; j<5; j++)
    {
        waitpid(arr[j], &s, 0);
        WEXITSTATUS(s);
        sleep(5);
    }
    return 0;
}

void print_pid()
{
    printf("process Id : %d\n", getpid());
    arr[k++] = getpid();
}