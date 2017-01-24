#include <stdio.h>
#include <crtdbg.h>

#include "doubleLinkedList.h"
#include "parseFile.h"
#include <malloc.h>

void inputString(DataType *userInputWord, const char *message);
int inputWordList(LinkedList *pPointWords, LinkedList *pUserWords, 
	unsigned int *executionCnt, int(*compare)(DataType *, DataType *));
int ruleCheck(const LinkedList *userList, const DataType *userInput);

int main()
{
	LinkedList pointWords, userInputWords;
	unsigned int pointWordsCnt = 0;
	unsigned int executionCnt = 1;
	DataType firstString;
	
	// init double linked list for pointWords, and userInputWords
	create(&pointWords);
	create(&userInputWords);
	dataFileLoad(&pointWords);
	sortList(&pointWords, compareWords);
	
	strcpy(firstString.words, "pointer");
	appendFromTail(&userInputWords, &firstString);

	// loop until all elements of pointWords are deleted
	pointWordsCnt = pointWords.length;
	while (pointWordsCnt)
	{
		printf("* ����Ʈ�ܾ� : ");
		display(&pointWords, printWord);
		puts("");

		printf("* ����� �Է� �ܾ� : ");
		display(&userInputWords, printWord);
		puts("");
		
		if (inputWordList(&pointWords, &userInputWords, &executionCnt, compareWords))
		{
			pointWordsCnt--;
		}
		puts("");
	}
	printf("\n** ����Ʈ �ܾ ��� ������ϴ�. ������ �����մϴ�.\n");

	// free list
	destroy(&pointWords);
	destroy(&userInputWords);

	//_CrtDumpMemoryLeaks();
	return 0;
}


/*----------------------------------------------------------------------------------
name : inputString()
func : input String from user
parm *userInputWord : buffer to store user input string
parm *message : message
----------------------------------------------------------------------------------*/
void inputString(DataType *userInputWord, const char *message)
{
	printf("%s : ", message);
	fgets(userInputWord->words, WORD_MAX_SIZE, stdin);
	userInputWord->words[strlen(userInputWord->words) - 1] = NULL;
}

int inputWordList(LinkedList *pPointWords, LinkedList *pUserWords, 
	unsigned int *executionCnt, int(*compare)(DataType *, DataType *))
{
	DataType userInputWord;
	Node * resp;
	char message[WORD_MAX_SIZE] = { NULL, };

	sprintf(message, "�����ձ� �ܾ� �Է�(%dȸ��)", *executionCnt);
	inputString(&userInputWord, message);

	//check establishment of word chain
	if (ruleCheck(pUserWords, &userInputWord))	//if established...
	{
		++*executionCnt;
		appendFromTail(pUserWords, &userInputWord);	//update user list

		// check user input matches Point Words list
		resp = searchUnique(pPointWords, &userInputWord, compare);
		if (resp != NULL)
		{
			deleteNode(pPointWords, resp);
			return TRUE;
		}
	}
	else { printf("�߸� �Է��ϼ̽��ϴ�.\n"); }	//error message

	return FALSE;
}

int ruleCheck(const LinkedList *userList, const DataType *userInput) {
	char lastWord = TRUE;
	char newWord = FALSE;
	unsigned int idx = 0;

	idx = strlen(userList->tail->prev->data.words) - 1;
	lastWord = userList->tail->prev->data.words[idx];
	
	if (userList->tail->prev->data.words[idx] == userInput->words[0]) { return TRUE; }

	return FALSE;
}