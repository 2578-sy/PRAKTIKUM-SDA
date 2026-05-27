#include <stdio.h>      // Library standar input/output
#include <stdlib.h>     // Library fungsi umum seperti rand(), srand()
#include <string.h>     // Library manipulasi string seperti strcpy()
#include <time.h>       // Library untuk fungsi waktu


#include "sortingdasar.h"       // Header file sorting dasar
#include "advancesorting.h"     // Header file sorting lanjutan

#define MAX_DATA 1000
#define MAX_WORDS 500000 // Dinaikkan menjadi 500k agar mencakup seluruh isi dataset Kaggle
#define MAX_LENGTH 100   // Maksimum panjang tiap kata/string

/* Array words diletakkan di luar main (Global Variable). 
   Hal ini untuk memindahkan alokasi data besar dari Stack ke Data Segment 
   agar program tidak crash karena Stack Overflow saat dijalankan.
*/
char words[MAX_WORDS][MAX_LENGTH];

/* =========================================================
   DEKLARASI FUNCTION
   ========================================================= */

void generateRandomData(int arr[], int n);                  // Membuat data integer random
void shuffleInt(int arr[], int n);                          // Mengacak  urutan data integer 
void shuffleString(char arr[][MAX_LENGTH], int n);          // Mengacak urutan data string
void printIntData(int arr[], int n);                        // Menampilkan data integer (20 data pertama)     
void printStringData(char arr[][MAX_LENGTH], int n);        // Menampilkan data string (20 data pertama)
int loadWords(char filename[], char words[][MAX_LENGTH]);   // Membaca kata dari file txt

/* =========================================================
   MAIN PROGRAM
   ========================================================= */
int main()
{
    int choice;         // Menu utama
    int subChoice;      // Sub menu sorting  
    int data[MAX_DATA];
    int totalWords = 0;

    // Variabel untuk menghitung waktu eksekusi
    clock_t start, end;
    double executionTime;

    // Seed random berdasarkan waktu sekarang
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
        
       /* =========================================================
           MENU SORTING DASAR
           ========================================================= */

        case 1:
            generateRandomData(data, MAX_DATA);     // Generate data random
            shuffleInt(data, MAX_DATA);             // Mengacak urutan data agar tidak selalu dalam kondisi terurut saat di-sort  

            printf("\n====================================\n");
            printf("         SORTING DASAR\n");
            printf("====================================\n");
            printf("1. Bubble Sort\n");
            printf("2. Insertion Sort\n");
            printf("3. Selection Sort\n");
            printf("4. Kembali\n");
            printf("Pilih metode : ");
            scanf("%d", &subChoice);

            // Kembali ke menu utama
            if (subChoice == 4)
            {
                break;
            }

            // Menampilkan 20 data pertama sebelum sorting
            printf("\nData Sebelum Sorting (20 data pertama):\n");
            printIntData(data, 20);

            start = clock();    // Mulai hitung waktu

            // Pemilihan metode sorting
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

            end = clock();                                                  // Selesai hitung waktu
            executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;       // Hitung waktu eksekusi dalam detik

            // Menampilkan data setelah sorting
            printf("\nData Setelah Sorting (20 data pertama):\n");
            printIntData(data, 20);

            // Menampilkan waktu eksekusi
            printf("\nWaktu Eksekusi : %.6f detik\n", executionTime);
            break;

         /* =========================================================
           MENU ADVANCE SORTING
           ========================================================= */

        case 2:
            // Sesuai ketentuan, membaca data langsung dari file dataset .txt
            if (totalWords == 0) {
                totalWords = loadWords("words.txt", words);
            }

            // Jika file tidak ditemukan atau kosong
            if (totalWords == 0)
            {
                printf("\nFile words.txt tidak ditemukan atau kosong!\n");
                break;
            }

            // Mengacak data string
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

             // Kembali ke menu utama
            if (subChoice == 4)
            {
                break;
            }

            // Menampilkan 20 kata pertama sebelum sorting
            printf("\nData Sebelum Sorting (20 kata pertama):\n");
            printStringData(words, 20);

            // Mulai hitung waktu
            start = clock();

            // Pemilihan metode advance sorting
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

            end = clock();                                                 // Selesai hitung waktu  
            executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;      // Menghitung waktu eksekusi

            // Menampilkan hasil sorting
            printf("\nData Setelah Sorting (20 kata pertama):\n");
            printStringData(words, 20);

            // Menampilkan waktu eksekusi
            printf("\nWaktu Eksekusi : %.6f detik\n", executionTime);
            break;

        /* =========================================================
           KELUAR PROGRAM
           ========================================================= */
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

/*
   Function untuk membuat data integer random
*/
void generateRandomData(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

/*
   Function untuk mengacak data integer
*/
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

/*
   Function untuk mengacak data string
*/
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

/*
   Function untuk menampilkan data integer
*/
void printIntData(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
   Function untuk menampilkan data string
*/
void printStringData(char arr[][MAX_LENGTH], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", arr[i]);
    }
}

/*
   Function untuk membaca kata dari file txt
*/
int loadWords(char filename[], char words[][MAX_LENGTH])
{
    // Membuka file dalam mode read
    FILE *file = fopen(filename, "r");
    
    // Jika file gagal dibuka
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;

     // Membaca kata satu per satu dari file
    while (fscanf(file, "%99s", words[count]) != EOF)
    {
        count++;

        // Membatasi jumlah data agar tidak melebihi kapasitas array
        if (count >= MAX_WORDS)
        {
            break;
        }
    }
    fclose(file);       // Menutup file
    return count;       // Mengembalikan jumlah kata yang berhasil dibaca
}