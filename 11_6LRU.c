#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void pageReplacementLRU(int pages[], int n, int frames) {
    int frame[MAX_FRAMES] = {-1};
    int pageFaults = 0;
    int lastUsed[MAX_FRAMES] = {0}; // To track the last used time of pages

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; 
                lastUsed[j] = i; // Update last used time
                break;
            }
        }

        // If page is not found, it's a page fault
        if (!found) {
            if (pageFaults < frames) {
                frame[pageFaults] = pages[i];
                lastUsed[pageFaults] = i; // Set last used time
            } else {
                // Find the least recently used page
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex]) {
                        lruIndex = j; // Update lruIndex if found an older page
                    }
                }
                frame[lruIndex] = pages[i]; // Replace LRU page
                lastUsed[lruIndex] = i; // Update last used time
            }
            pageFaults++;
        }

        // Print the current state of the frames
        printf("Page: %d | Frame: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }
    
    printf("Total Page Faults (LRU): %d\n", pageFaults);
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

    pageReplacementLRU(pages, n, frames);
    return 0;
}
