#include <stdio.h>
#include <assert.h>
#include <string.h>
#define TRUE (1)
#define FALSE (0)
#define MAX_BSIZE 1000

typedef struct _relativeCoordinate
{
	int x;  /* x ��� ��ǥ */
	int y;  /* y ��� ��ǥ */
}RCoordinate;

int initBoard(FILE *fp);
int boggleGame(const char *searchWord);
int hasWord(int y, int x, const char * word);
int inRange(int y, int x);

int maxX;   /* x ��ǥ�� �ִ밪 ���� */
int maxY;   /* y ��ǥ�� �ִ밪 ���� */

RCoordinate RCXY[8] = { { -1,-1 },{ -1,0 },{ -1,1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,-1 },{ 0,1 } }; /* ��� ��ǥ ��� �迭 */
																			  /* ( 0, 0 )�� ������ġ�� ������ �����ǥ ǥ��

																			  (-1,-1) ( 0,-1) ( 1,-1)
																			  (-1, 0) ( 0, 0) ( 1, 0)
																			  (-1, 1) ( 0, 1) ( 1, 1)
																			  */
char board[MAX_BSIZE][MAX_BSIZE + 2];  /* ���๮��, NULL������ ũ�⸦ ����ؼ� column�� +2 */

/*------------------------------------------------------------------
�Լ��� : main()
------------------------------------------------------------------*/
int main()
{
	FILE *fp;
	int res;  /* �ܾ� �˻� ���� �� 1, ���� �� 0 ���� */
	char *searchWord[] = { "PRETTY", "LGE", "ASDVX" };
	int count = 0;  /* ���� ȸ�� �������� */


	fp = fopen("c:\\data\\boggleGame.txt", "rt");
	assert(fp != NULL);

	while (initBoard(fp))
	{
		res = boggleGame(searchWord[count]); /* ���� ���� �Լ� ȣ�� */

		if (res == TRUE)  /* �ܾ  ã������ */
			printf("+ Existence!!(%s)\n", searchWord[count]);
		else   /* �ܾ ��ã������ */
			printf("- Nonexistence!!(%s)\n", searchWord[count]);
		++count;
	}

	fclose(fp);

	return 0;
}
/*------------------------------------------------------------------
�Լ��� �� ���: initBoard() - ���Ͽ��� ���� ������ board������ �Է� �޾� �ʱ�ȭ
�������� : fp - board������ �����ϰ� �ִ� ������ ���� ������
���ϰ�: board������ ���������� �ʱ�ȭ �ϸ� 1����, �����ϸ� 0 ����
------------------------------------------------------------------*/
int initBoard(FILE *fp)
{
	int i; /* iterator */
	fscanf(fp, "%d %d\n", &maxY, &maxX);  /* ������ ����, ���� ���� �б� */
	if (maxY == 0 || maxX == 0) return FALSE;  /* ���� �Ǵ� ���� ũ�� 0�̸� �ʱ�ȭ ���� */

	for (i = 0; i< maxY; ++i)
	{
		fgets(board[i], maxX + 2, fp); /* ���๮�ڿ� �ι����� ũ�� ����ؼ� +2 */
		board[i][maxX] = '\0';  /* �Բ� �������� �� �� ���� ���๮�� ���� */
		puts(board[i]);  /* �о���� �迭 ��� */
	}
	return TRUE;  /* board �ʱ�ȭ ���� */
}
/*-----------------------------------------------------------------
�Լ��� �� ���: boggleGame() - board�� ���޵� ���ڿ��� �ִ°� �˻��ϴ� �Լ�
�������� : searchWord - �˻��� �ܾ�ڿ��� �����ּ�
���ϰ�: board�� ã�� ���ڿ��� ������ 1����, ������ 0����
-----------------------------------------------------------------*/
int boggleGame(const char *searchWord)
{
	int i, j;  /* iterator */
	int res;  /* �ܾ� �˻� �������� ���� */
	for (i = 0; i<maxY; ++i)
	{
		for (j = 0; j<maxX; ++j)
		{
			res = hasWord(i, j, searchWord); /* �迭 ��ü�� �� ���� �ܾ� �˻� ���������� �����Ͽ� �ݺ� ȣ�� �� */
			if (res == TRUE)  /* �ܾ ã������ �ٷ� TRUE ���� */
				return TRUE;
		}
	}
	return FALSE;
}
/*-------------------------------------------------------------------
�Լ��� �� ���: inRange() - ���޵� y, x ��ǥ�� ��ȿ�� �˻� �Լ�
�������� : y - ��ȿ�� �˻��� y ��ǥ
x - ��ȿ�� �˻��� y ��ǥ
���ϰ�: y,x ��ǥ�� ��� ��ȿ�ϸ� 1����, �� ��ǥ�� ��ȿ���� ������ 0 ����
-------------------------------------------------------------------*/
int inRange(int y, int x)
{
	if (y >= 0 && y<maxY && x >= 0 && x<maxX)
		return TRUE;
	else
		return FALSE;
}
/*--------------------------------------------------------------------------
�Լ��� �� ���: hasWord() - y,x ��ǥ�� ã�� ���� ���翩�θ� �˻��ϴ� ����Լ�
�������� : y - �˻��� y ��ǥ
x - �˻��� y ��ǥ
word - �˻��� ���ڿ��� �����ּ�
���ϰ�: �ش���ǥ�� ã�� ���� ������ 1����, ��ǥ�� ��ȿ���� �ʰų� ã�� ���� ������ 0����
--------------------------------------------------------------------------*/
int hasWord(int y, int x, const char * word)
{
	int i;  /* iterator */
	int nextY; /* ������ �˻��� Y��ǥ ���� */
	int nextX; /* ������ �˻��� X��ǥ ���� */
	int len;

	/* basis prat1 : ���� ��ġ�� ���� ���̸� ���� */
	if (!inRange(y, x))
		return FALSE;

	/* basis prat2 : word���ڿ��� ù ���ڰ� x, y ��ǥ�� ����� ��ġ���� ������ ���� */
	if (board[y][x] != word[0])
		return FALSE;

	/* basis prat3 : �ܾ��� ���̰� 1�̸� ���� <== basis prat2���� �ݵ�� ���߿� �˻��ؾ� �� */
	len = strlen(word);
	if (len == 1)
		return TRUE;
		

	/* 8���⿡ ���� �̾����� ���縵�� �����ϴ°� �˻� - ��� ȣ���� �Ͼ�� �κ�*/
	for (i = 0; i < 8; i++)
	{
		if (hasWord(y + RCXY[i].x, x + RCXY[i].y, word + 1))
			return TRUE;
	}

	return FALSE;
}



