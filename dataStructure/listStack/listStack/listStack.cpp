#include "liststack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
/*--------------------------------------------------------------------------------------
�Լ���ױ�� : initStack() -  ��ũ�帮��Ʈ�� �����Ǵ� ���� ���� �Լ�
�������� : sPtr - ���ð��� ����ü�� �ּ�
���ϰ� : ����
--------------------------------------------------------------------------------------*/
void initStack(Stack *sPtr)
{
	sPtr->head = (Snode *)calloc(1, sizeof(Snode)); //��� ��� ����
	assert(sPtr->head != NULL);
	sPtr->tail = (Snode *)calloc(1, sizeof(Snode)); //���� ��� ����
	assert(sPtr->tail != NULL);
	/*����尡 ���ϳ�带, ���ϳ�尡 ���ϳ�带 ����Ű�� ��*/
	sPtr->head->next = sPtr->tail;
	sPtr->tail->next = sPtr->tail;
	sPtr->cur = NULL;
	return;
}
/*--------------------------------------------------------------------------------------
�Լ���ױ�� : push() - ���ÿ� ������ �ϳ��� ������
�������� : sPtr - ���ñ���ü�� �ּ�
inData - ���ÿ� ������ ������
���ϰ� : ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int push(Stack *sPtr, DataType inData) /* stack�� ������ �����ϱ� */
{
	Snode *newNode;
	newNode = (Snode *)calloc(1, sizeof(Snode));
	if (newNode == NULL) { return FALSE; }

	newNode->next = sPtr->head->next;
	sPtr->head->next = newNode;

	newNode->data = inData;

	return TRUE;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ��� : pop() - ���ÿ��� ������ �ϳ��� ����
�������� : sPtr - ���ñ���ü�� �ּ�
popData - ���� �����͸� ������ �������� �ּ�
���ϰ� : ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int pop(Stack *sPtr, DataType *popData)
{
	if (isStackEmpty(sPtr)) { return FALSE; }
	sPtr->cur = sPtr->head->next;
	sPtr->head->next = sPtr->cur->next;
	*popData = sPtr->cur->data;

	free(sPtr->cur);

	return TRUE;
}
/*--------------------------------------------------------------------------------------
�Լ���ױ�� : printStack() - ������ ��� �����͸� ��� ��
�������� : sPtr - ���ñ���ü�� �ּ�
print -  DataType�� ������ ����ϴ� ��� ���� �Լ�
���ϰ� : ����
--------------------------------------------------------------------------------------*/
void printStack(Stack *sPtr, void(*print)(DataType *))
{
	sPtr->cur = sPtr->head->next;
	while (sPtr->cur != sPtr->tail) {
		print(&sPtr->cur->data);
		sPtr->cur = sPtr->cur->next;
	}

}
/*--------------------------------------------------------------------------------------
�Լ���ױ�� : destroyStack() - ���� �Ҹ� �Լ�
�������� : sPtr - ���ñ���ü�� �ּ�
���ϰ� : ����
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sPtr)
{
	Snode* tp;
	sPtr->cur = sPtr->head->next;
	while (sPtr->cur != sPtr->tail) {
		tp = sPtr->cur;
		sPtr->cur = sPtr->cur->next;
		free(tp);
	}

	free(sPtr->head);
	free(sPtr->tail);

}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: getStackTop() - ���ó��� �ֻ���� ���� �о���� �Լ�(pop������ ����)
��������: sPtr - ���ñ���ü�� �ּ�
getData - ���� �����͸� ������ �������� �ּ�
���ϰ�: ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int getStackTop(Stack *sPtr, DataType *getData)
{
	if (isStackEmpty(sPtr))  // stack�� ��������� pop����
	{
		return FALSE;
	}
	*getData = sPtr->head->next->data;
	return TRUE;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: isStackEmpty() - ������ ����ִ°� �˻�
��������: sPtr - ���ñ���ü�� �ּ�
���ϰ�: ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
int isStackEmpty(Stack *sPtr)
{
	if (sPtr->head->next == sPtr->tail) { return TRUE; }
	return FALSE;
}
