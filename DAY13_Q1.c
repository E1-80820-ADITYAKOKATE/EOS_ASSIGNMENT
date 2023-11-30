#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define mq_key 0X00001234
#define mq1_key 0X00001235

typedef struct msg
{
    long type;
    int num1;
    int num2;
}msg_t;

typedef struct msg1
{
    long type;
    int sum;
}msg1_t;

int main()
{
    int ret, s, pid, mqid, mqid1;
    
    mqid = msgget(mq_key ,IPC_CREAT|0600);
    mqid1 = msgget(mq1_key, IPC_CREAT|0600);

    if (mqid < 0)
    {
        perror("Msgget() failed !!!\n");
        _exit(0);
    }
    ret = fork();
    if (ret == 0)
    {
        //child process
        msg_t m1;
        m1.type = 11;
        printf("Enter 2 numbers : ");
        scanf("%d %d", &m1.num1,&m1.num2);
        msgsnd(mqid, &m1, sizeof(m1) - sizeof(m1.type), 0);
        
        msg1_t m2;
        printf("Child is waiting for Sum : \n");
        msgrcv(mqid1, &m2, sizeof(m2.sum), 22, 0);
        printf("Child Recived : The sum of 2 numbers is %d\n", m2.sum);

        msgctl(mqid1,IPC_RMID,0);
        _exit(0);

    }
    else
    {
        //parent process
        msg_t m2;
        printf("Parent is waiting for recieving numbers : \n");
        msgrcv(mqid, &m2, sizeof(m2) - sizeof(m2.type), 11, 0 );
        printf("Parent recived : num1 = %d, num2 = %d\n", m2.num1, m2.num2);

        msg1_t m1;
        m1.type = 22;
        m1.sum = m2.num1 + m2.num2;
        msgsnd(mqid1, &m1, sizeof(m1.sum),0);

        msgctl(mqid,IPC_RMID,0);
        waitpid(-1,&s,0);
    }

    return 0;
}
