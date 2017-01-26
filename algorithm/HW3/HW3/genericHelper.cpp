#include "circularQueue.h"

//-------------------------------------
//   char string[] 보조 함수
//-------------------------------------
void printString(DataType *p)
{
	makeSecret(p);
	printf("%-15s ", p->name);
	printf("%-17s  ", p->birth);
	printf("%-20s\n", p->phoneNumber);
}

void makeSecret(DataType *p)
{
	int idx;
	idx = strlen(p->birth);
	strcat(p->birth, "-*******");

	idx = findCharPos(p->phoneNumber, '-', 2);
	sprintf(p->phoneNumber + idx, "%s", "****");
}

int findCharPos(char *string, char key, int cnt)
{
	int pos = 0;
	int len;
	while (cnt--)
	{
		len = strlen(string);
		for (int i = 0; i < len; i++)
		{
			if (string[i+pos] == key) { 
				pos += i + 1; 
				break;
			}
		}
	}
	return pos;
}