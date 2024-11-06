#include <stdio.h>
#include <limits.h>

int arrival_t[100], burst_t[100], ct[100], temp[100];

int main() {
    int i, smallest, count = 0, j, n;
    double avg_wt = 0, avg_tat = 0;
    printf("\nEnter the total number of processes: ");
    scanf("%d", &n);
    
    // Get the details of the processes
    for (i = 0; i < n; i++) {
        printf("\nEnter Arrival Time for P%d: ", i + 1);
        scanf("%d", &arrival_t[i]);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &burst_t[i]);
        temp[i] = burst_t[i];  // Store original burst time for TAT calculation
    }
    
    // Set a very large value for initial comparison (to act like infinity)
    burst_t[99] = INT_MAX; 

    // Start the scheduling
    for (i = 0; count != n; i++) {
        smallest = 99; // Initialize smallest index

        // Find the process with the smallest remaining burst time that has arrived
        for (j = 0; j < n; j++) {
            if (arrival_t[j] <= i && burst_t[j] < burst_t[smallest] && burst_t[j] > 0) {
                smallest = j;
            }
        }

        // Execute the process with the smallest burst time
        burst_t[smallest]--;
        
        // If the process is completed
        if (burst_t[smallest] == 0) {
            count++;
            ct[smallest] = i + 1; // Store completion time
        }
    }

    // Calculate Average Turnaround Time and Average Waiting Time
    for (i = 0; i < n; i++) {
        int TAT = ct[i] - arrival_t[i]; // Turnaround Time
        avg_tat += TAT;                  // Sum Turnaround Time
        avg_wt += TAT - temp[i];        // Calculate Waiting Time
    }

    printf("Average Turnaround Time: %lf\n", avg_tat / n);
    printf("Average Waiting Time: %lf\n", avg_wt / n);
    
    return 0;
}
