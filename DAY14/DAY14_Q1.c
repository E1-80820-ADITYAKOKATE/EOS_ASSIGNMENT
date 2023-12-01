#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
    int ret, s, fd, new_fd, err;
    
    ret = fork();
    if(ret == 0)
    {
        fd = open("int.txt", O_RDONLY);
        dup2(fd, 1);
        close(fd);
        if (fd < 0)
        {
            perror("File opening error ...!!!\n");
            _exit(0);
        }
        err = execlp("wc", "wc", NULL);
        if (err < 0)
        {
            perror("Error while exec() ,...\n");
        }
    }
    else
    {
        waitpid(-1,&s,0);
    }

    printf("Program completed !!!\n");

    return 0;
}
