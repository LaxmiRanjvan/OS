#include <stdio.h>
#define MAX_PROCESSES 10
struct Proc {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int start_time;
};
void roundRobin(struct Proc procs[], int n, int time_quantum) {
    int remaining_processes = n;
    int current_time = 0;

    printf("Gantt Chart:\n");
    printf("|");
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (procs[i].remaining_time > 0) {
                int execute_time = (procs[i].remaining_time < time_quantum) ? procs[i].remaining_time : time_quantum;
                procs[i].remaining_time -= execute_time;
                current_time += execute_time;
                printf("  P%d(%d-%d)  |", procs[i].pid, current_time - execute_time, current_time);
                if (procs[i].start_time == -1)
                    procs[i].start_time = current_time - execute_time;
                if (procs[i].remaining_time == 0) {
                    procs[i].completion_time = current_time;
                    remaining_processes--;
                }
            }
        }
    }
    printf("\n");
}
int main() {
    struct Proc procs[MAX_PROCESSES];
    int n, time_quantum;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Proc %d: ", i + 1);
        scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time);
        procs[i].pid = i + 1;
        procs[i].remaining_time = procs[i].burst_time;
        procs[i].start_time = -1;
    }
    printf("\n");
    roundRobin(procs, n, time_quantum);
    printf("| Process | Arrival Time | Burst Time | Start Time | End Time | TAT | WT | RT | RD |\n");
    float total_tat = 0, total_wt = 0, total_rt = 0, total_rd = 0;
    for (int i = 0; i < n; i++) {
        procs[i].turnaround_time = procs[i].completion_time - procs[i].arrival_time;
        procs[i].waiting_time = procs[i].turnaround_time - procs[i].burst_time;
        procs[i].response_time = procs[i].start_time - procs[i].arrival_time;
        float response_delay = (float)procs[i].turnaround_time / procs[i].burst_time;
        printf("|    P%d   |      %2d       |      %2d     |     %2d     |    %2d    |  %2d | %2d | %2d | %.2f |\n",
               procs[i].pid, procs[i].arrival_time, procs[i].burst_time, procs[i].start_time,
               procs[i].completion_time, procs[i].turnaround_time, procs[i].waiting_time,
               procs[i].response_time, response_delay);
        total_tat += procs[i].turnaround_time;
        total_wt += procs[i].waiting_time;
        total_rt += procs[i].response_time;
        total_rd += response_delay;
    }
    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
    float avg_rt = total_rt / n;
    float avg_rd = total_rd / n;
    printf("Average TAT: %.2f\n", avg_tat);
    printf("Average WT: %.2f\n", avg_wt);
    printf("Average RT: %.2f\n", avg_rt);
    printf("Average RD: %.2f\n", avg_rd);
    return 0;
}
/*
0 25
0 6
0 3*/