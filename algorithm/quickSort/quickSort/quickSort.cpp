#include <stdio.h>
void quickSort(int *ary, int size);
void output(int *ary, int size);
void swap(int *p1, int *p2);
int main()
{
	int dataList[] = { 76, 12, 29, 3, 15, 6, 34, 29, 25 };
	int size = sizeof(dataList) / sizeof(dataList[0]);
	quickSort(dataList, size); 	/* 퀵 정렬 함수 호출 */
	printf("\n\n[ 퀵 정렬  후 출력 ]\n");
	output(dataList, size);

	return 0;
}
/*----------------------------------------------------------------------
함수명 및 기능 : quickSort() - 퀵 정렬 함수
전달인자: ary - 정렬할 데이터 배열의 시작주소
size - 소트할 데이터의 개수
리턴값: 없음
--------------------------------------------------------------------*/
void quickSort(int *ary, int size)
{
	int pivot, temp;
	int i, j;

	if (size <= 1) return; // 구간값이 1이하이면 sort가 완료된 것 이므로 return

	pivot = ary[size - 1];         // 구간의 가장 우측값을 pivot으로 정함

	i = 0;
	j = size - 1;
	while (i < j)
	{
		// ary[i] > pivot 인 i 값 검출
		while (ary[i] <= pivot && i < j) { i++; }
		while (ary[j] >= pivot && i < j) { j--; }
		if (i < j) { swap(ary + i, ary + j); }
	}
	swap(ary + i, ary + size - 1);
	// 좌측 소구간에 대한 퀵 정렬 재귀 호출
	quickSort(ary, i);

	// 우측 소구간에 대한 퀵 정렬 재귀 호출
	quickSort(ary + i + 1, size - i -1);

}
/*------------------------------------------------------------------------
함수명 및 기능 : output() - 배열의 모든 원소 출력하기
전달인자: ary - 정렬할 데이터 배열의 시작주소
size - 데이터의 개수
리턴값: 없음
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