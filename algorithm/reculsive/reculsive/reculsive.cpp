#include<stdio.h>
int iteratorPowerOf2(int power);
int recursivePowerOf2(int power);
int  main()
{
	int power = 10;
	printf("2ÀÇ %d½ÂÀÇ °ª =  %d\n", power, iteratorPowerOf2(power));
	printf("2ÀÇ %d½ÂÀÇ °ª =  %d\n", power, recursivePowerOf2(power));
	getchar();
	return 0;
}

int iteratorPowerOf2(int power)
{
	int res = 1;
	while (power--)
	{
		res *= 2;
	}
	return res;
}

int recursivePowerOf2(int power)
{
	if (power == 0) { return 1; }
	else 
	{
		return 2 * recursivePowerOf2(power - 1);
	}
}
