/*
    Find the size of pipe buﬀer in your system.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
    int count =0; 
    int ret, s;
    int fd[2];

    fd[1] = open("int.txt", O_WRONLY);
    char str = 'a';

    ret = pipe(fd);
    if (ret < 0)
    {
        perror("pipe failed()... \n");
    }
    while(1)
    {
        //
        write(fd[1] ,&str, sizeof(str));
        count = count + 1;
        printf("count = %d", count);
    }
    return 0;
}