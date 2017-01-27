#pragma once
#define FILE_PATH "C:\\data\\patternData.txt"
#define PATTERN_MAX 100

typedef struct PatternData
{
	char pattern[PATTERN_MAX];
	int cnt;
}PatternData;

typedef  PatternData DataType;     // ��峻�� ������ ������ ���� ������ 

//-------------------------------------
//   PatternData ����ü ���� �Լ�
//-------------------------------------
int comparePatternData(DataType *p1, DataType *p2);  // PatternData ����ü�� Pattern����� ���ϴ� �Լ�
void printPatternData(DataType *p);  // PatternData ����ü�� Pattern ����� ����ϴ� �Լ� 
