#include "listQueue.h" 
#include <stdio.h> 
//--------------------------------------------------------------------------------
//   main() 
//--------------------------------------------------------------------------------
int main() 
{ 
	Queue que; /* 큐생성*/ 
	int N, M;   /* N : 인원수, M : 간격 수 */
	int i;
	DataType getData;  /* deueue한 데이터 저장 변수 */

	initQueue(&que); /* 큐 생성 및 초기화*/ 

	printf("N(인원수)와 M(간격수)를 입력하시오 (M<=N) : ");
	scanf("%d %d", &N, &M);

	for(i=1; i<=N; ++i)  /* queue에 1~N까지의 순번을 저장 */
		enqueue(&que, i);

	printf("(%d,%d) 조세퍼스의 순열 : ", N, M);
	while(!isQueueEmpty(&que)){
		for(i=1; i<M; ++i){
			if(dequeue(&que, &getData) == TRUE)
				enqueue(&que, getData);
		}
		if(dequeue(&que, &getData)==TRUE)
			printf("%4d", getData);
	}
	printf("\n\n");
	destroyQueue(&que); 
	return 0; 
} 

//-------------------------------------
//   int type 보조 함수
//-------------------------------------
/*--------------------------------------------------------------------------------------
  함수명 및 기능: printInt() - 전달인자로 넘겨진 int값을 정해진 format으로 출력 함
  전달인자: p - 출력할 정수의 주소
  리턴값: 없음
  --------------------------------------------------------------------------------------*/
void printInt(DataType *p)
{
	printf("%4d", *p);
}