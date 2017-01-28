#include "listQueue.h"
#include <stdio.h>
//#include <crtdbg.h>
//--------------------------------------------------------------------------------
//   main()
//--------------------------------------------------------------------------------
int main()
{
	Queue que; /* ť����*/
	int N, M;   /* N : �ο���, M : ���� �� */
	int i, cnt = 1;
	int getData;   /* deueue�� ������ ���� ���� */

	createQueue(&que); /* ť ���� �� �ʱ�ȭ*/

	printf("N(�ο���)�� M(���ݼ�)�� �Է��Ͻÿ� (M<=N) : ");
	scanf("%d %d", &N, &M);

	//�ο���(N)��ŭ�� ���� ����
	for (i = 1; i <= N; i++)
		enqueue(&que, i);

	printf("josephus(%d,%d) ���� ���� ��...\n", N, M);
	while (que.head->next->next != que.tail)	// queue�� ��尡 1���� ������ �ݺ�
	{
		for (i = 1; i < M; i++)	// ������ �� ������ ť�� �ٽ� ���� (M-1ȸ)
		{
			dequeue(&que, &getData);
			enqueue(&que, getData);
		}
		dequeue(&que, &getData);
		printf("%dȸ ���� �� ���� �� �� : %d\n", cnt++, getData);
	}
	dequeue(&que, &getData);
	printf("josephus(%d,%d) ������ ��� : %d\n", N, M, getData);

	destroyQueue(&que);
	//getchar(); getchar();
	//_CrtDumpMemoryLeaks();
	return 0;
}

