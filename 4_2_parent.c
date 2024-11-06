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

int main() {
    int arr[SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = SIZE;

    // Sort the array using bubble sort
    bubble_sort(arr, n);

    // Print sorted array
    printf("Sorted array (Bubble Sort): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        char *args[SIZE + 2];  // +2 for program name and NULL
        args[0] = "./child";   // Name of the child program

        // Convert sorted array to string arguments
        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(12);  // Allocate memory for each integer as a string
            sprintf(args[i + 1], "%d", arr[i]);  // Convert integers to strings
        }
        args[n + 1] = NULL;  // Last argument must be NULL

        // Execute the child program with sorted array as arguments
        execve(args[0], args, NULL);
        perror("execve failed");  // If execve fails, print error
        exit(1);
    } else {
        // Parent process waits for the child to finish
        wait(NULL);
        printf("Parent process finished.\n");
    }

    return 0;
}
