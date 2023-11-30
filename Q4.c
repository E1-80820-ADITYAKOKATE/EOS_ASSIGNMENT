/*parent
|- child1 (gcc -c circle.c)
|- child2 (gcc -c square.c)
|- child3 (gcc -c rectangle.c)
|- child4 (gcc -c main.c)
wait for all child and check exit status. If all exit status 0 (success), then link
|- child5 (gcc -o program.out circle.o square.o rectangle.o main.o)
wait for child and check exit status. If all exit status 0 (success), then run it.
|- child6 (./program.out)
wait for child and check exit status. Then print child exit status.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>

int main() {
    int i=0, err,pid1, pid2, pid3,pid4,pid5,pid6, s1, s2, s3,s4,s5,s6;
     char *ptr,*args[30];
    pid1 = fork();
    if(pid1 == 0) { // first child
   
   char cmd[100]="gcc -c circle.c";
    

    ptr=strtok(cmd," ");
    args[i++]=ptr;
    do{
            ptr=strtok(NULL," ");
            args[i++]=ptr;
        }while(ptr != NULL);
    
         err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                }
            sleep(1);            
        _exit(0);
    }

    pid2 = fork();
    if(pid2 == 0) { // second child
        char cmd[100]="gcc -c square.c";
    

    ptr=strtok(cmd," ");
    args[i++]=ptr;
    do{
            ptr=strtok(NULL," ");
            args[i++]=ptr;
        }while(ptr != NULL);
    
         err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                  }  
                  sleep(1);
                  _exit(0);
    }

    pid3 = fork();
    if(pid3 == 0) { // third child
   char cmd[100]="gcc -c rect.c";
    

    ptr=strtok(cmd," ");
    args[i++]=ptr;
    do{
            ptr=strtok(NULL," ");
            args[i++]=ptr;
        }while(ptr != NULL);
    
         err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                  }  
                  sleep(1);
        _exit(0);
    }
    pid4 = fork();
    if(pid4 == 0) { // third child
       char  cmd[100]="gcc -c main.c";
    

    ptr=strtok(cmd," ");
    args[i++]=ptr;
    do{
            ptr=strtok(NULL," ");
            args[i++]=ptr;
        }while(ptr != NULL);
    
         err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                  }  
                  sleep(1);
        _exit(0);
    }
    pid5 = fork();
    if(pid5 == 0) { // third child
        sleep(1);
    if(WEXITSTATUS(s1)==0 && WEXITSTATUS(s2)==0 && WEXITSTATUS(s3)==0 && WEXITSTATUS(s4)==0)
    {
      char  cmd[100]="gcc -o program.out circle.o square.o rect.o main.o";
    

    ptr=strtok(cmd," ");
    args[i++]=ptr;
    do{
            ptr=strtok(NULL," ");
            args[i++]=ptr;
        }while(ptr != NULL);
    
         err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                }
    }      
    sleep(1);
        _exit(0);

    }
    pid6 = fork();
    if(pid6 == 0) {
            sleep(1); 
        if(WEXITSTATUS(s5)==0)
        {
      char  cmd[100]="./program.out";
    

    ptr=strtok(cmd," ");
    args[i++]=ptr;
    do{
            ptr=strtok(NULL," ");
            args[i++]=ptr;
        }while(ptr != NULL);
    
         err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                  }
        } 
        sleep(1);         
        _exit(0);
    }


    waitpid(pid1, &s1, 0);
    waitpid(pid2, &s2, 0);
    waitpid(pid3, &s3, 0);
    waitpid(pid4, &s4, 0);
    waitpid(pid5, &s5, 0);
    waitpid(pid6, &s6, 0);
    printf("parent: child's 1 exit status: %d\n", WEXITSTATUS(s1));
    printf("parent: child's 2 exit status: %d\n", WEXITSTATUS(s2));
    printf("parent: child's 3 exit status: %d\n", WEXITSTATUS(s3));
    printf("parent: child's 4 exit status: %d\n", WEXITSTATUS(s4));
    printf("parent: child's 5 exit status: %d\n", WEXITSTATUS(s5));
    printf("parent: child's exit status: %d\n", WEXITSTATUS(s6));

    return 0;
}


