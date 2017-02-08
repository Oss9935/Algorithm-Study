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
long long int memo[1000] = { 1,1, };  // 메모이제이션 처리를 위한 배열(fibonacci수열을 순서대로 저장 함)

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
		printf("[ 비재귀를 이용한 처리 결과 ]\n");
		startTime = clock();
		fiboCnt = nrFibonacci(start, end);
		printf("Fibonacci 개수 : %3d\n", fiboCnt);
		endTime = clock();
		printf("알고리즘 실행 소요시간 : %d(millisecond)\n", (endTime - startTime));

		printf("[ 단순 재귀 호출을 이용한 처리 결과 ]\n");
		startTime = clock();
		fiboCnt = rFibonacci(start, end); // end값이 10억을 넘어가면 속도가 현저히 떨어짐 
		printf("Fibonacci 개수 : %3d\n", fiboCnt);
		endTime = clock();
		printf("알고리즘 실행 소요시간 : %d(millisecond)\n", (endTime - startTime));

		printf("---------------------------------------\n");
		printf("[ 동적계획법(DP)를 이용한 처리 결과 ]\n");
		startTime = clock();
		fiboCnt = dpFibonacci(start, end); // end값이 10억을 넘어가도 매우 빠름
		printf("Fibonacci 개수 : %3d\n", fiboCnt);
		endTime = clock();
		printf("알고리즘 실행 소요시간 : %d(millisecond)\n", (endTime - startTime));
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
		fiboNum = dpfibo(i);  // i번째 fibonacci 수를 찾음
		if (fiboNum >= start && fiboNum <= end) // 구간이내의 fibonacci수 이면
		{
			++fibonacciCnt;
			printf("%lld\n", fiboNum);
		}
	}
	return fibonacciCnt;
}
long long int dpfibo(int num)  // num번째 fibonacci수의 값을 구함
{
	if (num >= 2 && memo[num] == 0) // 메모이제이션된 값이 있으면 아래 식을 계산하지 않으므로 속도가 향상됨
		memo[num] = dpfibo(num - 2) + dpfibo(num - 1);  // 계산된 값을 메모이제이션 함
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
		fiboNum = rfibo(i);  // i번째 fibonacci 수를 찾음
		if (fiboNum >= start && fiboNum <= end) // 구간이내의 fibonacci수 이면
		{
			++fibonacciCnt;
			printf("%lld\n", fiboNum);
		}
	}
	return fibonacciCnt;
}


//-------------------------------------------------------------------------------------------------------------
long long int rfibo(int num)  // num번째 fibonacci수의 값을 구함
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
	printf("\n시작 값 [공백] 끝 값 입력(0 0 입력시 종료) : ");
	scanf("%lld %lld", num1, num2);
	if (*num1 + *num2 == 0)
	{
		return FALSE;
	}
	return TRUE;
}