#include<stdio.h>
#include<malloc.h>
#include "graph.h"
void displayTitle(char *message);
void dijkstra(GraphMatrix *g, int vNum, int *weightArray, int *parent);
void printWeightArray(int *weightArray, int vNum, int vCnt);
void printParent(int *parent, int vCnt);
void pathPrint(int *parent, int * weightArray, int startVNum, int endVNum);
int visitCheck(int *check, int vertexCnt);
int getMinGravity(int *weightArray, int *check, int minIndex, int vertexCnt);

/*----------------------------------------------------------------------------------
�Լ��� : main()
----------------------------------------------------------------------------------*/
int main()
{
	GraphMatrix g;
	int weightArray[MAX_VERTEX];  /* ����ġ�� ���������� �����ϴ� �迭 */
	int parent[MAX_VERTEX];      /* �θ� ���� ���� �迭*/
	int i;

	initGraph(&g, "c:\\data\\graphData2.txt");/* �׷��� �ʱ�ȭ */

	displayTitle("[���� �׷����� ���� ��� ���]");
	outputGraph(&g);   /* �׷��� ���� �� ����ġ ���� ���*/
	NEWL; NEWL;

	/* ���ͽ�Ʈ�� �˰��� ���� */

	displayTitle("[����ġ ��ȭ ���� ���]");
	dijkstra(&g, 5, weightArray, parent);  /* 5���� �ش��ϴ� ������ �������� ���ͽ�Ʈ�� �˰��� ���� */

	displayTitle("[�������� �θ�, �ڽİ��� ���]");
	printParent(parent, g.vertexCnt);  /* parent �迭 ��� */

	/* ���� ����(F-5�� ����)�� ���� �׷������� ��� ����(A~K)������ ��� �� ����ġ ��� */
	displayTitle("[F(5�� ����)�������� �� ���������� path ����ϱ�]");
	for (i = 0; i<g.vertexCnt; ++i)
		pathPrint(parent, weightArray, 5, i);

	return 0;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: displayTitle() - ���޵� �޽����� ��� ��
��������:  message - ����� �޽���
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void displayTitle(char *message)
{
	printf("\n----------------------------------------\n");
	printf(" %s\n", message);
	printf("----------------------------------------\n");
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: dijkstra() - ���޵� �׷������� ���õ� �������� ���� ������ ����������
�ּ� ����ġ�� ����ϰ� �θ��ڽ� ���踦 ������
��������:  g - �׷��� ���� ����ü�� �ּ�
vNum - ���õ� ���� ��ȣ
weightArray - ����ġ�� ������ �迭�� �����ּ�
parent - �������� �θ��ڽİ��踦 ������ �迭�� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void dijkstra(GraphMatrix *g, int vNum, int *weightArray, int *parent)
{
	int check[MAX_VERTEX] = { NON_CHECK, };
	int i, j;
	int minIndex = vNum;	//���� ���� ( �湮 ���� ��� �� �ּ� ��ȸ����ġ�� ���� ����)
	int dist;		//��ȸ ����ġ

	for (i = 0; i < g->vertexCnt; i++)
	{
		weightArray[i] = g->graph[vNum][i];	// ���� ������ ���� ����ġ ����
		parent[i] = vNum;
	}
	
	parent[vNum] = -1;
	check[vNum] = CHECK;	// ������ �� ���� �湮 �Ϸ� ���·� ����

	// ����ġ �迭 ���
	printWeightArray(weightArray, minIndex, g->vertexCnt);
	while (!visitCheck(check, g->vertexCnt))
	{

		// ���� ���� ���� ���
		minIndex = getMinGravity(weightArray, check, minIndex, g->vertexCnt);
		check[minIndex] = CHECK;

		// ���� ������ ���� ��� ������ ���� ����ġ ���
		for (i = 0; i < g->vertexCnt; i++)
		{
			dist = weightArray[minIndex] + g->graph[minIndex][i];
			if (dist < weightArray[i])
			{
				weightArray[i] = dist;
				parent[i] = minIndex;
			}
		}
		// ����ġ �迭 ���
		printWeightArray(weightArray, minIndex, g->vertexCnt);
	}	
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: printWeightArray() - weight�迭�� ��� ��
��������:  weightArray - ����ġ ���� �迭�� �����ּ�
vNum - ���� ���� ��ȣ
vCnt - ����� ������ ����
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void printWeightArray(int *weightArray, int vNum, int vCnt)
{
	int i;
	printf("%3c : ", 'A' + vNum);
	for (i = 0; i<vCnt; ++i)
		printf("%5d", weightArray[i]);

	NEWL;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: printParent() - �θ�, �ڽ� ��带 ǥ���ϴ� �迭 ���
��������:  parent - �θ�, �ڽ� ��� ǥ�� �迭�� �����ּ�
vCnt - ����� ������ ����
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void printParent(int *parent, int vCnt)
{
	int i;
	printf("\n---------------------------------------------------------\n");
	printf("child :  ");
	for (i = 0; i<vCnt; ++i)
		printf("%3c", i + 'A');
	NEWL;
	printf("Parent : ");
	for (i = 0; i<vCnt; ++i)
		if (parent[i] == -1) printf("  *");
		else printf("%3c", parent[i] + 'A');
	printf("\n--------------------------------------------------------\n");
	NEWL;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: pathPrint() - ���� ����->�� ���������� path �� ����ġ ���
��������:  parent - �θ�, �ڽİ��踦 ������ �迭�� �����ּ�
weightArray - ����ġ ���� �迭�� �����ּ�
startVNum - ���� ���� ��ȣ
endVNum - ���� ���� ��ȣ
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void pathPrint(int *parent, int * weightArray, int startVNum, int endVNum)
{
	int ary[MAX_VERTEX] = { 0, };
	int i = 0;

	int cur = endVNum;
	while (cur != -1)
	{
		ary[i++] = cur;
		cur = parent[cur];
	}
	
	i--;
	for (; i >= 0; i--)
	{
		printf("%c ", ary[i] + 'A');
		if (i)
			printf("->");
	}


	printf("(weight : %d)\n", weightArray[endVNum]);
}

int visitCheck(int *check, int vertexCnt)
{
	for (int i = 0; i < vertexCnt; i++)
	{
		if (check[i] == NON_CHECK)
			return FALSE;
	}
	return TRUE;
}

int getMinGravity(int *weightArray, int *check, int minIndex, int vertexCnt)
{
	int i;
	int min;

	for (i = 0; i < vertexCnt; i++)
		if (check[i] == NON_CHECK)
			break;
	min = i;
	
	for (i = vertexCnt - 1; i >= 0; i--)
		if (check[i] == NON_CHECK && weightArray[i] <= weightArray[min])
			min = i;

	return min;
}
/*======================================================================================================
[ ��� ��� ]
----------------------------------------
[���� �׷����� ���� ��� ���]
----------------------------------------
A  B  C  D  E  F  G  H  I  J  K
A  0  4  1  2  3 �� �� �� �� �� ��
B  4  0 �� �� ��  4 �� �� �� �� ��
C  1 ��  0  2 �� �� �� �� �� �� ��
D  2 ��  2  0 ��  4  4 �� �� �� ��
E  3 �� �� ��  0  4 �� �� �� �� ��
F ��  4 ��  4  4  0 �� �� ��  2  4
G �� �� ��  4 �� ��  0  3  3  4 ��
H �� �� �� �� �� ��  3  0  2 �� ��
I �� �� �� �� �� ��  3  2  0  2 ��
J �� �� �� �� ��  2  4 ��  2  0  1
K �� �� �� �� ��  4 �� �� ��  1  0

�� : 1000������ ����

----------------------------------------
[����ġ ��ȭ ���� ���]
----------------------------------------
F :  1000    4 1000    4    4    0 1000 1000 1000    2    4
J :  1000    4 1000    4    4    0    6 1000    4    2    3
K :  1000    4 1000    4    4    0    6 1000    4    2    3
B :     8    4 1000    4    4    0    6 1000    4    2    3
D :     6    4    6    4    4    0    6 1000    4    2    3
E :     6    4    6    4    4    0    6 1000    4    2    3
I :     6    4    6    4    4    0    6    6    4    2    3
A :     6    4    6    4    4    0    6    6    4    2    3
C :     6    4    6    4    4    0    6    6    4    2    3
G :     6    4    6    4    4    0    6    6    4    2    3
H :     6    4    6    4    4    0    6    6    4    2    3

----------------------------------------
[�������� �θ�, �ڽİ��� ���]
----------------------------------------
child :    A  B  C  D  E  F  G  H  I  J  K
Parent :   D  F  D  F  F  *  J  I  J  F  J

----------------------------------------
[F���� �� ���������� path ���]
----------------------------------------
F ->   D ->   A  (weight: 6)
F ->   B  (weight: 4)
F ->   D ->   C  (weight: 6)
F ->   D  (weight: 4)
F ->   E  (weight: 4)
F  (weight: 0)
F ->   J ->   G  (weight: 6)
F ->   J ->   I ->   H  (weight: 6)
F ->   J ->   I  (weight: 4)
F ->   J  (weight: 2)
F ->   J ->   K  (weight: 3)

*/