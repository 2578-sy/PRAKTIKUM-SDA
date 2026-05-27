#include <string.h>
#include <stdlib.h>
#include "advance_sorting.h"

// Gunakan strcasecmp (POSIX) atau stricmp (Windows) agar case-insensitive
#ifdef _WIN32
    #define COMPARE_STR stricmp
#else
    #define COMPARE_STR strcasecmp
#endif

/* =========================================================
   MERGE SORT
   ========================================================= */
void merge(char arr[][MAX_LENGTH], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Alokasi dinamis di heap memori untuk mencegah Stack Overflow
    char (*L)[MAX_LENGTH] = malloc(n1 * sizeof(*L));
    char (*R)[MAX_LENGTH] = malloc(n2 * sizeof(*R));

    // Validasi alokasi memori gagl
    if (L == NULL || R == NULL) {
        return; 
    }

    for (int i = 0; i < n1; i++)
    {
        strcpy(L[i], arr[left + i]);
    }
    for (int j = 0; j < n2; j++)
    {
        strcpy(R[j], arr[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (COMPARE_STR(L[i], R[j]) <= 0)
        {
            strcpy(arr[k], L[i]);
            i++;
        }
        else
        {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }
    while (j < n2)
    {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }

    // Wajib dibebaskan setelah selesai digunakan
    free(L);
    free(R);
}

void mergeSort(char arr[][MAX_LENGTH], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* =========================================================
   QUICK SORT
   ========================================================= */
int partition(char arr[][MAX_LENGTH], int low, int high)
{
    char pivot[MAX_LENGTH];
    strcpy(pivot, arr[high]);

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (COMPARE_STR(arr[j], pivot) < 0)
        {
            i++;
            char temp[MAX_LENGTH];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
        }
    }

    char temp[MAX_LENGTH];
    strcpy(temp, arr[i + 1]);
    strcpy(arr[i + 1], arr[high]);
    strcpy(arr[high], temp);

    return i + 1;
}

void quickSort(char arr[][MAX_LENGTH], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* =========================================================
   SHELL SORT
   ========================================================= */
void shellSort(char arr[][MAX_LENGTH], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            char temp[MAX_LENGTH];
            strcpy(temp, arr[i]);

            int j;
            for (j = i; j >= gap && COMPARE_STR(arr[j - gap], temp) > 0; j -= gap)
            {
                strcpy(arr[j], arr[j - gap]);
            }
            strcpy(arr[j], temp);
        }
    }
}
