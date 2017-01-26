#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>

#define READBUF_SIZE 20
enum { FALSE, TRUE };

typedef struct _Person {
	char name[READBUF_SIZE];
	char birth[READBUF_SIZE];
	char phoneNumber[READBUF_SIZE];
}Person;

typedef Person DataType;     // 노드내의 데이터 영역의 형명 재지정 

//-------------------------------------
//   char string[] 보조 함수
//-------------------------------------
void printString(DataType *p);


void makeSecret(DataType *p);
int findCharPos(char *string, char key, int cnt);