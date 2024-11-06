#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void pageReplacementFCFS(int pages[], int n, int frames) {
    int frame[MAX_FRAMES] = {-1}; 
    int pageFaults = 0;

    printf("\nFCFS Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the current page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;  
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!found) {
            // Place the new page in the next available frame
            frame[pageFaults % frames] = pages[i];
            pageFaults++;
        }

        // Print the current state of the frames
        printf("Page: %d | Frame: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (FCFS): %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES];
    int n, frames;

    printf("Enter the number of pages (max %d): ", MAX_PAGES);
    scanf("%d", &n);
    printf("Enter the page numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &frames);

    if (frames < 3) {
        printf("Error: Frame size must be at least 3.\n");
        return 1;
    }

    pageReplacementFCFS(pages, n, frames);
    return 0;
}
