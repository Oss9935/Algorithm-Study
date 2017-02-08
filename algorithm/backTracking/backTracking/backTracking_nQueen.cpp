#pragma warning(disable: 4996)
#include <stdio.h>
#define CHECK (1)
#define MAX_CNT 15
int columnChk[MAX_CNT + 1];             // column üũ �迭 (0���� ��� ����)
int incDiagonalLineChk[MAX_CNT * 2 + 1];  // ������ �����ϴ� �밢�� üũ �迭 (0���� ��� ����)
int decDiagonalLineChk[MAX_CNT * 2 + 1];  // ������ �����ϴ� �밢�� üũ �迭 (0���� ��� ����)
int placementCnt;                     // ���� ���ݸ��ϰ� ��ġ ������ ����� �� ī��Ʈ ����
int n;                                // queen�� ��(���� ��,���� ��) ���庯��

void nQueen(int row);

int main()
{
	while (1)  // ���� ������ 1~MAX_CNT �� ������ �ƴϸ� ���Է�
	{
		printf("���� ������ �Է� �Ͻÿ� : ");
		scanf("%d", &n);
		if (n>0 && n <= MAX_CNT)
			break;
	}
	nQueen(1);
	printf("��ġ ������ ����� �� : %d\n\n", placementCnt);
	return 0;
}
/*------------------------------------------------------------------
�Լ��� �� ���: nQueen() - n���� queen�� ��ġ�ϱ� ���� ���ȣ�� �Լ�
�������� : row - ü������ ���ȣ(0���� ��� ����)
���ϰ�: ����
------------------------------------------------------------------*/
void nQueen(int row)
{
	int i, j;

	// bias : ����
	if (row == n + 1)
	{
		placementCnt++;
		return;
	}

	// row ���� ���� queen�� column ��ġ ����
	// ���� ��ġ�� ������ �ش� ���� queen�� ���´�.
	// ���� ��ġ�� ������ ��Ʈ��ŷ�� �ؾ���. (�� ��, i = n + 1 �� ����)
	for (i = 1; i <= n; i++)
	{
		if ((columnChk[i] || incDiagonalLineChk[row + i] || decDiagonalLineChk[n + row - i]) == !CHECK)
		//if (columnChk[i] != CHECK && incDiagonalLineChk[row + i] != CHECK && decDiagonalLineChk[n + row - i] != CHECK)
		{
			columnChk[i] = CHECK;
			incDiagonalLineChk[row + i] = CHECK;
			decDiagonalLineChk[n + row - i] = CHECK;
			nQueen(row + 1);

			// Ž�� ���� �� ��Ʈ��ŷ�� ���� check ���� �ǵ���.
			columnChk[i] = !CHECK;
			incDiagonalLineChk[row + i] = !CHECK;
			decDiagonalLineChk[n + row - i] = !CHECK;
		}
	}

	// bias : ����
	return;
}
