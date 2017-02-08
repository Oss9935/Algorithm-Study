#include <stdio.h> 
#include <malloc.h> 
#include <assert.h> 
#include <limits.h>

#include "heap.h" 

#define TRUE 1 
#define FALSE 0 

/*--------------------------------------------------------------------------------------
함수명및기능 : initHeap() - 힙 생성 함수
전달인자 : hPtr - 힙 구조체의 주소
size - 힙의 크기(저장가능한 데이터의 개수)
리턴값 : 없음
--------------------------------------------------------------------------------------*/
void initHeap(Heap *hPtr , int size)
{ 
	hPtr->hSize = size; 
	hPtr->heap = (int *)calloc(hPtr->hSize+1, sizeof(int)); /* 실제 힙의 크기보다 1 크게 할당함 0방은 보초값을 저장 함 */
	hPtr->count = 0;
	hPtr->heap[0] = INT_MAX;  /* 힙의 0번 방은 보초값 저장함 */
} 
/*--------------------------------------------------------------------------------------
함수명및기능 : destroyHeap() - 힙 소멸 함수
전달인자 : hPtr - 힙 구조체의 주소
리턴값 : 없음
--------------------------------------------------------------------------------------*/
void destroyHeap(Heap *hPtr) 
{ 
	if(hPtr->heap != NULL)
		free(hPtr->heap); 
	hPtr->heap = NULL; 
	hPtr->hSize = 0; 
	hPtr->count = 0;
}
/*--------------------------------------------------------------------------------------
함수명및기능 : insertUpHeap() - 힙에 데이터 하나를 저장함
전달인자 : hPtr - 힙 구조체의 주소
inData - 힙에 저장할 데이터
리턴값 : 성공적으로 저장하면 TRUE(1)리턴, 실패하면 FALSE(0) 리턴
--------------------------------------------------------------------------------------*/
int insertUpHeap(Heap *hPtr, int inData) 
{ 
	int position;   /* insert된 데이터가 저장될 위치 */
	if( isHeapFull(hPtr) ) /* 힙이 꽉 차있으면 추가 불가 */ 
	{ 
		return FALSE; 
	} 
	hPtr->heap[++hPtr->count] = inData; /* 힙에 데이터수를 증가하고 데이터 추가 */

	/* 새로 추가된 데이터를 힙의 조건에 맞게 상승(Up)시킨다 */
	position = hPtr->count;

	while(hPtr->heap[position/2] < inData)  /* 새로 입력되는 값이 부모값 보다 크면 UPHEAP 실시 */
	{
		hPtr->heap[position] = hPtr->heap[position/2]; /* 부모값을 자식 위치로 내림 */
		position /= 2;  /* 부모 위치로 들어가기 위해 위치 조정 */
	}
	hPtr->heap[position] = inData; /* 조정된 위치에 입력 데이터 저장 */

	return TRUE; 
} 
/*--------------------------------------------------------------------------------------
함수명및기능 : deleteDownHeap() - 힙에 데이터 하나를 삭제
전달인자 : hPtr - 힙 구조체의 주소
getData - 힙에 꺼낸 데이터 저장변수의 주소
리턴값 : 성공적으로 삭제하면 TRUE(1)리턴, 실패하면 FALSE(0) 리턴
--------------------------------------------------------------------------------------*/
int deleteDownHeap(Heap * hPtr, int * getData) 
{
	if( isHeapEmpty(hPtr) ) // 힙이 비어있으면 삭제 불가 
	{ 
		return FALSE; 
	} 
	*getData = hPtr->heap[1];  /* 1번 방의 값이 가장 큰값(0번 방은 보초값으로 실제 데이터 아님) */
	hPtr->heap[1] = hPtr->heap[hPtr->count];  /* 힙의 말단 노드를 root 위치로 올림 */
    hPtr->heap[hPtr->count] = INT_MIN;
	--hPtr->count;  /* 데이터의 개수 하나 감소 */

	downHeap(hPtr, 1);

	return TRUE; 
} 
/*--------------------------------------------------------------------------------------
함수명및기능 : downHeap() - 힙에 데이터 하나를 삭제
전달인자 : hPtr - 힙 구조체의 주소
           position - 하향 시킬 데이터의 위치
리턴값 : 성공적으로 삭제하면 TRUE(1)리턴, 실패하면 FALSE(0) 리턴
--------------------------------------------------------------------------------------*/
void downHeap(Heap *hPtr, int position)
{
	int childPosition;  /* 자식의 저장 위치 */
	int downData;       /* 하강할 데이터값 저장 변수 */

	downData = hPtr->heap[position];
	
	while(position <= hPtr->count / 2) /* parentPosition이 내부 노드이면 down 시킴 */ /* !!비교시 = 빠지면... 소트되다 맘 */
	{
		childPosition = position << 1;  /* parentPosition *= 2와 같은 연산으로 왼쪽 자식 위치 구함 */
		if(hPtr->heap[childPosition] < hPtr->heap[childPosition+1]) /* 오른쪽 자식의 값이 더 크면 */
		{
			++childPosition;  /* 오른쪽 자식의 위치 선택 */
		}
		if(downData >= hPtr->heap[childPosition])  /* 더 이상 하강할 필요가 없으면 탈출 */
			break;
		hPtr->heap[position] = hPtr->heap[childPosition];  /* 선택된 자식의 값을 position위치에 저장하고 */
		position = childPosition;  /* 자식값의 위치로 position위치를 수정한다. */
	}
	hPtr->heap[position] = downData; /* 정해진 하강 위치에 하강데이터 저장 */
}
/*--------------------------------------------------------------------------------------
함수명및기능 : printHeape() - 힙 내의 데이터 출력 (상위->하위 방항)
전달인자 : hPtr - 힙 구조체의 주소
리턴값 : 없음
--------------------------------------------------------------------------------------*/
void printHeap(const Heap * hPtr) 
{ 
	int i;
	for(i=1; i <= hPtr->count; ++i) 
	{ 
		printf("%3d", hPtr->heap[i]); 
	}
	printf("\n");
} 
/*--------------------------------------------------------------------------------------
함수명 및 기능: isHeapEmpty() - 힙이 비어있는가 검사
전달인자: hPtr - 힙 구조체의 주소
리턴값: 비어있으면 1 리턴, 비어있지 않으면 0 리턴
--------------------------------------------------------------------------------------*/
int isHeapEmpty(Heap *hPtr)
{
	if(hPtr->count == 0) 
		return 1;
	else 
		return 0;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: isHeapFull() - 힙이 꽉차 있는가 검사
전달인자: hPtr - 힙 구조체의 주소
리턴값: 꽉 차 있으면 1 리턴, 꽉 차있지 않으면 0 리턴
--------------------------------------------------------------------------------------*/
int isHeapFull(Heap *hPtr)
{
	if(hPtr->count == hPtr->hSize)
		return 1;
	else 
		return 0;
}