#ifndef _FUNC_HPP_
#define _FUNC_HPP_
//c++
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#define _USE_MATH_DEFINES
/*
_USE_MATH_DEFINES 是 Microsoft 标准库中引入的一个预处理器宏。
当定义了 _USE_MATH_DEFINES 后，<cmath> 或 <math.h> 中会额外启用一组数学常数的定义。
e.g.
M_PI	3.141592653589793	 圆周率 𝜋
M_E		2.718281828459045	自然对数的底数 ��
M_SQRT2	1.414213562373095	根号2
*/
#include <cmath>
#include <algorithm>
#include <climits>
#include <complex>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>


/*
C++ 会对函数名进行“名字修饰”，即编译器会改变函数的名称以支持函数重载和其他 C++ 特性。
例如，C++ 会将函数名加上一些额外的信息（如参数类型）来支持函数重载。
C 语言不会做名字修饰，函数名保持原样。因此，如果你在 C++ 中调用 C 函数，必须显式地告诉编译器不要进行名字修饰。这就是 extern "C" 的作用。
extern "C" 的作用：
如果 C++ 代码需要调用 C 代码，或者你在 C++ 中需要链接 C 库，使用 extern "C" 来确保 C++ 编译器不对函数名进行名字修饰，从而保证 C 和 C++ 代码可以互相链接。
extern "C" 告诉编译器这个函数遵循 C 语言的链接约定，而不是 C++ 的链接约定。
*/
#ifdef __cplusplus
extern "C" {
#endif

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

int factorial(int n) ;//阶乘
int gcd(int a,int b);//最大公约数
int lcm(int a,int b);//最小公倍数
int isNarcissistic(int num);//水仙花数
int is_prime(int n);//素数

#ifdef __cplusplus
}
#endif



#endif
