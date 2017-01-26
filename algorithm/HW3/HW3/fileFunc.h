#pragma once
#include "circularQueue.h"

#define RESULT_FILE_PATH "C:\\data\\win.txt"

/*	file function	*/
FILE * openFile(char *, char *);
void closeFile(FILE *);
void dataFileLoad(Queue *, char *);
void dataFileWrite(DataType, FILE* fp);
