#include <stdio.h> 
#include <stdlib.h>

#define LEN 20
#define PMAS LEN/2 

int main(void)
{ 
	FILE *fpin; 
	FILE *fpout; 
	char line[LEN+2]; 
	char *pew[PMAS+1];// ������ ���������� �� ������ ����� 
	char *l; // ��������� �� ������
	char *src;// ��������� �� �����
	int j; //���-�� ��������
	int tmp;// ��������� ����������
	int k;// ���-�� ����
	int cnts;// ���-�� ��������
	int cntw;// ���-�� ���� ����� �������
	int prob;// �������� ���������� �������� ��� ������������
	int dob;// ������� �� ������� �������� �� �����

	if(!(fpin = fopen("test.txt", "r"))) return 1; 
	if(!(fpout = fopen("result.txt", "w"))) return 1; 

	while(l = fgets(line,sizeof(line),fpin))// ������ �����
	{ 
		sscanf(line,"%[^\n]",line);// ������� ����� ������ ���� �� ��������
		k = 0;
		pew[k] = 0;
		j = 0;

		for(;*l;l++)//���� �������� ��������
		{
			if(*l==' ')
				pew[k] = 0;
			else
			{
				if(!pew[k]) pew[k++] = line+j;//������ ������ �����
				*(line+j++)=*l;// ����� ��� ����� ������
			}
		}
		cnts = LEN - j;
		cntw = k - 1;
		if(cntw==0)
		{
			printf("%s\n",line);
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
			while(src!=pew[k])*l-- = *src--;// �������� �����
			*l-- = *src--;// ������� ������� ������� � �����
			tmp = prob;// �������� ���������� ���������� ��������
			while((tmp-->0) && (cnts-->0))*l-- = ' ';//��������� prob
			if(dob-->0)
			{
				cnts--;
				*l-- = ' ';
			}
			k--;
		}
		printf("%s\n",line);// ����� ����������
	}
	fclose(fpin);
	fclose(fpout);
	getchar();
	getchar();
	return 0;
}