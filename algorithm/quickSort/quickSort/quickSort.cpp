#include <stdio.h>
void quickSort(int *ary, int size);
void output(int *ary, int size);
void swap(int *p1, int *p2);
int main()
{
	int dataList[] = { 76, 12, 29, 3, 15, 6, 34, 29, 25 };
	int size = sizeof(dataList) / sizeof(dataList[0]);
	quickSort(dataList, size); 	/* �� ���� �Լ� ȣ�� */
	printf("\n\n[ �� ����  �� ��� ]\n");
	output(dataList, size);

	return 0;
}
/*----------------------------------------------------------------------
�Լ��� �� ��� : quickSort() - �� ���� �Լ�
��������: ary - ������ ������ �迭�� �����ּ�
size - ��Ʈ�� �������� ����
���ϰ�: ����
--------------------------------------------------------------------*/
void quickSort(int *ary, int size)
{
	int pivot, temp;
	int i, j;

	if (size <= 1) return; // �������� 1�����̸� sort�� �Ϸ�� �� �̹Ƿ� return

	pivot = ary[size - 1];         // ������ ���� �������� pivot���� ����

	i = 0;
	j = size - 1;
	while (i < j)
	{
		// ary[i] > pivot �� i �� ����
		while (ary[i] <= pivot && i < j) { i++; }
		while (ary[j] >= pivot && i < j) { j--; }
		if (i < j) { swap(ary + i, ary + j); }
	}
	swap(ary + i, ary + size - 1);
	// ���� �ұ����� ���� �� ���� ��� ȣ��
	quickSort(ary, i);

	// ���� �ұ����� ���� �� ���� ��� ȣ��
	quickSort(ary + i + 1, size - i -1);

}
/*------------------------------------------------------------------------
�Լ��� �� ��� : output() - �迭�� ��� ���� ����ϱ�
��������: ary - ������ ������ �迭�� �����ּ�
size - �������� ����
���ϰ�: ����
------------------------------------------------------------------------*/
void output(int *ary, int size)
{
	for (int i = 0; i<size; i++) {
		printf(" %d ", ary[i]);
	}
	printf("\n");
}

void swap(int *p1, int *p2)
{
	int temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}