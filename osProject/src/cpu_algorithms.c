#include "cpu_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 10000
#define MAX_QUEUE 100
void generateData(Process *process_arr, int PROCESS_NUM)
{
    srand(time(0));

    for (int i = 0; i < PROCESS_NUM; i++)
    {
        process_arr[i].pid = i + 1;
        process_arr[i].arrivalTime = (rand() % 50) + 1;
        process_arr[i].burstTime = (rand() % 10) + 1;
        process_arr[i].rem_time = process_arr[i].burstTime;
        process_arr[i].complete = false;
    }
}

void printData(Process *p_arr,int PROCESS_NUM)
{
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTAT\n");

    for (int i = 0; i < PROCESS_NUM; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p_arr[i].pid,
               p_arr[i].arrivalTime,
               p_arr[i].burstTime,
               p_arr[i].completionTime,
               p_arr[i].waitTime,
               p_arr[i].TAT);
    }
}
