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

    num_t n;
    sum_t s;

    int fd = open("/tmp/desd_fifo", O_RDONLY);

    if(fd < 0)
    {
        perror("File not opened in p2.. \n");
    }

    read(fd, &n, sizeof(n));
    close(fd);

    printf("The number recived are %d and %d\n", n.num1, n.num2);

    s.sum = n.num1 + n.num2;

    fd = open("/tmp/desd_fifo", O_WRONLY);

    write(fd, &s, sizeof(s));
    close(fd);

    return 0;
}