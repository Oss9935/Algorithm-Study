#include "fileFunc.h"
#include "circularQueue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int inputint(char *message);
int random(int);
DataType randomChoice(Queue *qPtr, int num);
void printResult();
void lottaryFunc(int *pLottary, char *fileName, int *cnt, FILE* fp);
DataType getRandomInQueue(Queue *qPtr);
int main()
{
	int lottaryNum;
	int total = 0, i = 0;
	int cnt = 0;
	int fileCnt = 0;
	
	char* fileName[] = { "C:\\data\\grade1.txt" , "C:\\data\\grade2.txt",
		"C:\\data\\grade3.txt"};

	FILE *fp;
	fp = openFile(RESULT_FILE_PATH, "wt");

	srand((unsigned int)time(NULL));
	lottaryNum = inputint("추첨자 명 수를 입력하시오 : ");
	
	fileCnt = sizeof(fileName) / sizeof(fileName[0]);

	while (lottaryNum > 0)
	{
		if (fileCnt == 0) { break; }
		fileCnt--;
		lottaryFunc(&lottaryNum, fileName[i++], &cnt, fp);
	}
	closeFile(fp);

	printResult();
	return 0;
}

void lottaryFunc(int *pLottary, char *fileName, int *cnt, FILE* fp)
{
	Queue que;
	int personCnt;
	DataType temp;

	initQueue(&que, QUEUE_SIZE);
	dataFileLoad(&que, fileName);
	personCnt = getQueueLength(&que);
	if (personCnt <= *pLottary)
	{ 
		//total만큼 파일에 write(난수 추첨 필요X)
		for (int i = 0; i < personCnt; i++)
		{
			dequeue(&que, &temp);
			dataFileWrite(temp, fp);
		}
	}
	else
	{
		//난수 발생하여 lottaryNum만큼 write
		for (int i = 0; i < *pLottary; i++)
		{
			temp = getRandomInQueue(&que);
			dataFileWrite(temp, fp);
		}
	}
	*pLottary -= personCnt;
	destroyQueue(&que);
}

DataType getRandomInQueue(Queue *qPtr)
{
	DataType data;
	int len;
	int randomNum;

	len = getQueueLength(qPtr);
	randomNum = random(len);
	while (randomNum--)
	{
		dequeue(qPtr, &data);
		enqueue(qPtr, data);
	}
	dequeue(qPtr, &data);

	return data;
}

int inputint(char *message)
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

int random(int num)
{
	return rand() % num;
}

DataType randomChoice(Queue *qPtr, int num)
{
	DataType temp;
	int peek = random(num);

	while (--peek)
	{
		dequeue(qPtr, &temp);
		enqueue(qPtr, temp);
	}
	dequeue(qPtr, &temp);
	return temp;
}


void printResult()
{
	Queue que;
	DataType data;
	int total;
	int i;

	initQueue(&que, QUEUE_SIZE);
	dataFileLoad(&que, RESULT_FILE_PATH);
	total = getQueueLength(&que);
	puts("[       당첨자명           주민번호           연락처   ]");
	for (i = 1; i <= total; i++)
	{
		printf("%3d.   ", i);
		dequeue(&que, &data);
		printString(&data);
	}
	destroyQueue(&que);
}