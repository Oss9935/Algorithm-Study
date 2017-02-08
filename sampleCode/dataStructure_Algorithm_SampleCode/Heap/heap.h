#pragma once 
typedef struct _heap { 
	int * heap;
	int hSize; 
	int count;  /* heap�� ����Ǿ��ִ� �������� �� */
}Heap; 

void initHeap(Heap * , int ); 
void destroyHeap(Heap *); 
int insertUpHeap(Heap * , int ); 
int deleteDownHeap(Heap *, int *); 
void downHeap(Heap *, int); 
void printHeap(const Heap *); 
int isHeapEmpty(Heap *);
int isHeapFull(Heap *);
