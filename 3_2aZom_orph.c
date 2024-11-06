#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 10

void bubble_sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int main() {
    int Arr[SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = SIZE;

    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork Process Failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("I am a child process (PID: %d, PPID: %d). Starting Selection Sort...\n", getpid(), getppid());
        selection_sort(Arr, n);
        printf("Child sorted array (Selection Sort): ");
        for (int i = 0; i < n; i++) {
            printf("%d ", Arr[i]);
        }
        printf("\n");
        
        // Uncomment this sleep for orphan demonstration
        // sleep(5);  // Allow time for the parent to exit before child finishes
        
        exit(0);
    } else {
        // Parent process
        printf("I am the parent process (PID: %d). Exiting immediately...\n", getpid());
        // Uncomment the following lines for the zombie demonstration
        // sleep(5);  // Allow time for the child to finish and become a zombie
        // int status;
        // wait(&status); // Reap child
        exit(0);  // Parent exits immediately to create an orphan
    }

    return 0;
}
