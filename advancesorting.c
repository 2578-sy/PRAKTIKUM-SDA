#include <string.h>
#include <stdlib.h>
#include "advance_sorting.h"

// Perbandingan string tanpa membedakan huruf besar/kecil
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
    int n1 = mid - left + 1; // ukuran bagian kiri
    int n2 = right - mid;    // ukuran bagian kanan

    // alokasi array sementara
    char (*L)[MAX_LENGTH] = malloc(n1 * sizeof(*L));
    char (*R)[MAX_LENGTH] = malloc(n2 * sizeof(*R));

    // cek alokasi memori
    if (L == NULL || R == NULL) {
        return;
    }

    for (int i = 0; i < n1; i++)
    {
        strcpy(L[i], arr[left + i]); // salin data kiri
    }

    for (int j = 0; j < n2; j++)
    {
        strcpy(R[j], arr[mid + 1 + j]); // salin data kanan
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (COMPARE_STR(L[i], R[j]) <= 0) // pilih data lebih kecil
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
        strcpy(arr[k], L[i]); // salin sisa kiri
        i++;
        k++;
    }

    while (j < n2)
    {
        strcpy(arr[k], R[j]); // salin sisa kanan
        j++;
        k++;
    }

    free(L); // bebaskan memori kiri
    free(R); // bebaskan memori kanan
}

void mergeSort(char arr[][MAX_LENGTH], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2; // cari titik tengah

        mergeSort(arr, left, mid);      // urutkan kiri
        mergeSort(arr, mid + 1, right); // urutkan kanan
        merge(arr, left, mid, right);   // gabungkan hasil
    }
}

/* =========================================================
   QUICK SORT
   ========================================================= */
int partition(char arr[][MAX_LENGTH], int low, int high)
{
    char pivot[MAX_LENGTH];
    strcpy(pivot, arr[high]); // gunakan elemen terakhir sebagai pivot

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (COMPARE_STR(arr[j], pivot) < 0) // jika lebih kecil dari pivot
        {
            i++;

            char temp[MAX_LENGTH];
            strcpy(temp, arr[i]);     // swap data
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
        }
    }

    char temp[MAX_LENGTH];
    strcpy(temp, arr[i + 1]); // letakkan pivot di posisi benar
    strcpy(arr[i + 1], arr[high]);
    strcpy(arr[high], temp);

    return i + 1; // kembalikan indeks pivot
}

void quickSort(char arr[][MAX_LENGTH], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // bagi array

        quickSort(arr, low, pi - 1);  // urutkan kiri pivot
        quickSort(arr, pi + 1, high); // urutkan kanan pivot
    }
}

/* =========================================================
   SHELL SORT
   ========================================================= */
void shellSort(char arr[][MAX_LENGTH], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) // kurangi gap bertahap
    {
        for (int i = gap; i < n; i++)
        {
            char temp[MAX_LENGTH];
            strcpy(temp, arr[i]); // simpan data saat ini

            int j;
            for (j = i; j >= gap && COMPARE_STR(arr[j - gap], temp) > 0; j -= gap)
            {
                strcpy(arr[j], arr[j - gap]); // geser data
            }

            strcpy(arr[j], temp); // tempatkan data
        }
    }
}
