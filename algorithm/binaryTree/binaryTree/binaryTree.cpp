#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

/* -------------------------------------------------------------------------------------
함수명 : initTree - 트리 관리 구조체를 초기화 하는 함수
전달인자 : tr - Tree 구조체의 주소
리턴 값 : 없음
--------------------------------------------------------------------------------------*/
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}
/* --------------------------------------------------------------------------------------
함수명 : makeNode - 새 노드를 만들어 새 노드의 주소를 리턴하는 함수
전달인자 : data - 새 노드에 저장될 값(데이터)
left - 새 노드의 left 멤버 값
right - 새 노드의 right 멤버 값
리턴 값 : 새 노드의 주소 / 메모리 할당 실패 시 NULL pointer
---------------------------------------------------------------------------------------*/
Node * makeNode(DataType *data, Node *left, Node *right)
{
	Node *np;
	np = (Node *)malloc(sizeof(Node));
	assert(np != NULL);
	if (np != NULL) {
		np->data = *data;
		np->left = left;
		np->right = right;
	}
	return np;
}

/* --------------------------------------------------------------------------------------
함수명 : addNode - 노드를 삽입하는 함수
전달인자 : tr - Tree 구조체의 주소
data - 새 노드에 저장될 데이터 저장 공간의 주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴 값 : 새 노드의 주소 / 메모리 할당 실패 시 NULL pointer
---------------------------------------------------------------------------------------*/
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node *newNode, *tp, *pp;
	newNode = makeNode(data, NULL, NULL);

	// root 노드에 add node
	if (tr->root == NULL)
	{
		tr->root = newNode;
	}
	else {
		// root 이외의 노드에 add node
		tp = tr->root;
		while (tp != NULL)
		{
			pp = tp;	// 현재 노드 위치 저장하고(pp), tp를 이용한 탐색
			if (compare(&tp->data, &newNode->data)>0)	//노드 기준 왼쪽
			{
				tp = tp->left;
			}
			else if (compare(&tp->data, &newNode->data)<0) //노드 기준 오른쪽
			{
				tp = tp->right;
			}
			else { ; }
		}

		// pp 노드의 추가할 노드의 위치 결정
		if ((compare(&pp->data, &newNode->data) > 0))
		{
			pp->left = newNode;
		}
		else if ((compare(&pp->data, &newNode->data) < 0))
		{
			pp->right = newNode;
		}
		else { ; }
	}
	tr->nodeCnt++;

	return newNode;
}
/* --------------------------------------------------------------------------------------
함수명 : inorderTraverse - 중위순회(정렬 순서로 출력)
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void inorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np != NULL) {
		inorderTraverse(np->left, print);
		print(&np->data);
		inorderTraverse(np->right, print);
	}
}

/* --------------------------------------------------------------------------------------
함수명 : preorderTraverse - 전위순회
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void preorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np != NULL)
	{
		print(&np->data);
		preorderTraverse(np->left, print);
		preorderTraverse(np->right, print);
	}
}
/* --------------------------------------------------------------------------------------
함수명 : postorderTraverse - 후위순회
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void postorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np != NULL)
	{
		postorderTraverse(np->left, print);
		postorderTraverse(np->right, print);
		print(&np->data);
	}

}
/* --------------------------------------------------------------------------------------
함수명 : searchNode - data에 해당하는 노드 검색
전달인자 : tr - Tree 구조체의 주소
data - 검색할 데이터 저장 공간의 시작주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴 값 : 찾은 노드의 주소 / 못찾으면 NULL pointer
---------------------------------------------------------------------------------------*/
Node * searchNode(Tree *tr, DataType  *data, int(*compare)(DataType *, DataType *))
{
	Node *tp = tr->root;
	while (tp != NULL)
	{
		if (compare(&tp->data, data) > 0)
		{
			tp = tp->left;
		}
		else if (compare(&tp->data, data) < 0)
		{
			tp = tp->right;
		}
		else { return tp; }
		
	}

	return NULL;
}

/* --------------------------------------------------------------------------------------
함수명 : deleteNode - data에 해당하는 노드 삭제
전달인자 : tr - Tree 구조체의 주소
data - 삭제할 데이터의 시작주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴 값 : 삭제한 노드의 parent 노드의 주소 / 못찾으면(삭제 실패 시) NULL pointer
---------------------------------------------------------------------------------------*/
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node *parent = tr->root;	// 삭제할 노드의 부모노드
	Node *deleteNode = tr->root;	// 삭제할 노드의 시작주소
	Node *son;	// 노드 삭제 후 부모노드와 연결 관계 맺어 줄 노드
	Node *parentSon;
	
	// 삭제할 노드와 삭제할 노드의 부모노드 시작주소 찾기
	while (deleteNode != NULL)
	{
		if (compare(&deleteNode->data, data) == 0)	//탐색 성공
			break;

		parent = deleteNode;	//현재 노드의 부모값 저장
		if (compare(&deleteNode->data, data) > 0)	//현재 트리에서 검색한 data > serch data
			deleteNode = deleteNode->left;
		else //현재 트리에서 검색한 data < serch data
			deleteNode = deleteNode->right;
	}
	if (deleteNode == NULL)	//못찾은 경우 실패 리턴
		return NULL;


	
	// 유형1 : 삭제할 노드의 오른쪽 자식이 없는 경우-삭제할 노드의 왼쪽 자식이 son역할
	if (deleteNode->right == NULL)
		son = deleteNode->left;

	// 유형2 : 삭제할 노드의 오른쪽 자식의 왼쪽 자식이 없는 경우-삭제할 노드의 오른쪽 자식이 son역할
	else if (deleteNode->right->left == NULL)
	{
		son = deleteNode->right;
		son->left = deleteNode->left;
	}

	// 유형3 : 그외 모든 경우-삭제할 노드의 오른쪽 서브트리에서 삭제할 데이터와 가장 가까운 값을 찾음
	else
	{
		// 부모노드 저장하면서 삭제할 데이터와 가장 가까운 값 검색
		son = deleteNode->right;
		while (son->left != NULL)
		{
			parentSon = son;
			son = son->left;
		}

		parentSon->left = son->right;
		son->left = deleteNode->left;
		son->right = deleteNode->right;
	}
		
	/*	삭제될 노드 대신 자식(son) 역할을 할 노드를 위치시킴	*/
	// 루트 노드를 삭제하는 경우
	if (parent == deleteNode)
	{
		tr->root = son;
		return parent;
	}

	if (compare(&deleteNode->data, &parent->data) > 0)	//부모노드의 오른쪽 노드에 삽입
		parent->right = son;
	else// 부모노드의 왼쪽 노드에 삽입
		parent->left = son;

	free(deleteNode);
	tr->nodeCnt--;

	return parent;
}
/* --------------------------------------------------------------------------------------
함수명 : destroyTree - tree 내의 모든 노드 삭제(tree 소멸)
전달인자 : tr - Tree 구조체의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void destroyTree(Tree * tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);  // 데이터 노드는 순회 하며 삭제
	tr->root = NULL;
	tr->nodeCnt = 0;
}

/* --------------------------------------------------------------------------------------
함수명 : postorderDelete - postorder(후위 순회)방식의 노드 삭제(재귀호출 함수)
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void postorderDelete(Node *np, void(*print)(DataType *))
{
	if (np != NULL)
	{
		postorderDelete(np->left, print);
		postorderDelete(np->right, print);
		print(&np->data);
		free(np);
	}
	
}
