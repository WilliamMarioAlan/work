#ifndef __MYFUNC_H__
#define __MYFUNC_H__
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//common
void inputArray(int arr[],int* n);
void printArray(const int* arr,int n);
void print2DArray(int *arr, int rows, int cols);
void removeDuplicates(int* arr, int* n);//无序数组去重

int binarySearch(int* arr,int n,int target);

int is_hex(char c);//是否为16进制character
long hex_to_decimal(const char* hex_str);
//sort
void insertionSort(int* arr,int n);
void selectionSort(int *arr,int n);
void bubbleSort(int arr[], int n) ;

void testEmptyArray(void(*sort)(int*,int));
void testSingleElementArray(void(*sort)(int*,int));
void testSortedArray(void(*sort)(int*,int));
void testReverseArray(void(*sort)(int*,int));
void testArrayWithDuplicates(void(*sort)(int*,int));
void testRandomArray(int n,void(*sort)(int*,int));
int isSorted(int arr[], int n);
void test_sort(void(*sort)(int*,int));

//mystd
double calc_pow(double x,int n);

//string matching
char* search(char* s,char*t);
#endif
