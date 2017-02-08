#pragma warning(disable: 4996)
#include <stdio.h>
#include <assert.h>
#define MAX_CNT 100
int weight[MAX_CNT + 1];  // ������ ���Ը� �����ϴ� �迭(0���� ��� ����)
int value[MAX_CNT + 1];   // ���Ǻ� ��ġ�� �����ϴ� �迭 (0���� ��� ����)
int n;                  // ������ ���� ���庯��
int totWeight;          // �賶�� ���� ������ �� ���� ���� ����
void fileLoad(char * fileName);
int knapsack(void);
int makePermutaionTable(int(*indexAry)[4]);
/*---------------------------------------------------------------------------------------
main()
---------------------------------------------------------------------------------------*/
int main()
{
	fileLoad("C:\\data\\knapsack1.txt");
	printf("�ִ� ��ġ : %d\n\n", knapsack());
	return 0;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: fineLoad() - ���Ͽ��� ������ ����(����, ��ġ)�� �Է� �޾� �ʱ�ȭ�ϴ� �Լ�
�������� : fileName - ������ ������ �����ϰ� �ִ� ���ϸ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void fileLoad(char * fileName)
{
	FILE *fp;
	int i; /* iterator */
	fp = fopen(fileName, "rt");
	assert(fp != NULL);

	fscanf(fp, "%d %d\n", &n, &totWeight);  // ������ ������ �賶�� ���尡���� �ִ� ���� �Է� 

	for (i = 1; i <= n; ++i)
	{
		fscanf(fp, "%d %d\n", &weight[i], &value[i]); // ���Ǻ� ���Կ� ��ġ �Է�
	}
	fclose(fp);
	return;
}
/*------------------------------------------------------------------
�Լ��� �� ���: knapsack() - ���濡 ���� ū ��ġ�� �����ϴ� ��츦 ã�Ƴ��� �Լ�
�������� : ����
���ϰ�: ������ ���� ��ü �߿� �� ���Ը� ����� �ִ� ��ġ�� ���� ��
------------------------------------------------------------------*/
int knapsack(void)
{
	int indexAry[24][4] = { 0 };  // ���� ����迭
	int maxValue = 0; // �ִ� ��ġ ���� ���� 
	int cnt;	//������ ����
	int i ,j;
	int sumWeight, sumMoney;

	cnt = makePermutaionTable(indexAry);
	for (i = 0; i < cnt; i++)
	{
		sumWeight = 0;
		sumMoney = 0;
		j = 0;
		do 
		{
			sumWeight += weight[indexAry[i][j]];
			sumMoney += value[indexAry[i][j]];
			j++;
		} while (sumWeight <= totWeight);
		if (sumMoney >= maxValue)
			maxValue = sumMoney;
	}

	return  maxValue; // ���� ��ü �߿� �� ���Ը� ����� �ִ� ��ġ�� ���� ��
}
/*------------------------------------------------------------------
�Լ��� �� ���: makePermutaionTable() - index 4���� ������ ���� indexAry�� �����ϴ� �Լ�
�������� : ���� ������ ���� ���� �迭�� �����ּ�
���ϰ�: ������ ����
------------------------------------------------------------------*/
int makePermutaionTable(int(*indexAry)[4])
{
	int i, j, k, l;  // iterator
	int cnt = 0;  // ������ ���� ���� ����
	for (i = 1; i <= n; ++i)
	{
		for (j = 1; j <= n; ++j)
		{
			if (j != i)
			{
				for (k = 1; k <= n; ++k)
				{
					if (k != i && k != j)
					{
						for (l = 1; l <= n; ++l)
						{
							if (l != i && l != j && l != k)
							{
								indexAry[cnt][0] = i;
								indexAry[cnt][1] = j;
								indexAry[cnt][2] = k;
								indexAry[cnt][3] = l;
								++cnt;  // ������ ���� ī��Ʈ
							}

						}
					}
				}
			}
		}
	}
	return cnt;
}