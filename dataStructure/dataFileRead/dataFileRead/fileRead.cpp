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
		// fscanf() ���� �� return : EOF(������ EOF ������ EOF ��ȯ)
		if (fscanf(fp, "%s %d ", name, &age) == EOF) { break; }
		printf("�̸� : %s, ���� : %d\n", name, age);
	}

	fclose(fp);

	return 0;
}