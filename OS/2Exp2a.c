#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{

    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("\nChild Process (PID: %d)\n", getpid());
        printf("Child sorting in descending order:\n");
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] < arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        for (i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
        printf("Child sleeping for 10 seconds (to create orphan if parent exits)...\n");
        sleep(10);
        printf("Child’s parent PID after sleep: %d\n", getppid());
        printf("Child process ends.\n");
    }

    else
    {
        printf("\nParent Process (PID: %d)\n", getpid());
        sort(arr, n);
        printf("Parent sorting in ascending order:\n");
        for (i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        printf("Parent waiting for child to finish...\n");
        wait(NULL);
        printf("Child completed. Parent exiting.\n");
    }
    return 0;
}