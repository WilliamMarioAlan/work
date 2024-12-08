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


int c_filter(int* arr,int n) { //return array length
	int i = 0;
	for (int j = 0;j < n;++j) 
		if (arr[i] != arr[j]) 
			arr[++i] = arr[j];
	return i + 1;
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
	return (c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f')?1:0;
}

int calculation(const int* arr,int n) {
	if (n <= 2) return 0;
	int a = 0,b = 0;
	for (int r = 0;r < n;r++) {
		for (int c = 0;c < n;c++) {
			a += *(arr + (r * n) + c);
		}
	}
	int c = n - 1;
	for (int r = 0;r < n;r++) {
			b += *(arr + (r * n) + c);
			c--;
	}
	for (int c = 0;c < n;c++) b += *(arr + ((n - 1) * n) + c);
	for (int r = 0;r < n;r++) b += *(arr + (r * n) + n - 1);
	return a - b + *(arr + (n - 1) * n) + *(arr + n - 1) + *(arr + ((n - 1) * n) + n - 1);
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

