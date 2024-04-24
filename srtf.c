#include <stdio.h>
#include <limits.h> // For INT_MAX
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

// Function to find the process with the shortest remaining burst time
int findShortestJob(struct Proc procs[], int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_job_time = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (procs[i].arrival_time <= current_time && procs[i].remaining_time < shortest_job_time && procs[i].remaining_time > 0) {
            shortest_job_index = i;
            shortest_job_time = procs[i].remaining_time;
        }
    }
    return shortest_job_index;
}

void SRTF(struct Proc procs[], int n) {
    int remaining_processes = n;
    int current_time = 0;

    printf("Gantt Chart:\n");
    printf("|");
    while (remaining_processes > 0) {
        int shortest_job_index = findShortestJob(procs, n, current_time);
        if (shortest_job_index == -1) {
            current_time++; // No process available, move to the next unit of time
            continue;
        }
        if (procs[shortest_job_index].start_time == -1)
            procs[shortest_job_index].start_time = current_time;

        procs[shortest_job_index].remaining_time--;
        current_time++;
        printf("  P%d(%d-%d)  |", procs[shortest_job_index].pid, current_time - 1, current_time);
        if (procs[shortest_job_index].remaining_time == 0) {
            procs[shortest_job_index].completion_time = current_time;
            remaining_processes--;
        }
    }
    printf("\n");
}

int main() {
    struct Proc procs[MAX_PROCESSES];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Proc %d: ", i + 1);
        scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time);
        procs[i].pid = i + 1;
        procs[i].remaining_time = procs[i].burst_time;
        procs[i].start_time = -1;
    }
    printf("\n");
    SRTF(procs, n);

    printf("| Process | Arrival Time | Burst Time | Start Time | End Time | TAT | WT | RT |\n");
    float total_tat = 0, total_wt = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        procs[i].turnaround_time = procs[i].completion_time - procs[i].arrival_time;
        procs[i].waiting_time = procs[i].turnaround_time - procs[i].burst_time;
        procs[i].response_time = procs[i].start_time - procs[i].arrival_time;
        printf("|    P%d   |      %2d       |      %2d     |     %2d     |    %2d    |  %2d | %2d | %2d |\n",
               procs[i].pid, procs[i].arrival_time, procs[i].burst_time, procs[i].start_time,
               procs[i].completion_time, procs[i].turnaround_time, procs[i].waiting_time,
               procs[i].response_time);
        total_tat += procs[i].turnaround_time;
        total_wt += procs[i].waiting_time;
        total_rt += procs[i].response_time;
    }
    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
    float avg_rt = total_rt / n;
    printf("Average TAT: %.2f\n", avg_tat);
    printf("Average WT: %.2f\n", avg_wt);
    printf("Average RT: %.2f\n", avg_rt);
    return 0;
}
/*Proc 1: 0 5
Proc 2: 1 3
Proc 3: 2 4
Proc 4: 4 1*/