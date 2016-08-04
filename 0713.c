#include <stdio.h>
#include "sort.h"


void swap(int *a,int *b){
	int t = *a;
	*a = *b;
	*b = t;
}
int larger(int a, int b){
	return a > b;

}
int smaller(int a, int b){
	return a < b;
}
void sort(int* arr, int length, int (*compare)(int, int)){
	int flag = 1;
	int i, j;
	for(i = 0; i < length-1 && flag == 1; i++){
	flag = 0;
	for(j = 0; j < length-i-1; j++){
	if(compare(arr[j+1], arr[j])){
	swap(arr + j + 1, arr + j);
	flag = 1;
}
} 
}

}

int main(void){
	int number1[] ={31, 25, 42, 33, 75};
	sort(number1, 5, larger);
	printf("larger to smaller ");
	int i;
	for(i = 0; i < 5; i++){
	printf("%d ", number1[i]);
}
	putchar('\n');
	
	int number2[] = {31, 25, 42, 33, 75};
	sort(number2, 5, smaller);
	printf("smaller to larger");
	for(i = 0; i < 5; i++){

	printf("%d ", number2[i]);
}
	putchar('\n');
	return 0;
}
