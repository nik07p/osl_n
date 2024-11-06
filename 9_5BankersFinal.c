#include <stdio.h>

int required[100], allocate[100], need[100];

int main() {
    int n;
    int max = 12; // Total resources available
    int allocateCount = 0;
    
    printf("Enter the number of processes: \n");
    scanf("%d", &n);
    
    printf("Enter the required resources for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Requirement for Process %d: ", i + 1);
        scanf("%d", &required[i]);
    }
    
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Allocation for Process %d: ", i + 1);
        scanf("%d", &allocate[i]);
        allocateCount += allocate[i];
        need[i] = required[i] - allocate[i];
    }
    
    int available = max - allocateCount;
    int sequence = 0;
    int ans[100], ind = 0;
    int finished[100] = {0};  // Track completed processes

    while (sequence < n) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (finished[j] == 0 && need[j] <= available) {
                ans[ind++] = j + 1;
                sequence++;
                available += allocate[j];
                finished[j] = 1;  // Mark as finished
                found = 1;
            }
        }
        if (!found) {
            break;
        }
    }

    if (sequence == n) {
        printf("The system is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", ans[i]);
        }
        printf("\n");
    } else {
        printf("The system is in an unsafe state.\n");
    }

    return 0;
}
/*
Enter the number of processes: 
3
Enter the required resources for each process:
Requirement for Process 1: 7
Requirement for Process 2: 5
Requirement for Process 3: 3
Enter the allocated resources for each process:
Allocation for Process 1: 3
Allocation for Process 2: 2
Allocation for Process 3: 2
The system is in a safe state.
Safe sequence: P1 P2 P3
*/

/*
Enter the number of processes: 
5
Enter the required resources for each process:
Requirement for Process 1: 7
Requirement for Process 2: 3
Requirement for Process 3: 9
Requirement for Process 4: 2
Requirement for Process 5: 4 
Enter the allocated resources for each process:
Allocation for Process 1: 0
Allocation for Process 2: 2
Allocation for Process 3: 3
Allocation for Process 4: 2
Allocation for Process 5: 0
The system is in a safe state.
Safe sequence: P2 P3 P4 P5 P1
*/