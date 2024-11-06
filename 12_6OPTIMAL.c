#include <stdio.h>
#include <stdlib.h>
#define MAX_PAGES 100
#define MAX_FRAMES 10

void pageReplacementOptimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES] = {-1};  
    int pageFaults = 0;
    printf("\nOptimal Page Replacement:\n");
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; 
                break;
            }
        }
        if (!found) {
            if (pageFaults < frames) {
                frame[pageFaults] = pages[i];  
            } else {
                int optimal = -1, farthest = -1;
                for (int j = 0; j < frames; j++) {
                    int next = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            next = k;  // Next usage of the page
                            break;
                        }
                    }
                    if (next == -1) {
                        optimal = j;  // This page will not be used again
                        break;
                    }
                    if (next > farthest) {
                        farthest = next;
                        optimal = j;  // Update optimal page index
                    }
                }
                frame[optimal] = pages[i];  // Replace optimal page
            }
            pageFaults++;
        }
        // Print current frame state
        printf("Page: %d | Frame: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
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

    pageReplacementOptimal(pages, n, frames);
    return 0;
}
