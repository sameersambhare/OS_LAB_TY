#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n, head, DiskSize;

void FIFO(int Arr[], int Head) {
    int TotalHM = 0;
    printf("\nFIFO Order: %d ", Head);
    for (int i = 0; i < n; i++) {
        printf("-> %d ", Arr[i]);
        TotalHM += abs(Arr[i] - Head);
        Head = Arr[i];
    }
    printf("\nTotal Head Movement (FIFO): %d\n", TotalHM);
}

void SSTF(int Arr[], int Head) {
    int TotalHM = 0;
    int Finish[n];
    for (int i = 0; i < n; i++) Finish[i] = 0;

    printf("\nSSTF Order: %d ", Head);
    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!Finish[j] && abs(Arr[j] - Head) < min) {
                min = abs(Arr[j] - Head);
                index = j;
            }
        }
        Finish[index] = 1;
        printf("-> %d ", Arr[index]);
        TotalHM += abs(Arr[index] - Head);
        Head = Arr[index];
    }
    printf("\nTotal Head Movement (SSTF): %d\n", TotalHM);
}

void SCAN(int Arr[], int Head) {
    int TotalHM = 0, Dir;
    printf("Enter Direction (Right = 1 / Left = 0): ");
    scanf("%d", &Dir);

    int Temp[n + 1];
    for (int i = 0; i < n; i++) Temp[i] = Arr[i];
    Temp[n] = Head;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; j++)
            if (Temp[j] > Temp[j + 1]) {
                int t = Temp[j];
                Temp[j] = Temp[j + 1];
                Temp[j + 1] = t;
            }

    int pos;
    for (int i = 0; i <= n; i++)
        if (Temp[i] == Head) pos = i;

    printf("\nSCAN Order: %d", Head);
    if (Dir == 1) {
        for (int i = pos + 1; i <= n; i++) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
        if (Head != DiskSize - 1) {
            TotalHM += abs((DiskSize - 1) - Head);
            printf(" -> %d", DiskSize - 1);
            Head = DiskSize - 1;
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
        if (Head != 0) {
            TotalHM += abs(Head - 0);
            printf(" -> 0");
            Head = 0;
        }
        for (int i = pos + 1; i <= n; i++) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
    }

    printf("\nTotal Head Movement (SCAN): %d\n", TotalHM);
}

void CSCAN(int Arr[], int Head) {
    int TotalHM = 0, Dir;
    printf("Enter Direction (Right = 1 / Left = 0): ");
    scanf("%d", &Dir);

    int Temp[n + 1];
    for (int i = 0; i < n; i++) Temp[i] = Arr[i];
    Temp[n] = Head;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; j++)
            if (Temp[j] > Temp[j + 1]) {
                int t = Temp[j];
                Temp[j] = Temp[j + 1];
                Temp[j + 1] = t;
            }

    int pos;
    for (int i = 0; i <= n; i++)
        if (Temp[i] == Head) pos = i;

    printf("\nC-SCAN Order: %d", Head);
    if (Dir == 1) {
        for (int i = pos + 1; i <= n; i++) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
        if (Head != DiskSize - 1) {
            printf(" -> %d", DiskSize - 1);
            TotalHM += abs(DiskSize - 1 - Head);
            Head = DiskSize - 1;
        }
        printf(" -> 0");
        TotalHM += DiskSize - 1;
        Head = 0;

        for (int i = 0; i < pos; i++) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
        if (Head != 0) {
            printf(" -> 0");
            TotalHM += Head;
            Head = 0;
        }
        printf(" -> %d", DiskSize - 1);
        TotalHM += DiskSize - 1;
        Head = DiskSize - 1;

        for (int i = n; i > pos; i--) {
            printf(" -> %d", Temp[i]);
            TotalHM += abs(Temp[i] - Head);
            Head = Temp[i];
        }
    }

    printf("\nTotal Head Movement (C-SCAN): %d\n", TotalHM);
}

int main() {
    int ch;
    printf("Enter Number of Requests: ");
    scanf("%d", &n);

    int Arr[n];
    printf("Enter the Request Sequence:\n");
    for (int i = 0; i < n; i++) scanf("%d", &Arr[i]);

    printf("Enter Initial Head Position: ");
    scanf("%d", &head);

    printf("Enter Total Disk Size: ");
    scanf("%d", &DiskSize);

    do {
        printf("\n******** MENU ********\n");
        printf("1. FIFO\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                FIFO(Arr, head);
                break;
            case 2:
                SSTF(Arr, head);
                break;
            case 3:
                SCAN(Arr, head);
                break;
            case 4:
                CSCAN(Arr, head);
                break;
            case 5:
                printf("Thank you! Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (ch != 5);

    return 0;
}

