#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Child process displaying array in reverse order:\n");
    for (int i = argc - 1; i > 0; i--) {  // Start from argc - 1 (the last element) to 1 (skipping the program name)
        printf("%s ", argv[i]);  // Print each argument
    }
    printf("\n");
    return 0;
}
