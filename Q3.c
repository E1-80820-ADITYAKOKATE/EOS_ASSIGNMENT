/*
    Find max number of child processes that can be created on Linux using C program? Hint: use fork() in inﬁnite loop (wisely).
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret, count = 0,n;

    while(1) {
        ret = fork();
        if(ret == -1)
            break;
        else if(ret == 0) {
            // child process
            sleep(5);
            _exit(0);
        }
        else {
            count++;
        }
    }
    while (n <= count)
    {
        wait(NULL);
        n++;
    }
    printf("max child count: %d\n", count);
    return 0;
}