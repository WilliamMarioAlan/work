#include "myfunc.h"
#define MAX 11

int main() {
	char str[100];
   	printf("Enter a string (end with Enter): ");
   	scanf("%s",str);
	printf("%ld\n", hex_to_decimal(str));
}

//+-P-xf4+-1!#
//-3905



	//1.
	// int arr1[MAX],arr2[MAX],ans[MAX];
	// int n,m;

	// inputArray(arr1,&n);
	// inputArray(arr2,&m);

	// int flag,k = 0;
	// for (int i = 0;i < n;i++) {
	// 	flag = 1;
	// 	for (int j = 0;j < m;j++) {
	// 		if (arr1[i] == arr2[j]) flag = 0;
	// 	}
	// 	if (flag) ans[k++] = arr1[i];
	// }
	// for (int i = 0;i < m;i++) {
	// 	flag = 1;
	// 	for (int j = 0;j < n;j++) {
	// 		if (arr2[i] == arr1[j]) flag = 0;
	// 	}
	// 	if (flag) ans[k++] = arr2[i];
	// }
	// removeDuplicates(ans,&k);
	// printArray(ans,k);

	//2.
	// int n;
    // printf("Enter n: ");
	// scanf("%d", &n);
	// int matrix[n][n];
    // printf("Enter an array:");
	// for (int i = 0;i < n;i++) {
	// 	for (int j = 0;j < n;j++) {
	// 		scanf("%d", &matrix[i][j]);
	// 	}
	// }
	// printf("%d\n",calculation((int*)matrix,n));
