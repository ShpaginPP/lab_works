/*���� ������ "�����������"
 ���������� ����.
 �������������� ����.
 �������� �������.
 ����� ����������� ���� �� �������� � ���������� �������. ����� ��������
���������� �������� �� ���� ������.
 ����� ������ ������ �� ��������� ������������� � ���������� �������.
������ ����� �� ������������� � ������� �����.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define LEN 100
#define SPC 20
struct data //���� ���
{
	char name[LEN];//������: ������ �.�.
	char spec[SPC];//�������������
	int num;//����� ��������
	int day;// ���� ������
	int st_vis;//������ ������
	int end_vis;//����� ������
	struct data *ptr;//��������� �� ��������� �������
};
//���������� ������ ���c��
struct data* init()//� - �������� ������� ����
{
	struct data *lst;
	lst = (struct data*)malloc(sizeof(struct data));
	lst->ptr = NULL; // ��������� ���� ������
	return (lst);
}
// �������� ������
struct data * deleteHead(struct data *head)
{
	struct data *temp;
	temp = head->ptr;
	free(head);//������������ ������ �������� ����� ������
	return(temp);
}
//���������� �����!!!!
void deleteDoc(struct data *lst, struct data *head)
{
	struct data *temp;
	temp = head;
	while (temp->ptr != lst)//������ ������ � ������
	{
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr;
	free(lst);
}
void freeStruct(struct data *head)//������� ������
{
	struct data * current = head;
	struct data * next = NULL;
	do
	{
		next = current->ptr;
		free(current);
		current = next;
	} while (current != NULL);
}
//���������� �������� � ����� ������
struct data* appendlist(struct data **headRef)
{
	struct data* current = *headRef;
	struct data* lst;
	lst = (struct data*)malloc(sizeof(struct data));
	lst->ptr = NULL;
	// ���� ������ ����
	if (current == NULL) {
		*headRef = lst;
	}
	else {
		// �����
		while (current->ptr != NULL) {
			current = current->ptr;
		}
		current->ptr = lst;
	}
	return(lst);
}
//��������������� ����� ������
void sort(struct data* headRef, int count)
{
	struct data* current;
	struct data* next;
	int noSwap;
	int iBuf;
	char cBuf[LEN];
	for (int i = count - 1; i >= 0; i--)
	{
		current = headRef;
		next = current->ptr;
		noSwap = 1;
		for (int j = 0; j < i; j++)
		{
			if (strcmp(current->name, next->name) > 0)
			{
				strcpy(cBuf, current->name);
				strcpy(current->name, next->name);
				strcpy(next->name, cBuf);
				strcpy(cBuf, current->spec);
				strcpy(current->spec, next->spec);
				strcpy(next->spec, cBuf);
				iBuf = current->num;
				current->num = next->num;
				next->num = iBuf;
				iBuf = current->day;
				current->day = next->day;
				next->day = iBuf;
				iBuf = current->st_vis;
				current->st_vis = next->st_vis;
				next->st_vis = iBuf;
				iBuf = current->end_vis;
				current->end_vis = next->end_vis;
				next->end_vis = iBuf;
				noSwap = 0;
			}
			current = current->ptr;
			next = current->ptr;
		}
		if (noSwap == 1)
			break;
	}
}
void input(struct data **headRef, int *cnt)//������ �� �����
{
	FILE *fin;
	FILE *finit;
	char line[100];
	struct data *current;
	fin = fopen("test.txt", "r"); // ������� ���� ��� ������
	if (fin == NULL)
	{
		finit = fopen("test.txt", "w");
		fclose(finit);
		fin = fopen("test.txt", "r");
	}
	while (!feof(fin))
	{
		if (!*cnt)
		{
			current = *headRef = init();
		}
		else
		{
			current = appendlist(headRef);
		}
		if (fscanf(fin, "%[^\n]\n", line) == -1)
		{
			break;
		}
		strcpy(current->name, line);
		fscanf(fin, "%[^\n]\n", line);
		strcpy(current->spec, line);
		fscanf(fin, "%d %d %d %d\n", &current->num, &current->day, &current->st_vis, &current->end_vis);
		(*cnt)++;
	}
	fclose(fin);
}
void save(struct data* head)//���������� ���������
{
	FILE *fout;
	struct data* current = head;
	fout = fopen("test.txt", "w"); // ������� ���� ��� ������
	while (current != NULL)
	{
		fprintf(fout, "%s\n", current->name);
		fprintf(fout, "%s\n", current->spec);
		fprintf(fout, "%d %d %d %d\n", current->num, current->day, current->st_vis, current->end_vis);
		current = current->ptr;
	}
	fclose(fout); // ������� ������� ����
}
void addDoc(struct data **head, int *cnt)//������� ���������� �����
{
	char spec[6][20] = { "������","�����������","��������","�������","���","����������" };
	char days[5][20] = { "�����������","�������","�����","�������","�������" };
	int i;
	int callback_int;
	int flag;//���������� ��� ������������ �����
	struct data *current;
	//char callback_char[LEN];//���������� ���������� ������
	if (!*cnt)
	{
		current = *head = init();
		(*cnt)++;
	}
	else
	{
		current = appendlist(head);//���������� ������ �����
		(*cnt)++;
	}
	system("cls");//��������� �������
	printf("������� ��� �����:\n���: ");
	scanf("\n%[^\n]", &current->name);
	system("cls");//��������� �������
	printf("������� ������������� �����:\n");
	for (i = 0; i < 6; i++)
	{
		printf("[%d]%s\n", i + 1, spec[i]);
	}
	printf("�������� ������������� ����� (1-6): ");
	flag = 0;
	do {
		if (flag)
			printf("������� ������������ ��������. ������� �� 1 �� 6: ");
		scanf("%d", &callback_int);
		flag = 1;
	} while ((callback_int < 1) || (callback_int > 6));
	strcpy(current->spec, spec[callback_int - 1]);
	system("cls");//��������� �������
	printf("������� ����� ��������: ");
	scanf("%d", &current->num);
	system("cls");//��������� �������
	for (i = 0; i < 5; i++)
	{
		printf("[%d]%s\n", i + 1, days[i]);
	}
	printf("�������� ���� ������ ����� (1-5): ");
	flag = 0;
	do {
		if (flag)
			printf("������� ������������ ��������. ������� �� 1 �� 5: ");
		scanf("%d", &callback_int);
		flag = 1;
	} while ((callback_int < 1) || (callback_int > 5));
	current->day = callback_int;
	system("cls");//��������� �������
	printf("������� ����� ������ ������: ");
	scanf("%d", &current->st_vis);
	system("cls");//��������� �������
	printf("������� ����� ����� ������: ");
	scanf("%d", &current->end_vis);
}
void edit(struct data *current)//������� �������������� �����
{
	int i;
	int vibor;
	int flag;
	char spec[6][20] = { "������","�����������","��������","�������","���","����������" };
	char days[5][20] = { "�����������","�������","�����","�������","�������" };
	system("cls");//��������� �������
	printf("������ ��� �����: %s \n", current->name);
	printf("������� ����� ��� �����:\n���: ");
	scanf("\n%[^\n]", &current->name);
	system("cls");//��������� �������
	printf("������ ������������� �����: %s \n", current->spec);
	printf("������� ����� ������������� �����:\n");
	for (i = 0; i < 6; i++)
	{
		printf("[%d]%s\n", i + 1, spec[i]);
	}
	printf("�������� ������������� ����� (1-6): ");
	flag = 0;
	do {
		if(flag)
			printf("������� ������������ ��������. ������� �� 1 �� 6: ");
		scanf("%d", &vibor);
		flag = 1;
	} while ((vibor < 1) || (vibor > 6));
	strcpy(current->spec, spec[vibor - 1]);
	system("cls");//��������� �������
	printf("������ ����� ��������: %d\n", current->num);
	printf("������� ����� ����� ��������: ");
	scanf("%d", &current->num);
	system("cls");//��������� �������
	printf("������ ���� ������ �����: %s \n", days[current->day - 1]);
	for (i = 0; i < 5; i++)
	{
		printf("[%d]%s\n", i + 1, days[i]);
	}
	printf("�������� ���� ������ ����� (1-5): ");
	flag = 0;
	do {
		if (flag)
			printf("������� ������������ ��������. ������� �� 1 �� 5: ");
		scanf("%d", &vibor);
		flag = 1;
} while ((vibor < 1) || (vibor > 5));
	current->day = vibor;
	system("cls");//��������� �������
	printf("������� ����� ������ ������: ");
	scanf("%d", &current->st_vis);
	system("cls");//��������� �������
	printf("������� ����� ����� ������: ");
	scanf("%d", &current->end_vis);
}
int main(void)//�������� �������
{
	system("chcp 1251");
	system("cls");
	struct data *head = NULL;
	struct data *current = NULL;
	int vibor;
	int flag = 0;
	int count = 0, i = 0;
	char days[5][20] = { "�����������","�������","�����","�������","�������" };
	char spec[6][20] = { "������","�����������","��������","�������","���","����������" };
	char main;
	input(&head, &count);
	do
	{
		system("cls");
		printf("[0] ����� �� ���������\n[1] �������� ������ �����\n[2] ������������� ����������\n[3] ������� �����\n[4] ������� ������ � ���������� �������\n[5] ������ �������� �� ���� ������\n[6] ������ �����\n�������� ����� �� ������ : ");
		scanf("%c", &main);
		switch (main)
		{
		case '1':
			addDoc(&head, &count);
			break;
		case '2':
			system("cls");
			if (!count)
			{
				printf("��� ������\n");
				system("pause");
				break;
			}
			i = 0;
			current = head;
			while (current != NULL)
			{
				printf("[%d] %s - %s\n", i + 1, current->name, current->spec);
				i++;
				current = current->ptr;
			}
			printf("�������� ����� ��� ���������: ");
			scanf("%d", &vibor);
			current = head;
			for (i = 0; i < vibor - 1; i++)
			{
				current = current->ptr;
			}
			edit(current);
			break;
		case '3':
			system("cls");
			if (!count)
			{
				printf("��� ������\n");
				system("pause");
				break;
			}
			current = head;
			i = 0;
			while (current != NULL)
			{
				printf("[%d] %s\n", i + 1, current->name);
				i++;
				current = current->ptr;
			}
			printf("�������� ����� ��� ����������: ");
			scanf("%d", &vibor);
			current = head;
			for (i = 0; i < vibor - 1; i++)
			{
				current = current->ptr;
			}
			if (vibor == 1)
			{
				head = deleteHead(current);

			}
			else
			{
				deleteDoc(current, head);
			}
			count--;
			break;
		case '4':
			if (!count)
			{
				printf("��� ������\n");
				system("pause");
				break;
			}
			sort(head, count);
			current = head;
			i = 1;
			while (current != NULL)
			{
				printf("------[%d]------\n", i);
				printf("�������������: %s\n", current->spec);
				printf("���: %s\n", current->name);
				printf("�������: %d\n", current->num);
				printf("����: %s\n", days[(current->day) - 1]);
				printf("������/����� ������: � %d �� %d\n", current->st_vis, current->end_vis);
				i++;
				current = current->ptr;
			}
			system("pause");
			break;
		case '5':
			system("CLS");
			if (!count)
			{
				printf("��� ������\n");
				system("pause");
				break;
			}
			printf("������� ����� ��������: ");
			scanf("%d", &vibor);
			system("CLS");
			printf("=========================\n");
			printf("������� � %d\n", vibor);
			printf("=========================\n");
			for (i = 0; i < 5; i++)
			{
				printf("-------------------------\n");
				printf("%s\n", days[i]);
				printf("-------------------------\n");
				current = head;
				while (current != NULL)
				{
					if (current->num == vibor && current->day == i)
						printf("%d - %d\n", current->st_vis, current->end_vis);
					current = current->ptr;
				}
				printf("\n");
			}
			system("pause");
			break;
		case '6':
			system("CLS");
			if (!count)
			{
				printf("��� ������\n");
				system("pause");
				break;
			}
			for (i = 0; i < 6; i++)
			{
				printf("[%d]%s\n", i + 1, spec[i]);
			}
			printf("�������� ������������� ����� (1-6): ");
			flag = 0;
			do {
				if(flag)
					printf("������� ������������ ��������. ������� �� 1 �� 6: ");
				scanf("%d", &vibor);
				flag = 1;
			}while ((vibor < 1) || (vibor > 6));
			system("CLS");
			current = head;
			i = 1;
			while (current != NULL)
			{
				if (!strcmp(current->spec, spec[vibor - 1]))
				{
					printf("------[%d]------\n", i);
					printf("�������������: %s\n", current->spec);
					printf("���: %s\n", current->name);
					printf("�������: %d\n", current->num);
					printf("����: %s\n", days[(current->day) - 1]);
					printf("������/����� ������: � %d �� %d\n", current->st_vis, current->end_vis);
					i++;
				}
				current = current->ptr;
			}
			system("pause");
			break;
		default:
			break;
		}
	} while (main != '0');
	save(head);
	freeStruct(head);
	return 0;
}