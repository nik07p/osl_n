#include <stdio.h>

int arrival_t[100], burst_t[100], remaining_t[100], ct[100];

int main() {
    int n, time_quantum;
    
    // Input the number of processes
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    
    // Input arrival and burst times
    printf("Enter details of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &arrival_t[i]);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &burst_t[i]);
        remaining_t[i] = burst_t[i];
    }
    
    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    
    int current_time = 0, count = 0;

    // Round Robin scheduling logic
    while (count < n) {
        int done = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_t[i] > 0 && arrival_t[i] <= current_time) {
                done = 1; // A process is ready to run
                if (remaining_t[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_t[i] -= time_quantum;
                } else {
                    current_time += remaining_t[i];
                    ct[i] = current_time; // Completion time for the process
                    remaining_t[i] = 0; // Process finished
                    count++; // Increment count of completed processes
                }
            }
        }
        if (!done) {
            current_time++; // No process is ready, increment time
        }
    }

    // Calculating average waiting and turnaround times
    double avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        int TAT = ct[i] - arrival_t[i]; // Turnaround Time
        avg_tat += TAT; // Summing Turnaround Times
        avg_wt += TAT - burst_t[i]; // Waiting Time
    }
    
    // Display the results
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);
    printf("Average Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
