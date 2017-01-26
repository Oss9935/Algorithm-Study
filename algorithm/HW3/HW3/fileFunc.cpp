#include "fileFunc.h"
#include "circularQueue.h"

/*----------------------------------------------------------------------------------
name : openFile
func : openFile and error handling
return : opened file's descriptor
----------------------------------------------------------------------------------*/
FILE * openFile(char *path, char *mode)
{
	FILE *fp;
	fp = fopen(path, mode);
	assert(fp != NULL);
	return fp;
}

/*----------------------------------------------------------------------------------
name : closeFile
func : closeFile
parm fp : file descriptor to close
----------------------------------------------------------------------------------*/
void closeFile(FILE *fp)
{
	fclose(fp);
}

void dataFileLoad(Queue *q, char *path)
{
	FILE *fp;
	DataType addData;
	char readBuf[READBUF_SIZE];

	fp = openFile(path, "rt");
	while (fgets(readBuf, READBUF_SIZE, fp))
	{
		// read name from file
		readBuf[strlen(readBuf) - 1] = NULL;
		strcpy(addData.name, readBuf);	

		// read birth from file
		fgets(readBuf, READBUF_SIZE, fp);
		readBuf[strlen(readBuf) - 1] = NULL;
		strcpy(addData.birth, readBuf);

		// read phone number from file
		fgets(readBuf, READBUF_SIZE, fp);
		readBuf[strlen(readBuf) - 1] = NULL;
		strcpy(addData.phoneNumber, readBuf);

		enqueue(q, addData);
	}

	closeFile(fp);
}

void dataFileWrite(DataType data, FILE* fp)
{
	
	fprintf(fp, "%s\n%s\n%s\n", data.name, data.birth, data.phoneNumber);
}
