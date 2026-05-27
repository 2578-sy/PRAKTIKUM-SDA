# Tugas Besar / UAS Praktikum Struktur Data dan Algoritma (SDA)

Repositori ini berisi program implementasi berbagai algoritma pengurutan (sorting) yang ditulis menggunakan bahasa pemrograman C. Program ini membandingkan kinerja algoritma sorting dasar (Basic Sorting) dan algoritma sorting lanjutan (Advance Sorting) berdasarkan waktu eksekusinya.

## Anggota Kelompok
* Abdan Syakura (250810701100017)
* Misyqa Aisara (250810701100028)
* Syaula Balqiea Mulyadi (250810701100078)

## Fitur dan Algoritma yang Diimplementasikan

### 1. Sorting Dasar (Basic Sorting)
Menu ini digunakan untuk mengurutkan data bertipe bilangan bulat (integer) acak yang dihasilkan secara otomatis oleh program sebanyak 1000 data. Algoritma yang tersedia:
* **Bubble Sort**: Mengurutkan data dengan membandingkan elemen yang berdekatan secara berulang.
* **Insertion Sort**: Mengurutkan data dengan cara menyisipkan elemen ke posisi yang tepat satu per satu.
* **Selection Sort**: Mengurutkan data dengan mencari elemen terkecil dan menukarnya ke posisi yang benar.

### 2. Advance Sorting
Menu ini digunakan untuk mengurutkan data berupa teks (string/kata) yang dimuat dari file eksternal bernama `words.txt`. Algoritma yang tersedia:
* **Merge Sort**: Menggunakan pendekatan Divide and Conquer dengan membagi array menjadi sub-array lalu menggabungkannya kembali secara terurut.
* **Quick Sort**: Menggunakan elemen pivot untuk mempartisi data menjadi dua bagian sebelum diurutkan.
* **Shell Sort**: Pengembangan dari insertion sort yang membandingkan elemen dengan jarak (gap) tertentu.

### 3. Fitur Tambahan
* **Pengukur Waktu Eksekusi**: Program menghitung durasi proses sorting dalam satuan detik menggunakan library `<time.h>`.
* **Pengacak Data (Shuffle)**: Menjamin data selalu dalam kondisi acak sebelum proses sorting dimulai untuk mendapatkan pengujian yang objektif.

## Prasyarat Sistem
* Compiler C (seperti GCC)
* Terminal atau Command Prompt
* File teks bernama `words.txt` yang diletakkan di direktori yang sama dengan program utama (untuk menu Advance Sorting).

## Struktur File
* `TUGAS02.c` : File kode sumber utama program.
* `words.txt` : File input berisi kumpulan kata yang akan diurutkan (harus dibuat manual atau disediakan terpisah).

## Cara Kompilasi dan Menjalankan Program

1. Buka terminal atau command prompt dan arahkan ke direktori tempat file kode sumber disimpan.
2. Lakukan kompilasi program menggunakan perintah berikut:
   ```bash
   gcc TUGAS02.c -o program_sorting