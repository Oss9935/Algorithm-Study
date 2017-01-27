#pragma once
#define FILE_PATH "C:\\data\\patternData.txt"
#define PATTERN_MAX 100

typedef struct PatternData
{
	char pattern[PATTERN_MAX];
	int cnt;
}PatternData;

typedef  PatternData DataType;     // 노드내의 데이터 영역의 형명 재지정 

//-------------------------------------
//   PatternData 구조체 보조 함수
//-------------------------------------
int comparePatternData(DataType *p1, DataType *p2);  // PatternData 구조체의 Pattern멤버로 비교하는 함수
void printPatternData(DataType *p);  // PatternData 구조체의 Pattern 멤버를 출력하는 함수 
