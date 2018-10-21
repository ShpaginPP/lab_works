#include <stdio.h> 
#include <stdlib.h>

#define LEN 20
#define PMAS LEN/2 

int main(void)
{ 
	FILE *fpin; 
	FILE *fpout; 
	char line[LEN+2]; 
	char *pew[PMAS+1]; 
	char *l; 
	char *src;
	int j;
	int tmp;
	int k;
	int cnts;
	int cntw;
	int prob; 
	int dob;

	if(!(fpin = fopen("test.txt", "r"))) return 1; 
	if(!(fpout = fopen("result.txt", "w"))) return 1; 

	while(l = fgets(line,sizeof(line),fpin))
	{ 
		sscanf(line,"%[^\n]",line);
		k = 0;
		pew[k] = 0;
		j = 0;

		for(;*l;l++)
		{
			if(*l==' ')
				pew[k] = 0;
			else
			{
				if(!pew[k]) pew[k++] = line+j;
				*(line+j++)=*l;
			}
		}
		cntw = LEN - j;
		cnts = k - 1;
		if(cntw==0)
		{
			printf("%s\n",line);
			continue;
		}
		prob = cnts / cntw;
		dob = cnts % cntw;
		*(line+LEN) = 0;
		l = line+LEN-1;
		pew[k--] = line+j;
		j = 0;
		while(k>=0)
		{
			j++;
			src = pew[k+1]-1;
			while(src!=pew[k])*l-- = *src--;
			*l-- = *src--;
			tmp = prob;
			while((tmp-->0) && (cntw-->0))*l-- = ' ';
			if(dob-->0)
			{
				cntw--;
				*l-- = ' ';
			}
			k--;
		}
		printf("%s\n",line);
	}
	fclose(fpin);
	fclose(fpout);
	system("pause");
	return 0;
}