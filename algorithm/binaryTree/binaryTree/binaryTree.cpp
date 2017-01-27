#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

/* -------------------------------------------------------------------------------------
�Լ��� : initTree - Ʈ�� ���� ����ü�� �ʱ�ȭ �ϴ� �Լ�
�������� : tr - Tree ����ü�� �ּ�
���� �� : ����
--------------------------------------------------------------------------------------*/
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}
/* --------------------------------------------------------------------------------------
�Լ��� : makeNode - �� ��带 ����� �� ����� �ּҸ� �����ϴ� �Լ�
�������� : data - �� ��忡 ����� ��(������)
left - �� ����� left ��� ��
right - �� ����� right ��� ��
���� �� : �� ����� �ּ� / �޸� �Ҵ� ���� �� NULL pointer
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
�Լ��� : addNode - ��带 �����ϴ� �Լ�
�������� : tr - Tree ����ü�� �ּ�
data - �� ��忡 ����� ������ ���� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : �� ����� �ּ� / �޸� �Ҵ� ���� �� NULL pointer
---------------------------------------------------------------------------------------*/
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node *newNode, *tp, *pp;
	newNode = makeNode(data, NULL, NULL);

	// root ��忡 add node
	if (tr->root == NULL)
	{
		tr->root = newNode;
	}
	else {
		// root �̿��� ��忡 add node
		tp = tr->root;
		while (tp != NULL)
		{
			pp = tp;	// ���� ��� ��ġ �����ϰ�(pp), tp�� �̿��� Ž��
			if (compare(&tp->data, &newNode->data)>0)	//��� ���� ����
			{
				tp = tp->left;
			}
			else if (compare(&tp->data, &newNode->data)<0) //��� ���� ������
			{
				tp = tp->right;
			}
			else { ; }
		}

		// pp ����� �߰��� ����� ��ġ ����
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
	

	return newNode;
}
/* --------------------------------------------------------------------------------------
�Լ��� : inorderTraverse - ������ȸ(���� ������ ���)
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
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
�Լ��� : preorderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
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
�Լ��� : postorderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
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
�Լ��� : searchNode - data�� �ش��ϴ� ��� �˻�
�������� : tr - Tree ����ü�� �ּ�
data - �˻��� ������ ���� ������ �����ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : ã�� ����� �ּ� / ��ã���� NULL pointer
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
�Լ��� : deleteNode - data�� �ش��ϴ� ��� ����
�������� : tr - Tree ����ü�� �ּ�
data - ������ �������� �����ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : ������ ����� parent ����� �ּ� / ��ã����(���� ���� ��) NULL pointer
---------------------------------------------------------------------------------------*/
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	// TODO	

	// ����1 : ������ ����� ������ �ڽ��� ���� ���-������ ����� ���� �ڽ��� son����

	// ����2 : ������ ����� ������ �ڽ��� ���� �ڽ��� ���� ���-������ ����� ������ �ڽ��� son����

	// ����3 : �׿� ��� ���-������ ����� ������ ����Ʈ������ ������ �����Ϳ� ���� ����� ���� ã��

	// ������ ��� ��� �ڽ�(son) ������ �� ��带 ��ġ��Ŵ
	return NULL;
}
/* --------------------------------------------------------------------------------------
�Լ��� : destroyTree - tree ���� ��� ��� ����(tree �Ҹ�)
�������� : tr - Tree ����ü�� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void destroyTree(Tree * tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);  // ������ ���� ��ȸ �ϸ� ����
	tr->root = NULL;
	tr->nodeCnt = 0;
}

/* --------------------------------------------------------------------------------------
�Լ��� : postorderDelete - postorder(���� ��ȸ)����� ��� ����(���ȣ�� �Լ�)
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
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