#include <stdio.h>
#include <Windows.h>

#define MAX_SIZE 100

DWORD WINAPI min_max(LPVOID lpParam);
DWORD WINAPI average(LPVOID lpParam);

int arr[MAX_SIZE];
int n;

int main()
{
    HANDLE hThreadMinMax, hThreadAverage;
    DWORD dwThreadMinMax, dwThreadAverage;

    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    hThreadMinMax = CreateThread(NULL, 0, min_max, NULL, 0, &dwThreadMinMax);
    if (hThreadMinMax == NULL) {
        printf("Error creating min_max thread\n");
        return 1;
    }

    hThreadAverage = CreateThread(NULL, 0, average, NULL, 0, &dwThreadAverage);
    if (hThreadAverage == NULL) {
        printf("Error creating average thread\n");
        return 1;
    }

    WaitForSingleObject(hThreadMinMax, INFINITE);
    WaitForSingleObject(hThreadAverage, INFINITE);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    int avg = sum / n;
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == min || arr[i] == max) {
            arr[i] = avg;
        }
    }

    printf("New array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

DWORD WINAPI min_max(LPVOID lpParam)
{
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
        Sleep(7);
    }
    printf("Min: %d\nMax: %d\n", min, max);
    return 0;
}

DWORD WINAPI average(LPVOID lpParam)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        Sleep(12);
    }
    double avg = (double)sum / n;
    printf("Average: %lf\n", avg);
    return 0;
}