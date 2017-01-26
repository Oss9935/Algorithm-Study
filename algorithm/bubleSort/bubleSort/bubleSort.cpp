#include<stdio.h>
#include<time.h>    // time()
#include<stdlib.h>  // rand(), srand()
void iteratorBubbleSort(int *ary, int n);
void recursiveBubbleSort(int *ary, int n);
void initArray(int *ary, int n), printArray(int *ary, int n);
void swap(int *p1, int *p2);
int  main()
{
	int numberArray[10], arySize;
	arySize = sizeof(numberArray) / sizeof(numberArray[0]);
	srand((unsigned int)time(NULL));

	initArray(numberArray, arySize);
	printArray(numberArray, arySize);
	iteratorBubbleSort(numberArray, arySize);
	printArray(numberArray, arySize);
	puts("");
	initArray(numberArray, arySize);
	printArray(numberArray, arySize);
	recursiveBubbleSort(numberArray, arySize);
	printArray(numberArray, arySize);

	//getchar();
	return 0;
}
void iteratorBubbleSort(int *ary, int n)
{
	int i;
	int cnt = n - 1;
	while (cnt--)
	{
		for (i = 0; i < n - 1; i++)
		{
			if (ary[i] > ary[i+1]) 
			{
				swap(ary + i, ary + i + 1);
			}
		}
	}
}
void recursiveBubbleSort(int *ary, int n)
{
	int i;
	if (n == 1) { return; }
	for (i = 0; i < n - 1; i++)
	{
		if (ary[i] > ary[i + 1])
		{
			swap(ary + i, ary + i + 1);
		}
	}
	recursiveBubbleSort(ary, n - 1);
}
void initArray(int *ary, int n)
{
	int i;
	for (i = 0; i<n; ++i)
		ary[i] = rand() % 20 + 1;
}
void printArray(int *ary, int n)
{
	int i;
	printf("배열 내용 : ");
	for (i = 0; i<n; ++i)
		printf("%4d", ary[i]);
	printf("\n");
}

void swap(int *p1, int *p2)
{
	int temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}