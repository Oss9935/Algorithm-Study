#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void print_array(int *data, int n);
void swap(int *data, int a, int b);
void selection_sort(int *data, int n);
void selection_sort2(int *data, int n);

int main()
{
	int data[100000];           // 소트할 데이터 저장 배열
	int n;                   // 소트할 데이터의 개수 저장
	int startTime, endTime;
	printf("process start time : %d(millisecond)\n", clock());
	srand((unsigned int)time(NULL));
	scanf("%d", &n);         // 소트할 데이터의 개수 입력
	for (int i = 0; i<n; i++)   // 소트할 데이터 생성
		data[i] = rand();
	//print_array(data, n);         // 배열 내용 출력
	startTime = clock();
	selection_sort2(data, n);
	endTime = clock();
	printf("소트 알고리즘 시작시간 : %d(millisecond)\n", startTime);
	printf("소트 알고리즘 종료시간 : %d(millisecond)\n", endTime);
	printf("소트 알고리즘 실행 소요시간 : %d(millisecond)\n", (endTime - startTime));
	//print_array(data, n);  // sort 종료 후 배열 내용 출력

	getchar(); getchar();
	return 0;
}

void print_array(int *data, int n)
{
	printf("------------------------------------------------\n");
	for (int i = 0; i<n; i++)
		printf("%d ", data[i]);
	printf("\n");
	printf("------------------------------------------------\n");
}

void swap(int *data, int a, int b)
{
	int t = data[a];
	data[a] = data[b];
	data[b] = t;
}

void selection_sort(int *data, int n)
{
	for (int i = 0; i<n - 1; i++)
		for (int j = i + 1; j<n; j++)
			if (data[i] > data[j])
				swap(data, i, j);
}

void selection_sort2(int *data, int n)
{
	int target;
	for (int i = 0; i<n - 1; i++)
	{
		target = i;
		for (int j = i + 1; j<n; j++)
			if (data[target] > data[j])
				target = j;
		swap(data, i, target);
	}
}
