#include<stdio.h>
#include "heap.h"
void displayTitle(char *message);
#define TRUE 1 
#define FALSE 0 
int main()
{
	int ary[9] = {1,2,3,4,5,6,7,8,9};
	//int ary[20] = {13,3,20,5,11,17,6,7,19,9,15,10,4,12,1,14,16,8,18,2};
	//int ary[20] = {1,2,3,4,4,3,2,1,1,1,2,2,3,3,4,4,4,3,2,1};
	int i;
	int size = sizeof(ary)/sizeof(ary[0]);
	Heap heap;
	int getData; 


	initHeap(&heap, size);
	for(i=0; i<size; ++i)
		if(insertUpHeap(&heap, ary[i]) == FALSE)
			printf(" insert heap 실패!\n");
	
	if(insertUpHeap(&heap, 99) == FALSE)
			printf(" insert heap 실패!\n");

	printHeap(&heap);

	for(i=0; i<size; ++i)
	{
		if(deleteDownHeap(&heap, &getData) == FALSE)
			printf(" delete heap 실패 \n");
		else
			printf("%3d", getData);
	}
	printf("\n");
	if(deleteDownHeap(&heap, &getData) == FALSE)
			printf(" delete heap 실패! \n");

	printf("\n\n");
	destroyHeap(&heap);
	/*-----------------------------------------------------------------------------------
	heap의 성능향상 기법 : downHeap만 실시하고 upHeap을 실시하지 않으므로 속도 빠름
	----------------------------------------------------------------------------------*/
	printf("heap의 성능향상 기법 : upHeap을 실시하지 않으므로 속도 빠름\n");
	
	initHeap(&heap, size);
	for(i=0; i<size; ++i)
		heap.heap[i+1] = ary[i];
	heap.count = size;

	for(i=heap.hSize/2; i>=1; --i)  /* 상향식 힙 생성, 모든 내부 노드에 대해 하향작업 */
		downHeap(&heap, i);

	printHeap(&heap);

	for(i=0; i<size; ++i)
	{
		deleteDownHeap(&heap, &getData);
		printf("%3d", getData);
	}
	printf("\n\n");
	destroyHeap(&heap);
	return 0;
}

void displayTitle(char *message)
{
	printf("\n----------------------------------------\n");
	printf("\t %s\n", message);
	printf("----------------------------------------\n");
}