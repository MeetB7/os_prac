#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 // Maximum number of page frames
#define MAX_PAGES 10 // Maximum number of pages in reference string

// Function prototypes
void fifo(int pages[], int n, int frames);
void lru(int pages[], int n, int frames);

int main()
{
    int pages[MAX_PAGES];
    int n, frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("\nFIFO Page Replacement:\n");
    fifo(pages, n, frames);

    printf("\nLRU Page Replacement:\n");
    lru(pages, n, frames);
    return 0;
}

void fifo(int pages[], int n, int frames)
{
    int frame[MAX_FRAMES];
    int page_faults = 0;
    int current_frame = 0;

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (int j = 0; j < frames;
             j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                break;
            }
        }

        // Page fault: replace the oldest page
        if (!found)
        {
            printf("Page %d caused a page fault.\n", page);
            frame[current_frame] = page;
            current_frame = (current_frame + 1) % frames; // Circular queue
            page_faults++;
        }

        // Display current state of frames
        printf("Frames: ");
        for (int j = 0; j < frames; j++)
        {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", page_faults);
}

void lru(int pages[], int n, int frames)
{
    int frame[MAX_FRAMES];
    int page_faults = 0;
    int counter[MAX_FRAMES] = {0};

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (int j = 0; j < frames;
             j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                counter[j] = i + 1; // Update counter to indicate recent access
                break;
            }
        }

        // Page fault: replace the least recently used page
        if (!found)
        {
            printf("Page %d caused a page fault.\n", page);
            int min_counter =
                counter[0];
            int min_index = 0;
            for (int j = 1; j < frames; j++)
            {
                if (counter[j] < min_counter)
                {
                    min_counter =
                        counter[j];
                    min_index = j;
                }
            }
            frame[min_index] = page;
            counter[min_index] = i + 1; // Update counter to indicate recent access
            page_faults++;
        }

        // Display current state of frames
        printf("Frames: ");
        for (int j = 0; j < frames; j++)
        {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", page_faults);
}