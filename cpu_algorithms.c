#include "cpu_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define MAX_QUEUE 100
void generateData(Process *process_arr)
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

void printData(Process *p_arr)
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

int compare_by_arrival(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->arrivalTime != p2->arrivalTime)
        return p1->arrivalTime - p2->arrivalTime;
    else
        return p1->pid - p2->pid;
}

void fcfs(Process *p, float *avg_tat, float *avg_wt)
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

void enqueue(int *queue, int *rear, int pid) {
    queue[*rear] = pid;
    (*rear)++;
}

int dequeue(int *queue, int *front) {
    int pid = queue[*front];
    (*front)++;
    return pid;
}

int isInQueue(int *queue, int front, int rear, int pid) {
    for (int i = front; i < rear; i++) {
        if (queue[i] == pid)
            return 1;
    }
    return 0;
}

void roundRobin(Process *p, int quantum, float *avg_tat, float *avg_wt) {
    int time = 0;
    int completed = 0;
    int queue[MAX_QUEUE], front = 0, rear = 0;
    int visited[PROCESS_NUM] = {0};

    enqueue(queue, &rear, 0); // add first process (assumes sorted by arrival time)
    visited[0] = 1;

    while (completed < PROCESS_NUM) {
        if (front == rear) {
            // If queue is empty, advance time to next arriving process
            for (int i = 0; i < PROCESS_NUM; i++) {
                if (!p[i].complete) {
                    time = p[i].arrivalTime;
                    enqueue(queue, &rear, i);
                    visited[i] = 1;
                    break;
                }
            }
        }

        int index = dequeue(queue, &front);

        if (p[index].rem_time > 0) {
            int exec_time = (p[index].rem_time > quantum) ? quantum : p[index].rem_time;
            time += exec_time;
            p[index].rem_time -= exec_time;

            // Add newly arrived processes during execution
            for (int i = 0; i < PROCESS_NUM; i++) {
                if (!visited[i] && p[i].arrivalTime <= time) {
                    enqueue(queue, &rear, i);
                    visited[i] = 1;
                }
            }

            if (p[index].rem_time == 0) {
                p[index].complete = true;
                p[index].completionTime = time;
                p[index].TAT = p[index].completionTime - p[index].arrivalTime;
                p[index].waitTime = p[index].TAT - p[index].burstTime;
                completed++;
            } else {
                enqueue(queue, &rear, index); // Put it back in the queue
            }
        }
    }

    int total_tat = 0, total_wt = 0;
    for (int i = 0; i < PROCESS_NUM; i++) {
        total_tat += p[i].TAT;
        total_wt += p[i].waitTime;
    }

    *avg_tat = (float)total_tat / PROCESS_NUM;
    *avg_wt = (float)total_wt / PROCESS_NUM;
}


void sjf(Process *p, float *avg_tat, float *avg_wt)
{
    int completed = 0, time = 0, total_tat = 0, total_wt = 0;
    while (completed < PROCESS_NUM)
    {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < PROCESS_NUM; i++)
        {
            if (!p[i].complete && p[i].arrivalTime <= time && p[i].burstTime < min_bt)
            {
                min_bt = p[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1)
        {
            p[idx].completionTime = time + p[idx].burstTime;
            p[idx].TAT = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitTime = p[idx].TAT - p[idx].burstTime;
            p[idx].complete = true;

            total_tat += p[idx].TAT;
            total_wt += p[idx].waitTime;
            time = p[idx].completionTime;
            completed++;
        }
        else
        {
            time++;
        }
    }

    *avg_tat = (float)total_tat / PROCESS_NUM;
    *avg_wt = (float)total_wt / PROCESS_NUM;
}
