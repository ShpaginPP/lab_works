#include <stdio.h> 
#include <stdlib.h>
#define LEN 100
#define PMAS LEN/2 

int main(void) 
{ 
	FILE *fpin; 
	FILE *fpout; 
	char line[LEN+2]; 
	char *pew[PMAS+1];// массив указателей на начало слова 
	char *l; // указатель на строку 
	char *src;// указатель на конец 
	int j; //кол-во символов 
	int tmp;// временная переменная 
	int k;// кол-во слов 
	int cnts;// кол-во пробелов 
	int cntw;// кол-во мест между словами 
	int prob;// итоговое количество пробелов для выравнивания 
	int dob;// остаток от деления пробелов на места 

	if(!(fpin = fopen("test.txt", "r"))) 
		return 1; 
	if(!(fpout = fopen("result.txt", "w")))
		return 1; 

	while(l = fgets(line,sizeof(line)-2,fpin))// чтение строк 
	{ 
		j = 0; 
		for(k = 1; k<PMAS; k++)
			pew[k] = l;
		k = 0; 
		pew[k] = 0; 
		for(;*l;l++)//цикл удаления пробелов 
		{ 
			if(*l==' ' || *l=='\n') 
				pew[k] = 0; 
			else 
			{ 
				if(!pew[k]) pew[k++] = line + j;//задаем начало слова 
				*(line + j++) = *l;// место где стоит символ 
			} 
		} 
		line[LEN] = '\n'; 
		line[LEN+1] = '\0'; 
		cnts = LEN - j; 
		cntw = k - 1; 
		if(cntw<=0) 
		{ 
			printf("%s",line); 
			continue; 
		} 
		prob = cnts / cntw; 
		dob = cnts % cntw; 
		l = line+LEN-1; 
		pew[k--] = line+j; 
		j = 0; 
		while(k>=0) 
		{ 
			j++; 
			src = pew[k+1]-1; 
			while(src!=pew[k]) *l-- = *src--;// копируем слово 
			*l-- = *src--;// перенос первого символа в слове 
			tmp = prob;// временно запоминаем количество пробелов 
			while((tmp-->0) && (cnts-->0))*l-- = ' ';//добавляем prob
			if(dob-->0) 
			{ 
				cnts--; 
				*l-- = ' '; 
			} 
			k--; 
		} 
		printf("%s",line);// вывод результата  
	} 
	fclose(fpin); 
	fclose(fpout); 
	getchar(); 
	getchar(); 
	return 0; 
}
