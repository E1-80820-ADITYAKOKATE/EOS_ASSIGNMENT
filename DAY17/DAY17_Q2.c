#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct arr
{
    int *arr;
    int size;
}arr_t;

void * sort_arr(void * param)
{
    int temp;
    arr_t * val = (arr_t *) param;
    int * arr = (int*)val->arr; 

    for(int it=0; it<val->size-1; it++)
    {
        for(int i=0; i<val->size-1-it; i++)
        {
            for(int j=1; j<val->size-it; j++)
            {
                if(arr[i] > arr[j])
                {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    int ret, size;
    pthread_t th;
    printf("Enter SIZE of array : ");
    scanf("%d", &size);
    arr_t arr;
    arr.size = size;
    int * ptr = (int *) malloc(sizeof(int) * size);
    arr.arr = ptr;
    printf("Enter Array Elements : ");
    for(int i=0; i<size; i++)
    {
        printf("Arr[%d] : ", i);
        scanf("%d", &arr.arr[i]);
    }

    ret = pthread_create(&th, NULL, sort_arr, &arr);

    pthread_join(th, NULL);
    printf("Array After Sort In Main : ");
    for(int i =0; i<arr.size; i++)
    {
        printf("%-4d", arr.arr[i]);
    }

    return 0;
}