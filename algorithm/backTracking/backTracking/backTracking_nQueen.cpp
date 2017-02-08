#pragma warning(disable: 4996)
#include <stdio.h>
#define CHECK (1)
#define MAX_CNT 15
int columnChk[MAX_CNT + 1];             // column 체크 배열 (0번방 사용 안함)
int incDiagonalLineChk[MAX_CNT * 2 + 1];  // 각도가 증가하는 대각선 체크 배열 (0번방 사용 안함)
int decDiagonalLineChk[MAX_CNT * 2 + 1];  // 각도가 감소하는 대각선 체크 배열 (0번방 사용 안함)
int placementCnt;                     // 서로 공격못하게 배치 가능한 경우의 수 카운트 변수
int n;                                // queen의 수(또한 행,열의 수) 저장변수

void nQueen(int row);

int main()
{
	while (1)  // 퀸의 개수가 1~MAX_CNT 개 범위가 아니면 재입력
	{
		printf("퀸의 개수를 입력 하시오 : ");
		scanf("%d", &n);
		if (n>0 && n <= MAX_CNT)
			break;
	}
	nQueen(1);
	printf("배치 가능한 경우의 수 : %d\n\n", placementCnt);
	return 0;
}
/*------------------------------------------------------------------
함수명 및 기능: nQueen() - n개의 queen을 배치하기 위한 재귀호출 함수
전달인자 : row - 체스판의 행번호(0행은 사용 안함)
리턴값: 없음
------------------------------------------------------------------*/
void nQueen(int row)
{
	int i, j;

	// bias : 성공
	if (row == n + 1)
	{
		placementCnt++;
		return;
	}

	// row 열에 놓을 queen의 column 위치 결정
	// 놓을 위치가 있으면 해당 열에 queen을 놓는다.
	// 놓을 위치가 없으면 백트래킹을 해야함. (이 때, i = n + 1 인 상태)
	for (i = 1; i <= n; i++)
	{
		if ((columnChk[i] || incDiagonalLineChk[row + i] || decDiagonalLineChk[n + row - i]) == !CHECK)
		//if (columnChk[i] != CHECK && incDiagonalLineChk[row + i] != CHECK && decDiagonalLineChk[n + row - i] != CHECK)
		{
			columnChk[i] = CHECK;
			incDiagonalLineChk[row + i] = CHECK;
			decDiagonalLineChk[n + row - i] = CHECK;
			nQueen(row + 1);

			// 탐색 실패 시 백트래킹을 위해 check 상태 되돌림.
			columnChk[i] = !CHECK;
			incDiagonalLineChk[row + i] = !CHECK;
			decDiagonalLineChk[n + row - i] = !CHECK;
		}
	}

	// bias : 실패
	return;
}
