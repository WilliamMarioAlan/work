#include <stdio.h>
#define MAX 11
void removeDuplicates(int* arr, int* n);//无序数组去重
int c_filter(int* arr,int n); //有序数组去重 return array length
void insertionSort(int* arr,int n);
void inputArray(int arr[],int* n);
void printArray(const int* arr,int n);
int main() {
	int arr1[MAX],arr2[MAX],ans[MAX];
	int n,m;

	inputArray(arr1,&n);
	inputArray(arr2,&m);

	int flag,k = 0;
	for (int i = 0;i < n;i++) {
		flag = 1;
		for (int j = 0;j < m;j++) {
			if (arr1[i] == arr2[j]) flag = 0;
		}
		if (flag) ans[k++] = arr1[i];
	}
	for (int i = 0;i < m;i++) {
		flag = 1;
		for (int j = 0;j < n;j++) {
			if (arr2[i] == arr1[j]) flag = 0;
		}
		if (flag) ans[k++] = arr2[i];
	}
	removeDuplicates(ans,&k);
	printArray(ans,k);
}

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