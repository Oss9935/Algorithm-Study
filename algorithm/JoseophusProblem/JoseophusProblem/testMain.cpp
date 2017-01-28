#include "listQueue.h"
#include <stdio.h>
//#include <crtdbg.h>
//--------------------------------------------------------------------------------
//   main()
//--------------------------------------------------------------------------------
int main()
{
	Queue que; /* 큐생성*/
	int N, M;   /* N : 인원수, M : 간격 수 */
	int i, cnt = 1;
	int getData;   /* deueue한 데이터 저장 변수 */

	createQueue(&que); /* 큐 생성 및 초기화*/

	printf("N(인원수)와 M(간격수)를 입력하시오 (M<=N) : ");
	scanf("%d %d", &N, &M);

	//인원수(N)만큼의 순열 생성
	for (i = 1; i <= N; i++)
		enqueue(&que, i);

	printf("josephus(%d,%d) 순열 제거 중...\n", N, M);
	while (que.head->next->next != que.tail)	// queue에 노드가 1개일 때까지 반복
	{
		for (i = 1; i < M; i++)	// 제외할 수 전까지 큐에 다시 삽입 (M-1회)
		{
			dequeue(&que, &getData);
			enqueue(&que, getData);
		}
		dequeue(&que, &getData);
		printf("%d회 수행 시 제거 된 수 : %d\n", cnt++, getData);
	}
	dequeue(&que, &getData);
	printf("josephus(%d,%d) 순열의 결과 : %d\n", N, M, getData);

	destroyQueue(&que);
	//getchar(); getchar();
	//_CrtDumpMemoryLeaks();
	return 0;
}

