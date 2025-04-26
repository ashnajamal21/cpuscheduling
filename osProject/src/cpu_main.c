// cpu_main.c
#include "cpu_algorithms.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    float avg_fcfs_tat = 0, avg_fcfs_wt = 0;
    float avg_rr_tat = 0, avg_rr_wt = 0;
    float avg_sjf_tat = 0, avg_sjf_wt = 0;
    int choice;
    int PROCESS_NUM;
   
    printf("Enter Number of Processes: ");
    scanf("%d", &PROCESS_NUM);
    Process original[PROCESS_NUM], temp[PROCESS_NUM];
    generateData(original,PROCESS_NUM);

    do {
        printf("\nCPU Scheduling Menu\n");
        printf("1. Run FCFS Scheduling\n");
        printf("2. Run Round Robin Scheduling\n");
        printf("3. Run SJF Scheduling\n");
        printf("4. Complexity Analysis\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice > 5 && choice < 1){
            printf("Invalid Input. Enter a Number Between 1 - 5.\n");
        }
        system("clear");
        memcpy(temp, original, sizeof(original));
        qsort(temp, PROCESS_NUM, sizeof(Process), compare_by_arrival);
        

       
        switch (choice) {
            case 1:
                fcfs(temp, &avg_fcfs_tat, &avg_fcfs_wt,PROCESS_NUM);
                printData(temp,PROCESS_NUM);
                printf("\nFCFS Average Turn Around Time: %.2f\n", avg_fcfs_tat);
                printf("FCFS Average Waiting Time: %.2f\n", avg_fcfs_wt);
                break;

            case 2:
                roundRobin(temp, 10, &avg_rr_tat, &avg_rr_wt,PROCESS_NUM);
                printData(temp,PROCESS_NUM);
                printf("\nRound Robin Average Turn Around Time: %.2f\n", avg_rr_tat);
                printf("Round Robin Average Waiting Time: %.2f\n", avg_rr_wt);
                break;

            case 3:
                sjf(temp, &avg_sjf_tat, &avg_sjf_wt,PROCESS_NUM);
                printData(temp,PROCESS_NUM);
                printf("\nSJF Average Turn Around Time: %.2f\n", avg_sjf_tat);
                printf("SJF Average Waiting Time: %.2f\n", avg_sjf_wt);
                break;

            case 4:
                printf("\n--- Complexity Analysis ---\n");

                sjf(temp, &avg_sjf_tat, &avg_sjf_wt,PROCESS_NUM);
                printf("SJF -> TAT: %.2f, WT: %.2f\n", avg_sjf_tat, avg_sjf_wt);

                fcfs(temp, &avg_fcfs_tat, &avg_fcfs_wt,PROCESS_NUM);
                printf("FCFS -> TAT: %.2f, WT: %.2f\n", avg_fcfs_tat, avg_fcfs_wt);

                roundRobin(temp, 10, &avg_rr_tat, &avg_rr_wt,PROCESS_NUM);
                printf("Round Robin -> TAT: %.2f, WT: %.2f\n", avg_rr_tat, avg_rr_wt);

                

                float min_avg = avg_fcfs_tat + avg_fcfs_wt;
                char best_algo[20] = "FCFS";

                if ((avg_rr_tat + avg_rr_wt) < min_avg) {
                    min_avg = avg_rr_tat + avg_rr_wt;
                    strcpy(best_algo, "Round Robin");
                }
                if ((avg_sjf_tat + avg_sjf_wt) < min_avg) {
                    min_avg = avg_sjf_tat + avg_sjf_wt;
                    strcpy(best_algo, "SJF");
                }

                printf("\nThe most efficient algorithm is: %s\n", best_algo);
                break;

            case 5:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}