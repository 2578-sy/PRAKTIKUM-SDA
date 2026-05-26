#ifndef ADVANCE_SORTING_H
#define ADVANCE_SORTING_H

#define MAX_LENGTH 100

void mergeSort(char arr[][MAX_LENGTH], int left, int right);
void quickSort(char arr[][MAX_LENGTH], int low, int high);
void shellSort(char arr[][MAX_LENGTH], int n);

void merge(char arr[][MAX_LENGTH], int left, int mid, int right);
int partition(char arr[][MAX_LENGTH], int low, int high);

#endif
