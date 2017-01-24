#pragma once
#include "doubleLinkedList.h"
#define FILE_PATH "C:\\data\\pointWord.txt"
#define FILE_WORD_BUF_SIZE 100	//equal to WORD_MAX_SIZE
#include <assert.h>
#include <stdio.h>
#include <string.h>


/*	file function	*/
FILE * openFile();
void dataFileLoad(LinkedList *lp);
