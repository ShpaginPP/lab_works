/*Áàçà äàííûõ "Ïîëèêëèíèêà"
 Ïîïîëíåíèå áàçû.
 Ðåäàêòèðîâàíèå áàçû.
 Óäàëåíèå çàïèñåé.
 Âûâîä ñîäåðæèìîãî áàçû ïî ôàìèëèÿì â àëôàâèòíîì ïîðÿäêå. Âûâîä çàãðóçêè
âûáðàííîãî êàáèíåòà ïî äíÿì íåäåëè.
 Âûâîä ñïèñêà âðà÷åé ïî óêàçàííîé ñïåöèàëüíîñòè â àëôàâèòíîì ïîðÿäêå.
Ïîäáîð âðà÷à ïî ñïåöèàëüíîñòè è âðåìåíè ïðè¸ìà.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define LEN 100
#define SPC 20
struct data //Óçåë ÎËÑ
{
	char name[LEN];//Ïðèìåð: Èâàíîâ È.È.
	char spec[SPC];//Ñïåöèàëüíîñòü
	int num;//Íîìåð êàáèíåòà
	int day;// Äåíü ïðèåìà
	int st_vis;//Íà÷àëî ïðèåìà
	int end_vis;//Êîíåö ïðèåìà
	struct data *ptr;//óêàçàòåëü íà ñëåäóþùèé ýëåìåíò
};
//Îáúÿâëåíèå íà÷àëà ñïècêà
struct data* init()//à - çíà÷åíèå ïåðâîãî óçëà
{
	struct data *lst;
	lst = (struct data*)malloc(sizeof(struct data));
	lst->ptr = NULL; // ïîñëåäíèé óçåë ñïèñêà
	return (lst);
}
// Óäàëåíèå ãîëîâû
struct data * deleteHead(struct data *head)
{
	struct data *temp;
	temp = head->ptr;
	free(head);//îñâîáîæäåíèå ïàìÿòè òåêóùåãî êîðíÿ ñïèñêà
	return(temp);
}
//óâîëüíåíèå âðà÷à!!!!
void deleteDoc(struct data *lst, struct data *head)
{
	struct data *temp;
	temp = head;
	while (temp->ptr != lst)//÷òåíèå ñïèñêà ñ ãîëîâû
	{
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr;
	free(lst);
}
void freeStruct(struct data *head)//î÷èñòêà ïàìÿòè
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
//äîáàâëåíèå ýëåìåíòà â êîíåö ñïèñêà
struct data* appendlist(struct data **headRef)
{
	struct data* current = *headRef;
	struct data* lst;
	lst = (struct data*)malloc(sizeof(struct data));
	lst->ptr = NULL;
	// åñëè ñïèñîê ïóñò
	if (current == NULL) {
		*headRef = lst;
	}
	else {
		// èíà÷å
		while (current->ptr != NULL) {
			current = current->ptr;
		}
		current->ptr = lst;
	}
	return(lst);
}
//ôîðìàòèðîâàííûé âûâîä âðà÷åé
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
void input(struct data **headRef, int *cnt)//çàïèñü èç ôàéëà
{
	FILE *fin;
	FILE *finit;
	char line[100];
	struct data *current;
	fin = fopen("test.txt", "r"); // îòêðûòü ôàéë äëÿ ÷òåíèÿ
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
void save(struct data* head)//ñîõðàíåíèå èçìåíåíèé
{
	FILE *fout;
	struct data* current = head;
	fout = fopen("test.txt", "w"); // îòêðûòü ôàéë äëÿ ÷òåíèÿ
	while (current != NULL)
	{
		fprintf(fout, "%s\n", current->name);
		fprintf(fout, "%s\n", current->spec);
		fprintf(fout, "%d %d %d %d\n", current->num, current->day, current->st_vis, current->end_vis);
		current = current->ptr;
	}
	fclose(fout); // çàêðûòü âõîäíîé ôàéë
}
void addDoc(struct data **head, int *cnt)//ôóíêöèÿ äîáàâëåíèÿ âðà÷à
{
	char spec[6][20] = { "Õèðóðã","Îôòàëüìîëîã","Òåðàïåâò","Ïåäèàòð","ËÎÐ","Ñòîìàòîëîã" };
	char days[5][20] = { "Ïîíåäåëüíèê","Âòîðíèê","Ñðåäà","×åòâåðã","Ïÿòíèöà" };
	char *ptr;
	int i;
	int callback_int;
	char callback_char[10];
	int flag;//ïåðåìåííàÿ ïðè íåïðàâèëüíîì ââîäå
	
	struct data *current;
	//char callback_char[LEN];//Ïåðåìåííàÿ ñ÷èòûâàíèÿ ñòðîêè
	if (!*cnt)
	{
		current = *head = init();
		(*cnt)++;
	}
	else
	{
		current = appendlist(head);//äîáàâëåíèå íîâîãî âðà÷à
		(*cnt)++;
	}
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå ÔÈÎ âðà÷à:\nÔÈÎ: ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå èìÿ. Ââåäèòå èìÿ â ôîðìàòå Ôàìèëèÿ È.Î. ");
		scanf("\n%[^\n]", &current->name);
		ptr = &current->name;
		while (*ptr!= '\0')
		{
			if (!(*ptr >= 'à' && *ptr <= 'ÿ' || *ptr == ' ' || *ptr == '.' || *ptr >= 'À' && *ptr <= 'ß'))
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
			ptr++;
		}
	} while (flag);
	flag = 0;
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå ñïåöèàëüíîñòü âðà÷à:\n");
	for (i = 0; i < 6; i++)
	{
		printf("[%d]%s\n", i + 1, spec[i]);
	}
	printf("Âûáåðèòå ñïåöèàëüíîñòü âðà÷à (1-6): ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 1 äî 6: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
	} while (callback_int < 1 || callback_int > 6);
	strcpy(current->spec, spec[callback_int - 1]);
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå íîìåð êàáèíåòà: ");
	scanf("%d", &current->num);
	system("cls");//Î÷èñùåíèå êîíñîëè
	for (i = 0; i < 5; i++)
	{
		printf("[%d]%s\n", i + 1, days[i]);
	}
	printf("Âûáåðèòå äåíü ðàáîòû âðà÷à (1-5): ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 1 äî 5: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
	} while (callback_int < 1 || callback_int > 5);
	current->day = callback_int;
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå âðåìÿ íà÷àëà ðàáîòû: ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 8 äî 24: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
		current->st_vis = callback_int;
	} while (callback_int < 8 || callback_int > 24);
		system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå âðåìÿ êîíöà ðàáîòû: ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 16 äî 24: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
		current->end_vis = callback_int;
	} while (callback_int < 16 || callback_int > 24);
}
void edit(struct data *current)//ôóíêöèÿ ðåäàêòèðîâàíèÿ âðà÷à
{
	int i;
	char vibor[2];
	int ivibor=0;
	int flag;
	char *ptr;
	char spec[6][20] = { "Õèðóðã","Îôòàëüìîëîã","Òåðàïåâò","Ïåäèàòð","ËÎÐ","Ñòîìàòîëîã" };
	char days[5][20] = { "Ïîíåäåëüíèê","Âòîðíèê","Ñðåäà","×åòâåðã","Ïÿòíèöà" };
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ñòàðîå ÔÈÎ âðà÷à: %s \n", current->name);
	printf("Ââåäèòå íîâîå ÔÈÎ âðà÷à:\nÔÈÎ: ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå èìÿ. Ââåäèòå èìÿ â ôîðìàòå Ôàìèëèÿ È.Î. : ");
		scanf("\n%[^\n]", &current->name);
		ptr = &current->name;
		while (*ptr != '\0')
		{
			if (!(*ptr >= 'à' && *ptr <= 'ÿ' || *ptr == ' ' || *ptr == '.' || *ptr >= 'À' && *ptr <= 'ß'))
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
			ptr++;
		}
	} while (flag);
	flag = 0;
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ñòàðàÿ ñïåöèàëüíîñòü âðà÷à: %s \n", current->spec);
	printf("Ââåäèòå íîâóþ ñïåöèàëüíîñòü âðà÷à:\n");
	for (i = 0; i < 6; i++)
	{
		printf("[%d]%s\n", i + 1, spec[i]);
	}
	printf("Âûáåðèòå ñïåöèàëüíîñòü âðà÷à (1-6): ");
	flag = 0;
	do {
		if(flag)
			printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 1 äî 6: ");
		scanf("%s", &vibor);
		ivibor = atoi(vibor);
		flag = 1;
	} while ((ivibor < 1) || (ivibor > 6));
	strcpy(cu
		rrent->spec, spec[ivibor - 1]);
	flag = 0;
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ñòàðûé íîìåð êàáèíåòà: %d\n", current->num);
	printf("Ââåäèòå íîâûé íîìåð êàáèíåòà: ");
	scanf("%d", &current->num);
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Áûâøèé äåíü ðàáîòû âðà÷à: %s \n", days[current->day - 1]);
	for (i = 0; i < 5; i++)
	{
		printf("[%d]%s\n", i + 1, days[i]);
	}
	printf("Âûáåðèòå äåíü ðàáîòû âðà÷à (1-5): ");
	flag = 0;
	do {
		if (flag)
			printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 1 äî 5: ");
		scanf("%d", &vibor);
		flag = 1;
} while ((vibor < 1) || (vibor > 5));
	current->day = vibor;
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå âðåìÿ íà÷àëà ðàáîòû: ");
	scanf("%d", &current->st_vis);
	system("cls");//Î÷èñùåíèå êîíñîëè
	printf("Ââåäèòå âðåìÿ êîíöà ðàáîòû: ");
	scanf("%d", &current->end_vis);
}
int main(void)//îñíîâíàÿ ôóíêöèÿ
{
	system("chcp 1251");
	system("cls");
	struct data *head = NULL;
	struct data *current = NULL;
	int vibor;
	int flag = 0;
	int count = 0, i = 0;
	char days[5][20] = { "Ïîíåäåëüíèê","Âòîðíèê","Ñðåäà","×åòâåðã","Ïÿòíèöà" };
	char spec[6][20] = { "Õèðóðã","Îôòàëüìîëîã","Òåðàïåâò","Ïåäèàòð","ËÎÐ","Ñòîìàòîëîã" };
	char main;
	input(&head, &count);
	do
	{
		system("cls");
		printf("[0] Âûéòè èç ïðîãðàììû\n[1] Äîáàâèòü íîâîãî âðà÷à\n[2] Ðåäàêòèðîâàòü ðàñïèñàíèÿ\n[3] Óâîëèòü âðà÷à\n[4] Âûâåñòè âðà÷åé â àëôàâèòíîì ïîðÿäêå\n[5] Ðàáîòà êàáèíåòà ïî äíÿì íåäåëè\n[6] Ïîäáîð âðà÷à\nÂûáåðèòå ïóíêò èç ñïèñêà : ");
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
				printf("Íåò âðà÷åé\n");
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
			printf("Âûáåðèòå âðà÷à äëÿ èçìåíåíèÿ: ");
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
				printf("Íåò âðà÷åé\n");
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
			printf("Âûáåðèòå âðà÷à äëÿ óâîëüíåíèÿ: ");
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
				printf("Íåò âðà÷åé\n");
				system("pause");
				break;
			}
			sort(head, count);
			current = head;
			i = 1;
			while (current != NULL)
			{
				printf("------[%d]------\n", i);
				printf("Ñïåöèàëüíîñòü: %s\n", current->spec);
				printf("Èìÿ: %s\n", current->name);
				printf("Êàáèíåò: %d\n", current->num);
				printf("Äåíü: %s\n", days[(current->day) - 1]);
				printf("Íà÷àëî/Êîíåö ïðèåìà: ñ %d äî %d\n", current->st_vis, current->end_vis);
				i++;
				current = current->ptr;
			}
			system("pause");
			break;
		case '5':
			system("CLS");
			if (!count)
			{
				printf("Íåò âðà÷åé\n");
				system("pause");
				break;
			}
			printf("Ââåäèòå íîìåð êàáèíåòà: ");
			scanf("%d", &vibor);
			system("CLS");
			printf("=========================\n");
			printf("Êàáèíåò ¹ %d\n", vibor);
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
				printf("Íåò âðà÷åé\n");
				system("pause");
				break;
			}
			for (i = 0; i < 6; i++)
			{
				printf("[%d]%s\n", i + 1, spec[i]);
			}
			printf("Âûáåðèòå ñïåöèàëüíîñòü âðà÷à (1-6): ");
			flag = 0;
			do {
				if(flag)
					printf("Ââåäåíî íåïðàâèëüíîå çíà÷åíèå. Ââåäèòå îò 1 äî 6: ");
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
					printf("Ñïåöèàëüíîñòü: %s\n", current->spec);
					printf("Èìÿ: %s\n", current->name);
					printf("Êàáèíåò: %d\n", current->num);
					printf("Äåíü: %s\n", days[(current->day) - 1]);
					printf("Íà÷àëî/Êîíåö ïðèåìà: ñ %d äî %d\n", current->st_vis, current->end_vis);
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
