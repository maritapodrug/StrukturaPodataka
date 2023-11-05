/*3. Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_LENGHT 100

struct _person;
typedef struct _person* position;
typedef struct _person {
	char name[MAX_LENGHT];
	char surname[MAX_LENGHT];
	int birthyear;
	position next;
}person;

position createperson();
position findlast(position head);
position addperson(position newperson);
int appendlist(position head);
int menu(position head);
int printlist(position first);
int addtoend(position head);
int findperson(position head);
int printperson(position person);
int deleteperson(position head);
int addafter(position head);
int addbefore(position head);
int inputdat(position head);
int readdat();
char* yoursurname();


int main(int argc, char** argv)
{
	person head = { .next = NULL,.name = {0},.surname = {0},.birthyear = 0 };
	menu(&head);
}

position createperson()
{
	position newperson = NULL;
	char name[MAX_LENGHT] = { 0 };
	char surname[MAX_LENGHT] = { 0 };
	int birthyear = 0;

	newperson = (position)malloc(sizeof(person));

	if (newperson == 0)
	{
		printf("CANNOT ALLOCATE MEMORY!");
		return -1;
	}

	printf("Name, surname, year of birth:");
	scanf("%s %s %d", name, surname, &birthyear);

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthyear = birthyear;

	return newperson;
}

int appendlist(position head)
{
	position newperson = NULL;

	newperson = createperson();

	if (newperson)
	{
		newperson->next = head->next;
		head->next = newperson;
	}
}

int printlist(position first)
{
	if (!first)
		printf("ERROR!EMPTY LIST!");
	else
		for (; first != NULL; first = first->next)
		{
			printf("Name: %s\tSurname: %s\tBirthyear: %d\n", first->name, first->surname, first->birthyear);
		}
}

position findlast(position head) {

	while (head->next != NULL)
		head = head->next;

	return head;
}

int addtoend(position head)
{
	position newperson = NULL;

	newperson = createperson();

	if (newperson)
	{
		head = findlast(head);
		newperson->next = head->next;
		head->next = newperson;
	}
}

char* yoursurname()
{
	char surname[MAX_LENGHT] = { 0 };

	printf("Enter the surname that you are looking for:\n");
	scanf(" %s", surname);

	return surname;
}

int printperson(position head)
{
	printf("Name: %s\tSurname: %s\tYear of birth: %d\n", head->name, head->surname, head->birthyear);
}

int findperson(position head)
{

	char* surname = yoursurname();

	if (head->next)
	{
		while (head->next && strcmp(head->next->surname, surname) != NULL)
			head = head->next;

		if (head->next)
			printperson(head->next);
		else {
			printf("Cannot find the person with that surname.");
			return -1;
		}
	}
	else printf("Empty list!");
}

int deleteperson(position head)
{
	char* surname = yoursurname();

	if (head->next)
	{
		position previous = NULL;

		while (head->next && strcmp(head->surname, surname) != NULL)
		{
			previous = head;
			head = head->next;
		}
		if (head->next && strcmp(head->surname, surname) == 0)
		{
			printperson(head);
			previous->next = head->next;
			free(head);
			printf("Deleted!\n");
		}
		else
			printf("Cannot find the person with that surname!");
	}
}

int addbefore(position head)
{
	char sur[MAX_LENGHT] = {0};
	printf("Write surname of the person before who you want to add:\n");
	scanf("%s", sur);

	position newperson = NULL;
	newperson = addperson(newperson);

	while (head != NULL && head->next!=NULL)
	{
		if (strcmp(head->next->surname, sur) == 0)
		{
			newperson->next = head->next;
			head->next = newperson;
			break;
		}
		head = head->next;
	}
}

int addafter(position head)
{
	char sur[] = {0};
	printf("Write surname of the person after who you want do add:\n");
	scanf("%s", sur);

	position newperson = NULL;
	newperson = addperson(newperson);

	while (head != NULL && head->next!=NULL)
	{
		if(strcmp(head->next->surname,sur)==0)
		{
			newperson->next = head->next;
			head->next = newperson;
		}
		head = head->next;
	}
}

int inputdat(position head)
{
	FILE* fp;

	fp = fopen("list.txt", "w");

	if (fp == NULL)
	{
		return -1;
	}

	while (head->next != NULL)
	{
		head = head->next;
		fprintf(fp, "%s %s %d", head->name, head->surname, head->birthyear);
	}

	fclose(fp);
}

int readdat()
{
	person pers = { .name = {0},.surname = {0},.birthyear = 0,.next=NULL};
	FILE* fp;

	fp = fopen("list.txt", "r");

	if (fp == NULL)
	{
		return -1;
	}

	while (1)
	{
		fscanf(fp, "%s %s %d", pers.name, pers.surname, &pers.birthyear);

		if (feof(fp))
			break;

		printf("%s %s %d\n", pers.name, pers.surname, pers.birthyear);
	}
		
	fclose(fp);
}

position addperson(position newperson)
{
	char name[MAX_LENGHT] = { 0 };
	char surname[MAX_LENGHT] = { 0 };
	int birthyear = 0;

	newperson = (position)malloc(sizeof(person));

	if (newperson == 0)
	{
		printf("CANNOT ALLOCATE MEMORY!");
		return -1;
	}

	printf("Name, surname, year of birth:");
	scanf("%s %s %d", name, surname, &birthyear);

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthyear = birthyear;

	return newperson;
}

int menu(position head)
{
	char choice = '\0';
	while (1) {
		printf("Enter your choice:\n(a)Append list\n(b)Add to the end of the list\n(c)Search by surname\n(d)Delete person\n(e)Print list\n(f)Add before element\n(g)Add after element\n(h)Input in file\n(i)Read file\n(x)Exit\n");
		scanf(" %c", &choice);
		switch (tolower(choice))
		{
		case 'a':
			appendlist(head);
			break;
		case 'b':
			addtoend(head);
			break;
		case 'c':
			findperson(head);
			break;
		case 'd':
			deleteperson(head);
			break;
		case'e':
			printlist(head->next);
			break;
		case 'f':
			addbefore(head);
			break;
		case 'g':
			addafter(head);
			break;
		case 'h':
			inputdat(head);
			break;
		case 'i':
			readdat();
			break;
		case'x':
			return 0;
		default:printf("Wrong letter!");
			break;

		}
	}
}