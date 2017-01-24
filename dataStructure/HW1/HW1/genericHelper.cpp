#include <string.h>
#include <stdio.h>
#include "datatype.h"

/*----------------------------------------------------------------------------------
name : compareWords()
func : compare two words
parm *source : words1
parm *target : words2
return : strcmp's result
----------------------------------------------------------------------------------*/
int compareWords(DataType *source, DataType *target)
{
	return strcmp(source->words, target->words);
}

/*----------------------------------------------------------------------------------
name : printWord()
func : print DataType(words)
parm *pData : array words to print
----------------------------------------------------------------------------------*/
void printWord(DataType *pData)
{
	printf(" %s /", pData->words);
}