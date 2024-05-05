#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100  // Maximum number of disk requests
#define MAX_CYLINDERS 200 // Maximum number of cylinders on the disk

// Function prototypes 
void fcfs(int requests[], int n, int initial_position);
void scan(int requests[], int n, int initial_position, int cylinders);
void c_scan(int requests[], int n, int initial_position, int cylinders);

int main()
{
    int requests[MAX_REQUESTS];
    int n, initial_position, cylinders;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d",
          &initial_position);

    printf("Enter the total number of cylinders on the disk: ");
    scanf("%d", &cylinders);

    printf("\nFirst-Come, First-Served (FCFS):\n");
    fcfs(requests, n,
         initial_position);

    printf("\nSCAN:\n");
    scan(requests, n, initial_position, cylinders);

    printf("\nC-SCAN:\n");
    c_scan(requests, n, initial_position,
           cylinders);

    return 0;
}

void fcfs(int requests[], int n, int initial_position)
{
    int total_seek_time =
        0;

    printf("Sequence of servicing requests:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
        total_seek_time += abs(requests[i] -
                               initial_position);
        initial_position = requests[i];
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
}

void scan(int requests[], int n, int initial_position, int cylinders)
{
    int
        total_seek_time = 0;
    int direction = 1; // 1 for right, -1 for left

    printf("Sequence of servicing requests:\n");

    // Sort requests to service in ascending order     
    for (int i = 0; i < n - 1; i++)
{
    for (int j = 0; j < n - i - 1; j++)
    {
        if (requests[j] >
            requests[j + 1])
        {
            int temp = requests[j];
            requests[j] =
                requests[j + 1];
            requests[j + 1] = temp;
        }
    }
}

// Find the index where the disk head should reverse direction     
int reverse_index = 0;
while (reverse_index < n &&
       requests[reverse_index] < initial_position)
{
    reverse_index++;
}

// Service requests in one direction     
for (int i = reverse_index - 1; i>= 0; i--)
{
    printf("%d ", requests[i]);
    total_seek_time +=
        abs(requests[i] - initial_position);
    initial_position = requests[i];
}

// Service requests in the reverse direction     
for (int i = reverse_index; i < n; i++)
{
    printf("%d ", requests[i]);
    total_seek_time +=
        abs(requests[i] - initial_position);
    initial_position = requests[i];
}

printf("\nTotal seek time: %d\n", total_seek_time);
}

void c_scan(int requests[], int n, int initial_position, int cylinders)
{
    int
        total_seek_time = 0;

    printf("Sequence of servicing requests:\n");

    // Sort requests to service in ascending order     
    for (int i = 0; i < n - 1; i++)
{
    for (int j = 0; j < n - i - 1; j++)
    {
        if (requests[j] >
            requests[j + 1])
        {
            int temp = requests[j];
            requests[j] =
                requests[j + 1];
            requests[j + 1] = temp;
        }
    }
}

// Service requests in one direction     
for (int i = 0; i < n && requests[i] < initial_position; i++)
{
    printf("%d ", requests[i]);
    total_seek_time += abs(requests[i] - initial_position);
    initial_position = requests[i];
}

// Jump to the beginning of the disk     
printf("%d ", 0);
total_seek_time += initial_position;

// Service requests in the reverse direction     
for (int i = n - 1; i >= 0 &&requests[i] >= initial_position; i--)
{
    printf("%d ", requests[i]);
    total_seek_time += abs(requests[i] - initial_position);
    initial_position = requests[i];
}

printf("\nTotal seek time: %d\n", total_seek_time);
}