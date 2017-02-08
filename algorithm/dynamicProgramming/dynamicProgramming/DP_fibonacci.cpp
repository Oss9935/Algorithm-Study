#pragma warning(disable:4996)
#include<stdio.h>
#include <stdlib.h>
#include <ctime>

enum { FALSE, TRUE };
long long int input(long long int *num1, long long int *num2);
long long int nrFibonacci(long long int num1, long long int num2);
long long int rFibonacci(long long int num1, long long int num2);
long long int rfibo(int num);
long long int dpFibonacci(long long int num1, long long int num2);
long long int dpfibo(int num);
long long int memo[1000] = { 1,1, };  // �޸������̼� ó���� ���� �迭(fibonacci������ ������� ���� ��)

int  main()
{
	long long int start, end;
	long long int res;
	long long int fiboCnt;
	while (1)
	{
		int startTime, endTime;

		res = input(&start, &end);
		if (res == FALSE)
			break;
		printf("[ ����͸� �̿��� ó�� ��� ]\n");
		startTime = clock();
		fiboCnt = nrFibonacci(start, end);
		printf("Fibonacci ���� : %3d\n", fiboCnt);
		endTime = clock();
		printf("�˰��� ���� �ҿ�ð� : %d(millisecond)\n", (endTime - startTime));

		printf("[ �ܼ� ��� ȣ���� �̿��� ó�� ��� ]\n");
		startTime = clock();
		fiboCnt = rFibonacci(start, end); // end���� 10���� �Ѿ�� �ӵ��� ������ ������ 
		printf("Fibonacci ���� : %3d\n", fiboCnt);
		endTime = clock();
		printf("�˰��� ���� �ҿ�ð� : %d(millisecond)\n", (endTime - startTime));

		printf("---------------------------------------\n");
		printf("[ ������ȹ��(DP)�� �̿��� ó�� ��� ]\n");
		startTime = clock();
		fiboCnt = dpFibonacci(start, end); // end���� 10���� �Ѿ�� �ſ� ����
		printf("Fibonacci ���� : %3d\n", fiboCnt);
		endTime = clock();
		printf("�˰��� ���� �ҿ�ð� : %d(millisecond)\n", (endTime - startTime));
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
long long int dpFibonacci(long long int start, long long int end)
{
	long long int fiboNum = 0;
	long long int fibonacciCnt = 0;
	long long int i;

	for (i = 1; fiboNum <= end; ++i)
	{
		fiboNum = dpfibo(i);  // i��° fibonacci ���� ã��
		if (fiboNum >= start && fiboNum <= end) // �����̳��� fibonacci�� �̸�
		{
			++fibonacciCnt;
			printf("%lld\n", fiboNum);
		}
	}
	return fibonacciCnt;
}
long long int dpfibo(int num)  // num��° fibonacci���� ���� ����
{
	if (num >= 2 && memo[num] == 0) // �޸������̼ǵ� ���� ������ �Ʒ� ���� ������� �����Ƿ� �ӵ��� ����
		memo[num] = dpfibo(num - 2) + dpfibo(num - 1);  // ���� ���� �޸������̼� ��
	return memo[num];
}
//-------------------------------------------------------------------------------------------------------------
long long int nrFibonacci(long long int start, long long int end)
{
	long long int temp;
	long long int fibonacciCnt = 0;
	long long int num1 = 0, num2 = 1;

	temp = num1 + num2;

	while (temp <= end)
	{
		temp = num1 + temp;
		num1 = temp - num1;
		if (start <= temp && temp <= end)
		{
			printf("%lld\n", temp);
			++fibonacciCnt;
		}
	}
	printf("\n");
	return fibonacciCnt;
}

//-------------------------------------------------------------------------------------------------------------
long long int rFibonacci(long long int start, long long int end)
{
	long long int fiboNum = 0;
	long long int fibonacciCnt = 0;
	long long int i;

	for (i = 1; fiboNum <= end; ++i)
	{
		fiboNum = rfibo(i);  // i��° fibonacci ���� ã��
		if (fiboNum >= start && fiboNum <= end) // �����̳��� fibonacci�� �̸�
		{
			++fibonacciCnt;
			printf("%lld\n", fiboNum);
		}
	}
	return fibonacciCnt;
}


//-------------------------------------------------------------------------------------------------------------
long long int rfibo(int num)  // num��° fibonacci���� ���� ����
{
	long long int res;

	if (num == 0 || num == 1)
		return 1;
	else
	{
		res = rfibo(num - 2) + rfibo(num - 1);
		return res;
	}
}


//-------------------------------------------------------------------------------------------------------------
long long int input(long long int *num1, long long int *num2)
{
	printf("\n���� �� [����] �� �� �Է�(0 0 �Է½� ����) : ");
	scanf("%lld %lld", num1, num2);
	if (*num1 + *num2 == 0)
	{
		return FALSE;
	}
	return TRUE;
}