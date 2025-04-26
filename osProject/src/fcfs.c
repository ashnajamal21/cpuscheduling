#include "cpu_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int compare_by_arrival(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->arrivalTime != p2->arrivalTime)
        return p1->arrivalTime - p2->arrivalTime;
    else
        return p1->pid - p2->pid;
}

void fcfs(Process *p, float *avg_tat, float *avg_wt,int PROCESS_NUM)
{
    int current_time = 0;
    int total_tat = 0, total_wt = 0;

    for (int i = 0; i < PROCESS_NUM; i++)
    {
        if (current_time < p[i].arrivalTime)
            current_time = p[i].arrivalTime;

        p[i].completionTime = current_time + p[i].burstTime;
        p[i].TAT = p[i].completionTime - p[i].arrivalTime;
        p[i].waitTime = p[i].TAT - p[i].burstTime;

        total_tat += p[i].TAT;
        total_wt += p[i].waitTime;

        current_time = p[i].completionTime;
    }

    *avg_tat = (float)total_tat / PROCESS_NUM;
    *avg_wt = (float)total_wt / PROCESS_NUM;
}
