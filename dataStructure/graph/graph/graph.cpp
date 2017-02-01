#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <malloc.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

int check[MAX_VERTEX];  /* 방문된 정점은 1로 미방문 정점은 0으로 저장 */
/*--------------------------------------------------------------------------------------
함수명 및 기능: initGraph() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
그래프를 인접 행렬법으로 초기화하는 함수
전달인자:  gm - 그래프 정보 구조체의 주소
fileName - 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
리턴값: 없음
 --------------------------------------------------------------------------------------*/
void initGraph(GraphMatrix *gm, char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
	int i, j, k;       /* iterator */
	FILE *fp;        /* 그래프 정보 저장 파일의 파일포인터 */

	fp = fopen(fileName, "rt");
	assert(fp != NULL);
	fscanf(fp, "%d %d\n", &gm->vertexCnt, &gm->edgeCnt);  /* 정점과 간선의 개수를 읽기 */

	// 그래프 0으로 초기화
	for (i = 0; i < gm->vertexCnt; i++)
		for (j = 0; j < gm->vertexCnt; j++)
			gm->graph[i][j] = 0;
	
	while (fscanf(fp, " %s ", vertex) != EOF )
	{
		gm->graph[vertex[0] - 'A'][vertex[1] - 'A']++;
		gm->graph[vertex[1] - 'A'][vertex[0] - 'A']++;
	}
	
	fclose(fp);
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: outputGraph() - 그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void outputGraph(GraphMatrix *gm)
{
	int i, j;         /* iterator */

	/* 정점명 가로방향 출력 */
	printf("   ");
	for (i = 0; i < gm->vertexCnt; ++i)
		printf("%3c", 'A' + i);

	NEWL;  // 개행 매크로 

	for (i = 0; i<gm->vertexCnt; ++i)
	{
		printf("%3c", 'A' + i);
		for (j = 0; j < gm->vertexCnt; j++)
			printf("%3d", gm->graph[i][j]);
		NEWL;
	}
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: DFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색
하기 위한 함수(재귀판)
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void DFS_Matrix(GraphMatrix *gm)
{
	int i;

	// 정점의 방문상태 정보를 저장할 check배열 초기화 
	for (i = 0; i < gm->vertexCnt; ++i)  
		check[i] = 0;

	// 그래프의 하나의 노드를 기준으로 연결된 모든 노드 방문 반복
	for (i = 0; i < gm->vertexCnt; ++i)
		if (check[i] == 0)
			DFS_recursive(gm, i);
	return;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: DFS_recursive() - 연결되어있는 하나의 그래프 내의 모든 정점을
재귀호출기법으로 방문하는 함수
전달인자:  gm : 그래프 정보 구조체의 주소
vNum : 방문하고자 하는 정점 번호
리턴값: 없음
--------------------------------------------------------------------------------------*/
void DFS_recursive(GraphMatrix *gm, int vNum)
{
	int i;
	visit(vNum);
	check[vNum] = VISIT;
	for(i = 0; i< gm->vertexCnt; i++)
		if (check[i] == NON_VISIT && gm->graph[vNum][i] == 1)
			DFS_recursive(gm, i);
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: visit() - 방문된 정점을 처리하는 함수(이 함수에서는 방문된 정점을 출력 함)
전달인자: vNum : 방문하고자 하는 정점 번호
리턴값: 없음
--------------------------------------------------------------------------------------*/
void visit(int vNum)
{
	printf("%3c", 'A' + vNum);
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: nrDFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색
하기 위한 함수(비 재귀판)
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void nrDFS_Matrix(GraphMatrix *gm)
{
	Stack stk;	/* 특정 노드부터 DFS를 이용해 탐색을 할 때 한 노드에 대한 
				여러 인접 노드 중 임의의 한 노드에 대해 먼저 탐색하기 위해
				나머지 노드들을 스택에 push하고 처리중인 노드의 탐색이 끝나면
				방문하기 위해 탐색중에 나중에 방문해야 할 노드를 임의로 담아 둘
				자료구조 필요. DFS는 한 노드에서 탐색할 수 있는 모든 노드를 탐색한 후
				나머지 노드들에 대해 탐색하기 때문에 향후 방문할 노드 정보를
				역순으로 저장할 자료구조가 필요하기 때문에 stack자료구조 사용.
				*/
	int i, j = 0;
	DataType curNode;	// 현재 방문중인 노드(stack에서 pop한 값)

	initStack(&stk);

	// 방문 상태 확인 전역변수 비방문 상태로 초기화
	for (i = 0; i < gm->vertexCnt; i++)
		check[i] = NON_VISIT;
	
	// 그래프의 노드 중 특정 노드기준으로 모든 노드 탐색 완료 시까지 반복
	for (i = 0; i < gm->vertexCnt; i++)
	{
		// 이미 탐색하지 않은 노드의 경우만 탐색 수행
		if (check[i] == NON_VISIT)
		{
			// 현재 노드 스택에 push 후 해당 노드 탐색 완료 상태로 변경
			push(&stk, i);	
			check[i] = VISIT;
			
			// 스택에 탐색할 노드가 없을 때 까지 반복 수행.
			while (!isStackEmpty(&stk))
			{
				// 현재 노드를 pop 하고 방문 처리
				pop(&stk, &curNode);
				visit(curNode);

				// pop한 노드의 인접노드(연결요소) 스택에 push.
				// 단, 방문하지 않는 노드만 push
				for (j = 0; j < gm->vertexCnt; j++)
					if (gm->graph[curNode][j] != 0 && check[j] == NON_VISIT)
					{
						// 스택에 들어간 적 없는 정점(방문X)이라면 스택에 push
						push(&stk, j);
						check[j] = VISIT;
					}
			}
		}
	}
	NEWL;
	destroyStack(&stk);

	return;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: nrBFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 너비 우선 탐색
하기 위한 함수(비 재귀판)
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void BFS_Matrix(GraphMatrix *gm)
{
	Queue que;
	int i, j;
	DataType curNode;	// 현재 방문중인 노드(queue에서 dequeue 한 값)

	initQueue(&que, MAX_VERTEX);

	// 방문 상태 확인 전역변수를 비방문 상태로 초기화
	for (i = 0; i < gm->vertexCnt; i++)
		check[i] = NON_VISIT;

	// 그래프의 특정 노드를 기준노드로 탐색 반복하여 모든 노드 탐색 완료시 까지 반복
	for (i = 0; i < gm->vertexCnt; i++)
	{
		// 이미 탐색하지 않은 경우만 탐색 수행
		if (check[i] == VISIT)
			continue;

		/*	이전까지 탐색되지 않는 기준 노드 탐색 처리 과정	*/
		// 현재 노드를 enqueue하고 방문 처리
		enqueue(&que, i);
		check[i] = VISIT;

		while (!isQueueEmpty(&que))
		{
			// 현재 노드를 dequeue 하고 방문 처리
			dequeue(&que, &curNode);
			visit(curNode);

			// 현재 노드와 인접해있는 노드들을 enqueue.
			// 단, 방문하지 않는 노드만
			for(j=0; j < gm->vertexCnt; j++)
				if (check[j] == NON_VISIT && gm->graph[curNode][j] != 0)
				{
					enqueue(&que, j);
					check[j] = VISIT;
				}
		}
	}
	NEWL;
	destroyQueue(&que);

	return;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: countGraphComponents() - 인접 행렬법으로 표기되 그래프 내의 연결 요소별로
정점들을 출력하고 연결 요소의 개수 리턴
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 그래프내의 연결 요소의 개수
--------------------------------------------------------------------------------------*/
int countGraphComponents(GraphMatrix *gm)
{
	int componetsCount = 0;  /* 그래프 내의 연결 요소 카운트 변수 */
	int i;

	// 정점의 방문상태 정보를 저장할 check배열 초기화 
	for (i = 0; i < gm->vertexCnt; ++i)
		check[i] = 0;

	// 그래프의 하나의 노드를 기준으로 연결된 모든 노드 방문 반복
	for (i = 0; i < gm->vertexCnt; ++i)
		if (check[i] == 0)
		{
			printf("연결 요소 %d : ", ++componetsCount);
			DFS_recursive(gm, i);
			NEWL;
		}

	return componetsCount;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: initGraph_L() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
그래프를 인접 리스트법으로 초기화하는 함수
전달인자:  g : 그래프 정보 구조체의 주소
fileName : 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
리턴값: 없음
--------------------------------------------------------------------------------------*/
void initGraph_List(GraphList *g, char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
	int i, j, k;       /* iterator */
	FILE *fp;        /* 그래프 정보 저장 파일의 파일포인터 */

	fp = fopen(fileName, "rt");
	assert(fp != NULL);
	fscanf(fp, "%d %d\n", &g->vertexCnt, &g->edgeCnt);  /* 정점과 간선의 개수를 읽기 */

	for (i = 0; i < MAX_VERTEX; i++)
		g->graph[i] = NULL;

	while (fscanf(fp, "%s", vertex) != EOF)
	{
		addNode(g, vertex[0] - 'A', vertex[1] - 'A');
		addNode(g, vertex[1] - 'A', vertex[0] - 'A');
	}
	

	fclose(fp);
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: addNode() - 두 정점의 관계를 리스트에 등록함
전달인자:  g - 그래프 정보 구조체의 주소
vNum1 - 첫번째 정점의 번호
vNum2 - 두번째 정점이 번호
리턴값: 정점 등록이 성공하면 TRUE 리턴, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int addNode(GraphList *g, int vNum1, int vNum2)
{
	int i;
	Node *insertNode = (Node *)malloc(sizeof(Node));
	if (insertNode == NULL)
		return FALSE;

	insertNode->next = g->graph[vNum1];
	insertNode->vertex = vNum2;
	g->graph[vNum1] = insertNode;

	return TRUE;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: outputGraph_L() - 그래프내의 정점과 간선의 관계를 인접 리스트 형태로 출력
전달인자:  g : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void outputGraph_List(GraphList *g)
{
	int linkCnt = 0;	//그래프의 연결 요소 갯수 저장
	Node *cur;

	for (int i = 0; i < g->vertexCnt; i++)
	{
		printf("%c : ", i + 'A');
		cur = g->graph[i];
		while (cur != NULL)
		{
			printf("  %c ", cur->vertex + 'A');
			cur = cur->next;
			if (cur != NULL)
				printf("->");
		}
		NEWL;
	}

}
/*--------------------------------------------------------------------------------------
함수명 및 기능: destroyGraph_L() - 그래프내의 정점 노드 모두 삭제
전달인자:  g : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void destroyGraph_List(GraphList *g)
{
	Node *deleteNode, *cur;
	for (int i = 0; i < g->vertexCnt; i++)
	{
		cur = g->graph[i];
		while (cur != NULL)
		{
			deleteNode = cur;
			cur = cur->next;
			free(deleteNode);
		}
	}

	for (int i = 0; i < MAX_VERTEX; i++)
		g->graph[i] = NULL;
}