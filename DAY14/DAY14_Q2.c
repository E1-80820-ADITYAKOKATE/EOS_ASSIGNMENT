/*
    The child process send two numbers to the parent process via pipe. The parent process calculate the sum and return via another pipe. The child process
print the result and exit. The parent process wait for completion of the child and then exit.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

typedef struct op
{
    int num1;
    int num2;
}op_t;

typedef struct res
{
    int sum;
}res_t;

int main()
{
    int ret, s, fd[2], fd1[2], ret1;
    
    op_t op;
    res_t res;

    ret = pipe(fd);
    ret1 = pipe(fd1);
    if(ret < 0)
    {
        perror("pipe failed()...\n");
        _exit(0);
    }
    if(ret1 < 0)
    {
        perror("pipe for second pipe failed ...\n");
        _exit(0);
    }

    ret = fork();
    if(ret == 0)
    {
        printf("Enter 2 numbers : \n");
        scanf("%d %d", &op.num1,&op.num2);
        //child process
        close(fd[0]);
        write(fd[1],&op,sizeof(op));
        close(fd[1]);
        
        printf("Child waiting for result : \n");
        close(fd1[1]);
        read(fd1[0], &res, sizeof(res));
        close(fd1[0]);

        printf("The sum of 2 numbers given is %d\n", res.sum);
        _exit(0);
    }
    else
    {
        // parent process
        printf("Waiting for 2 numbers : \n");
        close(fd[1]);
        read(fd[0],&op, sizeof(op));
        close(fd[0]);
        printf("The recived numbers are %d %d\n", op.num1, op.num2);

        res.sum = op.num1 + op.num2;

        close(fd1[0]);
        write(fd1[1],&res, sizeof(res));
        close(fd1[1]);

        waitpid(-1, &s, 0);
    }
    return 0;
}