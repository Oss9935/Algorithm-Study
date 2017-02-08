#include "liststack.h"
#include <stdio.h>
#include <assert.h>

int main()
{
	Stack lstk, rstk;     /* 왼쪽, 오른쪽 스택 생성*/
	FILE *fp;
	char ch;
	int i;
	int cmdCnt;  /* 명령어 개수 저장 변수 */

	initStack(&lstk); /* 스택초기화*/
	initStack(&rstk); /* 스택초기화*/

	fp = fopen("d:\\data\\editor.txt", "rt");
	assert(fp!=NULL);

	// 파일 첫줄의 문자열을 left stack에 저장 - 저장 후 커서의 위치를 문자열의 가장 뒤로 인식됨
	while((ch=fgetc(fp)) != '\n')
		push(&lstk, ch);
	fscanf(fp, "%d", &cmdCnt);  /* 명령어 개수 읽어들이기 */

	for(i=0; i<cmdCnt; ++i)
	{
		fscanf(fp, " %c", &ch);
		switch(ch) 
		{
		case 'P':   /* 문자를 커서 오른쪽에 추가함 - 추가 후 커서는 추가된 문자의 오른쪽에 위치 함 */
			fscanf(fp, " %c", &ch);
			push(&lstk, ch);
			break;
		case 'L' :  /* 커서를 왼쪽으로 한칸 옮김 - 커서가 맨 앞에 있으면 무시됨 */
			if(pop(&lstk, &ch))
				push(&rstk, ch);
			break;
		case 'D' : /* 커서를 오른쪽으로 한칸 옮김 - 커서가 맨 뒤에 있으면 무시됨 */
			if(pop(&rstk, &ch))
				push(&lstk, ch);
			break;
		case 'B' : /* 커서 왼쪽의 문자를 삭제함 - 커서가 맨 앞에 있으면 무시됨 */
			pop(&lstk, &ch);
			break;
		}
	}

	/* 결과 출력하기 - lstk의 내용을 rstk으로 모두 옮긴 후 rstk 출력 */
	while(pop(&lstk, &ch))   
			push(&rstk, ch);
	printStack(&rstk, printChar);

	destroyStack(&lstk);
	destroyStack(&rstk);

	fclose(fp);
	return 0;
}

//-------------------------------------
//   char type 보조 함수
//-------------------------------------
/*--------------------------------------------------------------------------------------
함수명 및 기능: printChar() – 전달인자로 넘겨진 int값을 정해진 format으로 출력 함
전달인자: p - 출력할 문자의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void printChar(DataType *p)
{
	printf("%c", *p);
}