#include "myfunc.h"

int main() {
    //test_sort(bubbleSort);
	int arr[] = {8,6,5,4,3,2,1};
	bubbleSort(arr,sizeof(arr)/sizeof(int));
	printArray(arr,sizeof(arr)/sizeof(int));
	printf("%d\n",binarySearch(arr,sizeof(arr)/sizeof(int),1));
	// double x;
	// int n;
	// scanf("%lf%d",&x,&n);
	// printf("%f\n",calc_pow(x,n));
}

