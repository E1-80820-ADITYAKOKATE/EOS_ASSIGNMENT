#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * sort_arr(void * param)
{
    int temp;
    int * arr = (int *) param;
    printf("Array in thread : ");
    for(int i=0; i<5; i++)
    {
        printf("%-4d", arr[i]);
    }
    for(int i =0; i<4; i++)
    {
        for(int j=i+1; j<5; j++)
        {
            if(arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                printf("Swapping....!!!\n");
                sleep(1);
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    int arr[5] = {22, 33, 44, 55, 11};
    pthread_t th;
    int ret;

    ret = pthread_create(&th, NULL, sort_arr, arr);
    if(ret < 0)
    {
        perror("Create() failed ... !!!\n");
        _exit(0);
    }
    pthread_join(th, NULL);
    printf("In Main : Array After Sort : ");
    for(int i=0; i<5; i++)
    {
        printf("%-4d", arr[i]);
    }
    printf("\n");

    return 0;
}