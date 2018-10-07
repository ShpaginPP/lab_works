#include <stdio.h>// директива подключения файлов библиотеки(предпроцессор - обработка перед комплияцией)
#define YES 1 // макроподстановка
#define NO 0
#define MAXLINE 100
void process_line( char buffer[]);// объявление интерфейс функции([аргументы])  
int main( void )// int - тип данных результата, точка входа
{
	char line[MAXLINE];// строка
	fgets(line,sizeof(line),stdin);// ввод символов в строку
	process_line( line ); // обработка
	puts( line );// вывод
	getchar ();
	return 0;// возвращение значение в main
}
void process_line ( char *buffer)
{
	char *c;// current symbol
	char *sp1; //начало первого слова
    char *fp1; //конец первого слова
    char *sp2; //начало второго слова
    char *fp2; //конец второго слова
    char *spg; //начало нового потенциального слова
    char *fpg; //конец нового потенциального слова
	int found; // признак слова
	found=NO;
	c=buffer;
	sp1=0;
	fp1=0;
	sp2=0;
	fp2=0;
	spg=0;
	fpg=0;
	while(*c)
	{
		if((*c<'a' || *c>'z')&&(*c<'A' || *c>'Z')&&(*c<'0' || *c>'9'))
		{
			if(found == YES && spg!=0)
			{
				sp2=sp1;
				fp2=fp1;
				sp1=spg;
				fp1=c;
			}
			spg=0;
			fpg=0;
			found=YES;
		}
		else
		{
			if(*c>='0' && *c<='9')
				found=NO;
			if(spg==0)
				spg=c;
		}
		c++;
	}
	if(sp2!=0)
		while(*sp2++=*fp2++); // удаление слова( где ";" тело цикла)
}	
