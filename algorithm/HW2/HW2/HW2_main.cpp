#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "doubleLinkedList.h"
//#include <crtdbg.h>>

int fileDataToList(char *fileName, LinkedList *lp);
FILE * openFile(char *fileName, char *mode);
void printPatternData(DataType *p);
int inputPatternLen();
int inputInt(char *);
void patternCheck(LinkedList *lp, int patternLen, int fileCnt);
void printString(DataType *p);

int main()
{
	LinkedList dataList;
	char fileName[] = FILE_PATH;
	int patternLen;
	int fileCnt;

	patternLen = inputPatternLen();
	fileCnt = fileDataToList(fileName, &dataList);

	patternCheck(&dataList, patternLen, fileCnt);

	destroy(&dataList);
	//_CrtDumpMemoryLeaks();
	return 0;
}

void patternCheck(LinkedList *lp, int patternLen, int fileCnt)
{
	LinkedList patternList;
	int patternCnt;
	Node *nowNode, *searchNode;
	int dataSize;
	DataType temp;

	while (fileCnt--)
	{
		nowNode = lp->head->next;	// ���� ���� ��Ʈ��
		dataSize = strlen(nowNode->data.pattern);	//���� ���� ��Ʈ���� �� ����
		patternCnt = strlen(nowNode->data.pattern) - patternLen + 1;	// ���� ���� �ݺ� Ƚ��
		create(&patternList);

		printString(&nowNode->data);
		for (int i = 0; i < patternCnt; i++)
		{
			strncpy(temp.pattern, nowNode->data.pattern + i, patternLen);
			temp.pattern[patternLen] = NULL;
			if ((searchNode = searchUnique(&patternList, &temp, comparePatternData)) == NULL)
			{
				temp.cnt = 1;
				appendFromTail(&patternList, &temp);
			}
			else
				searchNode->data.cnt++;
		}
		sortList(&patternList, comparePatternData);
		display(&patternList, printPatternData);

		destroy(&patternList);
		deleteNode(lp, nowNode);
		puts("----------------------------------------------");
	}
}


int fileDataToList(char *fileName, LinkedList *lp)
{
	FILE *fp;
	DataType data;
	int fileCnt = 0;

	fp = openFile(fileName, "rt");

	create(lp);	// file�� pattern data�� ������ doubleLinkedList ����
	while (fgets(data.pattern, PATTERN_MAX, fp))
	{
		data.pattern[strlen(data.pattern) - 1] = NULL;
		appendFromTail(lp, &data);
		fileCnt++;
	}

	fclose(fp);
	return fileCnt;
}

FILE * openFile(char *fileName, char *mode)
{
	FILE *fp;
	fp = fopen(fileName, mode);
	assert(fp != NULL);

	return fp;
}


int inputPatternLen()
{
	int num;
	while (1)
	{
		num = inputInt("* �˻��� ������ ���̸� �Է��Ͻÿ� : ");
		if (1 <= num && num <= 7) { return num; }
	}
}

int inputInt(char* message)
{
	int num;

	while (1)
	{
		printf("%s", message);
		scanf("%d", &num);
		if (getchar() == '\n') { return num; }
		while (getchar() != '\n') { ; }
	}
}

void printString(DataType *p)
{
	printf("** ��Ʈ�� : [ %s ]�� �˻� ��� **\n", p->pattern);
}

void printPatternData(DataType *p)
{
	printf("[%s] : %d��\n", p->pattern, p->cnt);
}

int comparePatternData(DataType *p1, DataType *p2)
{
	return strcmp(p1->pattern, p2->pattern);
}