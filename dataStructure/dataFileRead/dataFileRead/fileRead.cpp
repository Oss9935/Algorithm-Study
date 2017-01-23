#include <stdio.h>
#include <assert.h>

#define DATA_FILE "C:\\data\\list.txt"
#define NAME_SIZE 20

int main()
{
	char name[NAME_SIZE];
	int age;

	FILE *fp = NULL;

	fp = fopen(DATA_FILE, "rt");
	assert(fp != NULL);

	while (1) {
		// fscanf() 실패 시 return : EOF(파일의 EOF 만나면 EOF 반환)
		if (fscanf(fp, "%s %d ", name, &age) == EOF) { break; }
		printf("이름 : %s, 나이 : %d\n", name, age);
	}

	fclose(fp);

	return 0;
}