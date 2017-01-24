#include "parseFile.h"
#include "doubleLinkedList.h"

/*----------------------------------------------------------------------------------
name : openFile
func : openFile and error handling
return : opened file's descriptor
----------------------------------------------------------------------------------*/
FILE * openFile()
{
	FILE *fp;
	fp = fopen(FILE_PATH, "rt");
	assert(fp != NULL);
	return fp;
}


/*----------------------------------------------------------------------------------
name : dataFileLoad()
func : load file data to double linked list (unit : word)
parm *lp : LinkedList management struct's pointer
----------------------------------------------------------------------------------*/
void dataFileLoad(LinkedList *lp)
{
	FILE *fp;
	DataType addData;
	char wordBuf[FILE_WORD_BUF_SIZE];

	fp = openFile();

	while (fgets(wordBuf, FILE_WORD_BUF_SIZE, fp)) {
		strcpy(addData.words, wordBuf);
		appendFromTail(lp, &addData);
	}

}

