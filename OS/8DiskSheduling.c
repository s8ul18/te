#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void SSTF(int req[], int n, int head)
{
    int completed[n], total = 0, count = 0, pos = head;
    for (int i = 0; i < n; i++)
        completed[i] = 0;

    printf("\nSSTF Sequence: %d", head);
    while (count < n)
    {
        int min = 9999, index = -1;
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && abs(req[i] - pos) < min)
            {
                min = abs(req[i] - pos);

                index = i;
            }
        }
        total += abs(req[index] - pos);
        pos = req[index];
        completed[index] = 1;
        printf(" -> %d", pos);
        count++;
    }
    printf("\nTotal Head Movement: %d\n", total);
}
void SCAN(int req[], int n, int head, int disk_size)
{
    int total = 0, index, pos = head;
    sort(req, n);

    for (index = 0; index < n && req[index] < head; index++)
        ;
    printf("\nSCAN Sequence: %d", head);

    for (int i = index; i < n; i++)
    {
        total += abs(req[i] - pos);
        pos = req[i];
        printf(" -> %d", pos);
    }
    total += abs((disk_size - 1) - pos);
    pos = disk_size - 1;
    for (int i = index - 1; i >= 0; i--)
    {
        total += abs(req[i] - pos);
        pos = req[i];
        printf(" -> %d", pos);
    }
    printf("\nTotal Head Movement: %d\n", total);
}
void CLOOK(int req[], int n, int head)
{
    int total = 0, index, pos = head;
    sort(req, n);
    for (index = 0; index < n && req[index] < head; index++)
        ;

    printf("\nC-LOOK Sequence: %d", head);
    for (int i = index; i < n; i++)
    {
        total += abs(req[i] - pos);
        pos = req[i];
        printf(" -> %d", pos);
    }
    total += abs(pos - req[0]);
    pos = req[0];
    printf(" -> %d", pos);

    for (int i = 1; i < index; i++)
    {
        total += abs(req[i] - pos);
        pos = req[i];
        printf(" -> %d", pos);
    }
    printf("\nTotal Head Movement: %d\n", total);
}
int main()
{
    int n, head, disk_size;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    SSTF(req, n, head);
    SCAN(req, n, head, disk_size);
    CLOOK(req, n, head);
    return 0;
}
