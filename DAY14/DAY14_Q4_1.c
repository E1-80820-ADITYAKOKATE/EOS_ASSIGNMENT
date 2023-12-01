/*
The client process send two numbers to the server process via one ﬁfo. The server process calculate the sum and return via another ﬁfo. The client
process print the result.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

typedef struct number
{
    int num1;
    int num2;
}num_t;

typedef struct sum
{
    int sum;
}sum_t;

int main()
{
    int fd;

    num_t n;
    sum_t s;

    fd = open("/tmp/desd_fifo", O_WRONLY);

    if(fd < 0)
    {
        perror("The file is not opened ...!!!\n");
    }
    
    printf("Enter 2 numbers : ");
    scanf("%d %d", &n.num1,&n.num2);

    write(fd, &n, sizeof(n));
    close(fd);

    printf("The process 1 is waiting for result \n");

    fd = open("/tmp/desd_fifo", O_RDONLY);

    read(fd, &s, sizeof(s));
    close(fd);

    printf("Process 1: The result is %d\n", s.sum);

    return 0;
}