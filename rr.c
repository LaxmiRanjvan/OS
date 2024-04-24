#include <stdio.h>
#include <limits.h> // Include limits.h for INT_MAX constant

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

// Function declaration for the Round Robin scheduling algorithm
void roundRobin(struct Proc procs[], int n, int time_quantum);

int main() {
    struct Proc procs[MAX_PROCESSES]; // Array to store process information
    int n, time_quantum;

    // Input the number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Input arrival time and burst time for each process
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Proc %d: ", i + 1);
        scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time);
        procs[i].pid = i + 1;
        procs[i].remaining_time = procs[i].burst_time;
        procs[i].start_time = -1; // Initialize start time to -1
    }

    printf("\n");

    // Execute Round Robin scheduling algorithm
    roundRobin(procs, n, time_quantum);

    // Print table headers for process metrics
    printf("| Process | Arrival Time | Burst Time | Start Time | End Time | TAT | WT | RT | RD |\n");

    // Calculate and print process metrics and totals
    float total_tat = 0, total_wt = 0, total_rt = 0, total_rd = 0;
    for (int i = 0; i < n; i++) {
        // Calculate process metrics
        procs[i].turnaround_time = procs[i].completion_time - procs[i].arrival_time;
        procs[i].waiting_time = procs[i].turnaround_time - procs[i].burst_time;
        procs[i].response_time = procs[i].start_time - procs[i].arrival_time;
        float response_delay = (float)procs[i].turnaround_time / procs[i].burst_time;

        // Print process metrics
        printf("|    P%d   |      %2d       |      %2d     |     %2d     |    %2d    |  %2d | %2d | %2d | %.2f |\n",
               procs[i].pid, procs[i].arrival_time, procs[i].burst_time, procs[i].start_time,
               procs[i].completion_time, procs[i].turnaround_time, procs[i].waiting_time,
               procs[i].response_time, response_delay);

        // Update total metrics
        total_tat += procs[i].turnaround_time;
        total_wt += procs[i].waiting_time;
        total_rt += procs[i].response_time;
        total_rd += response_delay;
    }

    // Calculate and print average metrics
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

// Round Robin scheduling algorithm implementation
void roundRobin(struct Proc procs[], int n, int time_quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int completed[MAX_PROCESSES] = {0}; // Array to track completed processes

    // Print Gantt chart header
    printf("Gantt Chart:\n");
    printf("|");

    while (remaining_processes > 0) {
        int flag = 0; // Flag to track if any process is executed in the current time quantum

        // Iterate through each process
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and is not completed
            if (procs[i].arrival_time <= current_time && procs[i].remaining_time > 0) {
                int execute_time = (procs[i].remaining_time < time_quantum) ? procs[i].remaining_time : time_quantum;
                procs[i].remaining_time -= execute_time;
                current_time += execute_time;

                printf("  P%d(%d-%d)  |", procs[i].pid, current_time - execute_time, current_time);

                if (procs[i].start_time == -1)
                    procs[i].start_time = current_time - execute_time;

                if (procs[i].remaining_time == 0) {
                    procs[i].completion_time = current_time;
                    remaining_processes--;
                    completed[i] = 1; // Mark the process as completed
                }

                flag = 1; // Set flag indicating that a process is executed in this time quantum
            }
        }

        // If no process is executed in the current time quantum, skip to the next arrival time
        if (flag == 0) {
            int next_arrival = INT_MAX; // Initialize next arrival time to maximum possible value

            // Find the next arrival time
            for (int i = 0; i < n; i++) {
                if (procs[i].arrival_time > current_time && procs[i].arrival_time < next_arrival && !completed[i]) {
                    next_arrival = procs[i].arrival_time;
                }
            }

            // Skip to the next arrival time
            if (next_arrival != INT_MAX) {
                current_time = next_arrival;
                printf("  IDLE(%d-%d)  |", current_time, next_arrival);
            }
        }
    }

    printf("\n");
}
