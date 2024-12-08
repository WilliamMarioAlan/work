#ifndef __MYFUNC_H__
#define __MYFUNC_H__
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
void removeDuplicates(int* arr, int* n);//无序数组去重
int c_filter(int* arr,int n); //有序数组去重 return array length
void insertionSort(int* arr,int n);
void inputArray(int arr[],int* n);
void printArray(const int* arr,int n);
void print2DArray(int *arr, int rows, int cols);

//用one-dimensional-array计算two-dimensional-array计算
//除了副对角线 最后一行最后一列之外所有elements的sum
int calculation(const int* arr,int n);

int is_hex(char c);//是否为16进制character

long hex_to_decimal(const char* hex_str);
#endif
