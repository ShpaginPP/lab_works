#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#define YES 1
#define NO 0
#define LEN 100
#define NLINES 10
int main(void)
{
	system("chcp 1251");
	system("cls");
	char lines[32];
	FILE *f;
	char* pl;
	int cnt = 0, i, j;
	if ((f = fopen("input.txt", "r")) == NULL)
	{
		return 1;
	}
	pl = (char*)malloc(sizeof(char)*LEN*NLINES);
	while (!feof(f))
	{
		fgets(pl + cnt++ * LEN, LEN, f);

	}
	fclose(f);
	for (i = 1; i < cnt; i++)
	{
		for (j = 0; j < cnt - i; j++)
		{
			if (strcmp(pl + j * LEN, pl + (j + 1) * LEN) > 0)
			{
				strcpy(lines, pl + j * LEN);
				strcpy(pl + j * LEN, pl + (j + 1) * LEN);
				strcpy(pl + (j + 1) * LEN, lines);
			}
		}
	}
	for (i = 0; i < cnt; i++)
	{
		printf("%s", pl + i * LEN);
	}
	system("pause");
	return 0;
}
