#include <stdio.h>// ��������� ����������� ������ ����������(������������� - ��������� ����� �����������)
#define YES 1 // ����������������
#define NO 0
#define MAXLINE 100
void process_line( char buffer[]);// ���������� ��������� �������([���������])  
int main( void )// int - ��� ������ ����������, ����� �����
{
	char line[MAXLINE];// ������
	fgets(line,sizeof(line),stdin);// ���� �������� � ������
	process_line( line ); // ���������
	puts( line );// �����
	getchar ();
	return 0;// ����������� �������� � main
}
void process_line ( char *buffer)
{
	char *c;// current symbol
	char *sp1; //������ ������� �����
    char *fp1; //����� ������� �����
    char *sp2; //������ ������� �����
    char *fp2; //����� ������� �����
    char *spg; //������ ������ �������������� �����
    char *fpg; //����� ������ �������������� �����
	int found; // ������� �����
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
		while(*sp2++=*fp2++); // �������� �����( ��� ";" ���� �����)
}	