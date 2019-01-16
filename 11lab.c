#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define LETTER 1
#define NOT_THE_LETTER 0
#define MAXLEN 1000

void main(void)
{
	HANDLE hStdout;
	FILE *fp;
	char line[MAXLEN];
	char word[MAXLEN];
	int i = 0, k, j = 0;
	int flag, flag1, flag2 = 0, flag3 = 0;
	int prev_flag;
	char *ptr;
	char def_line[] = "#define";
	char mass[30][30];
	WORD foregroundColor0;
	WORD textAttribute;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	foregroundColor0 = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN;
	fp = fopen("test.txt", "rt");
	if (fp == NULL)
		return;
	while (!feof(fp))
	{
		ptr = fgets(line, 1000, fp);
		if (ptr == NULL)
			break;
		i = 0;
		prev_flag = flag = NOT_THE_LETTER;
		word[0] = '\0';
		while (*ptr != 0)
		{
			prev_flag = flag;
			if (*ptr == ' ' || *ptr == ',' || *ptr == '.' || *ptr == '\n' || *ptr == '[' || *ptr == ']' || *ptr == ';' || *ptr == '\0')
			{
				flag = NOT_THE_LETTER;
			}
			else
				flag = LETTER;
			if (flag != prev_flag)
			{
				word[i] = '\0';
				if (prev_flag && flag2)
				{
					strcpy(mass[j++], word);
				}
				flag1 = 0;
				for (k = 0; k < 10; k++)
				{
					if (!strcmp(word, mass[k]))
					{
						flag1 = 1;
						flag2 = 0;
						break;
					}
				}
				if (!strcmp(word, def_line))
					flag2 = 1;
				if (flag1)
				{
					textAttribute = foregroundColor0;
					SetConsoleTextAttribute(hStdout, textAttribute);
				}
				else
				{
					SetConsoleTextAttribute(hStdout, 7);
				}
				printf("%s", word);
				i = 0;
			}

			word[i++] = *ptr++;
		}
		if (i != 0)
		{
			word[i] = '\0';
			printf("%s", word);
		}
	}
	printf("\n");
	system("pause");
}
