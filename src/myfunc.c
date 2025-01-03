#include "myfunc.h"
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // 当前需要插入的元素
        int j = i - 1;

        // 将大于 key 的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // 将 key 插入到正确的位置
        arr[j + 1] = key;
    }
}
void selectionSort(int *arr,int n) {
	for (int i = 0;i < n;i++) {
		int min = i;
		for (int j = i + 1;j < n;j++) {
			if (arr[j] < arr[min]) 
				min = j;
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(const int* arr,int n) {
	printf("Array:");
	for (int i = 0;i < n;i++) printf("%d ",arr[i]);
	putchar('\n');
}
void removeDuplicates(int* arr, int* n) {
    int i, j, k = 0;
    for (i = 0; i < *n; i++) {
        int flag = 0;
        for (j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            arr[k++] = arr[i];
        }
    }
    *n = k;
}
void inputArray(int arr[],int* n) {
	printf("Enter n:");
	scanf("%d",n);
	printf("Enter %d elements:",*n);
	for (int i = 0;i < *n;i++) scanf("%d",&arr[i]);
}


void print2DArray(int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(arr + i * cols + j)); // 使用指针访问元素
        }
        printf("\n");
    }
}

int is_hex(char c) {
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))?1:0;
}

long hex_to_decimal(const char* hex_str) {
    long result = 0;
    int len = strlen(hex_str);
    int flag = 1;
    for (int i = 0; i < len - 1; i++) {
        char c = hex_str[i];
        // 将字符转换为数字
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';  // 数字 0-9
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;  // 字母 A-F
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;  // 字母 a-f
        } else if (hex_str[i] == '+' || hex_str[i] == '-'){
			if (is_hex(hex_str[i + 1])) {
				flag = hex_str[i] == '+' ?1:-1;
			}
			continue;
        }else {
			continue;
		}     
        // 将当前位的值加入到结果
        result = result * 16 + digit;
    }
    return result * flag;
}

int isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return 0;  // 返回0表示数组没有正确排序
        }
    }
    return 1;  // 返回1表示数组已正确排序
}
// 测试空数组
void testEmptyArray(void(*sort)(int*,int)) {
    int arr[] = {};
    int n = 0;
    printf("Test Empty Array:\n");
    sort(arr, n);
    printArray(arr, n);
    printf(isSorted(arr, n) ? "Pass\n" : "Fail\n");
}
// 测试单元素数组
void testSingleElementArray(void(*sort)(int*,int)) {
    int arr[] = {42};
    int n = 1;
    printf("Test Single Element Array:\n");
    sort(arr, n);
    printArray(arr, n);
    printf(isSorted(arr, n) ? "Pass\n" : "Fail\n");
}

// 测试已排序数组
void testSortedArray(void(*sort)(int*,int)) {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    printf("Test Sorted Array:\n");
    sort(arr, n);
    printArray(arr, n);
    printf(isSorted(arr, n) ? "Pass\n" : "Fail\n");
}

// 测试逆序数组
void testReverseArray(void(*sort)(int*,int)) {
    int arr[] = {5, 4, 3, 2, 1};
    int n = 5;
    printf("Test Reverse Array:\n");
    sort(arr, n);
    printArray(arr, n);
    printf(isSorted(arr, n) ? "Pass\n" : "Fail\n");
}

// 测试重复元素数组
void testArrayWithDuplicates(void(*sort)(int*,int)) {
    int arr[] = {3, 1, 2, 3, 2};
    int n = 5;
    printf("Test Array With Duplicates:\n");
    sort(arr, n);
    printArray(arr, n);
    printf(isSorted(arr, n) ? "Pass\n" : "Fail\n");
}

// 测试随机数组
void testRandomArray(int n,void(*sort)(int*,int)) {
    int arr[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Test Random Array:\n");
    printArray(arr, n);
    sort(arr, n);
    printArray(arr, n);
    printf(isSorted(arr, n) ? "Pass\n" : "Fail\n");
}

void test_sort(void(*sort)(int*,int)) {
	// 测试各种情况
    testEmptyArray(sort);
    testSingleElementArray(sort);
    testSortedArray(sort);
    testReverseArray(sort);
    testArrayWithDuplicates(sort);
    testRandomArray(20,sort);  // 测试一个长度为 10 的随机数组
}

double calc_pow(double x,int n) {
	if (n == 0) return 1;
	return x * calc_pow(x,--n);
}
char* search(char* s,char*t) {
	for (int i = 0;s[i] != '\0';i++) {
		int j = 0;
		while (s[i] == t[j] && s[i] != '\0' && t[j] != '\0') {
			i++;
			j++;
		}
		if (t[j] == '\0') return s + i - j;
		i -= j;
	}
	return NULL;
}

int binarySearch(int* arr,int n,int target) {
	int l = 0,r = n - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (arr[m] == target) return m;
		else if (arr[m] > target) r = m - 1;
		else l = m + 1;
	}
	return -1;
}