#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sortingdasar.h"
#include "advancesorting.h"

#define MAX_DATA 1000
#define MAX_WORDS 500000 // Dinaikkan menjadi 500k agar mencakup seluruh isi dataset Kaggle
#define MAX_LENGTH 100

/* Array words diletakkan di luar main (Global Variable). 
   Hal ini untuk memindahkan alokasi data besar dari Stack ke Data Segment 
   agar program tidak crash karena Stack Overflow saat dijalankan.
*/
char words[MAX_WORDS][MAX_LENGTH];

void generateRandomData(int arr[], int n);
void shuffleInt(int arr[], int n);
void shuffleString(char arr[][MAX_LENGTH], int n);
void printIntData(int arr[], int n);
void printStringData(char arr[][MAX_LENGTH], int n);
int loadWords(char filename[], char words[][MAX_LENGTH]);

/* =========================================================
   MAIN PROGRAM
   ========================================================= */
int main()
{
    int choice;
    int subChoice;
    int data[MAX_DATA];
    int totalWords = 0;

    clock_t start, end;
    double executionTime;

    srand(time(NULL));

    do
    {
        printf("\n====================================\n");
        printf("         MENU UTAMA\n");
        printf("====================================\n");
        printf("1. Sorting Dasar\n");
        printf("2. Advance Sorting\n");
        printf("3. Keluar\n");
        printf("Pilih menu : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            generateRandomData(data, MAX_DATA);
            shuffleInt(data, MAX_DATA);

            printf("\n====================================\n");
            printf("         SORTING DASAR\n");
            printf("====================================\n");
            printf("1. Bubble Sort\n");
            printf("2. Insertion Sort\n");
            printf("3. Selection Sort\n");
            printf("4. Kembali\n");
            printf("Pilih metode : ");
            scanf("%d", &subChoice);

            if (subChoice == 4)
            {
                break;
            }

            printf("\nData Sebelum Sorting (20 data pertama):\n");
            printIntData(data, 20);

            start = clock();

            switch (subChoice)
            {
            case 1:
                bubbleSort(data, MAX_DATA);
                printf("\nMetode : Bubble Sort\n");
                break;
            case 2:
                insertionSort(data, MAX_DATA);
                printf("\nMetode : Insertion Sort\n");
                break;
            case 3:
                selectionSort(data, MAX_DATA);
                printf("\nMetode : Selection Sort\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                continue;
            }

            end = clock();
            executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("\nData Setelah Sorting (20 data pertama):\n");
            printIntData(data, 20);

            printf("\nWaktu Eksekusi : %.6f detik\n", executionTime);
            break;

        case 2:
            // Sesuai ketentuan, membaca data langsung dari file dataset .txt
            if (totalWords == 0) {
                totalWords = loadWords("words.txt", words);
            }

            if (totalWords == 0)
            {
                printf("\nFile words.txt tidak ditemukan atau kosong!\n");
                break;
            }

            shuffleString(words, totalWords);

            printf("\n====================================\n");
            printf("         ADVANCE SORTING\n");
            printf("====================================\n");
            printf("1. Merge Sort\n");
            printf("2. Quick Sort\n");
            printf("3. Shell Sort\n");
            printf("4. Kembali\n");
            printf("Pilih metode : ");
            scanf("%d", &subChoice);

            if (subChoice == 4)
            {
                break;
            }

            printf("\nData Sebelum Sorting (20 kata pertama):\n");
            printStringData(words, 20);

            start = clock();

            switch (subChoice)
            {
            case 1:
                mergeSort(words, 0, totalWords - 1);
                printf("\nMetode : Merge Sort\n");
                break;
            case 2:
                quickSort(words, 0, totalWords - 1);
                printf("\nMetode : Quick Sort\n");
                break;
            case 3:
                shellSort(words, totalWords);
                printf("\nMetode : Shell Sort\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                continue;
            }

            end = clock();
            executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("\nData Setelah Sorting (20 kata pertama):\n");
            printStringData(words, 20);

            printf("\nWaktu Eksekusi : %.6f detik\n", executionTime);
            break;

        case 3:
            printf("\nProgram selesai.\n");
            break;

        default:
            printf("\nPilihan tidak valid!\n");
        }

    } while (choice != 3);

    return 0;
}

/* =========================================================
   FUNGSI-FUNGSI HELPER
   ========================================================= */

void generateRandomData(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

void shuffleInt(int arr[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void shuffleString(char arr[][MAX_LENGTH], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp[MAX_LENGTH];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void printIntData(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printStringData(char arr[][MAX_LENGTH], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", arr[i]);
    }
}

int loadWords(char filename[], char words[][MAX_LENGTH])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%99s", words[count]) != EOF)
    {
        count++;
        if (count >= MAX_WORDS)
        {
            break;
        }
    }
    fclose(file);
    return count;
}