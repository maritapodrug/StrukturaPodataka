/*2. Definirati strukturu osoba (ime, prezime, godina ro?enja) i napisati program koji:
A.dinami?ki dodaje novi element na po?etak liste,
B.ispisuje listu,
C.dinami?ki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odre?eni element iz liste,
U zadatku se ne smiju koristiti globalne varijable

3. Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>
#include<string.h>
#define MAX_LENGTH 100

typedef struct person* pos;
typedef struct person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int year;
	pos next;
}person;

void menu(pos);
void appendlist(pos);
pos createnewperson();
void printlist(pos);
void addtoend(pos);
void findbysurname(pos);
void deleteelement(pos);
void addafter(pos);
void addbefore(pos);
void printtofile(pos);
void readfile();

int main()
{
	person head = { .name = {0},.surname = {0},.year = 0,.next = NULL };
	menu(&head);
	return 0;
}

pos createnewperson()
{
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int year = 0;
	pos newperson = NULL;

	newperson = (pos)malloc(sizeof(person));

	if (!newperson)
	{
		printf("Memory unavailable!");
		return -1;
	}

	printf("Unesite ime,prezime,godinu rodenja:");
	scanf("%s %s %d", name, surname, &year);

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->year = year;

	return newperson;
}

void appendlist(pos head)
{
	pos newperson = NULL;
	pos temp = head;

	newperson = createnewperson();

	if (newperson)
	{
		while (temp->next != NULL)
			temp = temp->next;

		newperson->next = temp->next;
		temp->next = newperson;
	}
}

void printlist(pos head)
{
	if (head->next == NULL)
	{
		printf("Empty list!");
		return -1;
	}

	pos temp = head->next;

	while (temp != NULL)
	{
		printf("%s %s %d\n", temp->name, temp->surname, temp->year);
		temp = temp->next;
	}
}

void addtoend(pos head)
{
	pos temp = head->next;
	pos newperson;

	while (temp->next != NULL)
		temp = temp->next;

	newperson = createnewperson();

	newperson->next = temp->next;
	temp->next = newperson;
}

void findbysurname(pos head)
{
	char sur[MAX_LENGTH];
	pos temp = head->next;

	printf("Wanted surname:");
	scanf("%s", sur);

	while (temp != NULL)
	{
		if (!strcmp(temp->surname, sur))
			printf("Person found!\n%s %s %d\n", temp->name, temp->surname, temp->year);
		temp = temp->next;
	}
}

void deleteelement(pos head)
{
	char sur[MAX_LENGTH];
	pos temp = head->next;
	pos prev = head;

	printf("Surname to delete:");
	scanf("%s", sur);

	while (temp != NULL)
	{
		if (!strcmp(temp->surname, sur))
		{
			prev->next = temp->next;
			printf("Person found!%s %s %d deleted!\n", temp->name, temp->surname, temp->year);
			free(temp);
			return;
		}
		temp = temp->next;
		prev = prev->next;
	}
}

void addafter(pos head)
{
	char sur[MAX_LENGTH];
	pos temp = head->next;
	pos newperson = NULL;

	printf("Add after surname:");
	scanf("%s", sur);

	newperson = createnewperson();

	while (temp != NULL)
	{
		if (!strcmp(temp->surname, sur))
		{
			newperson->next = temp->next;
			temp->next = newperson;
			printf("Person added!\n");
			return;
		}
		temp = temp->next;
	}
}

void addbefore(pos head)
{
	char sur[MAX_LENGTH];
	pos temp = head->next;
	pos prev = head;
	pos newperson;

	printf("Add before surname:");
	scanf("%s", sur);

	newperson = createnewperson();


	while (temp != NULL)
	{
		if (!strcmp(temp->surname, sur))
		{
			newperson->next = temp;
			prev->next = newperson;
			printf("Person added!\n");
			return;
		}
		temp = temp->next;
		prev = prev->next;
	}
}

void printtofile(pos head)
{
	FILE* fp = NULL;
	pos temp = head->next;

	fp = fopen("imena.txt", "w");

	if (fp == 0)
	{
		printf("File not opened!");
		return -1;
	}

	fprintf(fp, "NAME\tSURNAME\tYEAR\n");

	while (temp != NULL) {
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->year);
		temp = temp->next;
	}

	printf("Successfully printed to file!\n");

	fclose(fp);
}

void readfile()
{
	FILE* fp = NULL;
	person pers = { .name = {0},.surname = {0},.year = 0 };
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	char year[MAX_LENGTH];

	fp = fopen("imena.txt", "r");

	if (fp == 0)
	{
		printf("File not opened!");
		fclose(fp);
		return;
	}

	fscanf(fp, "%s %s %s", name, surname, year);
	printf("%s\t%s\t%s\n", name, surname, year);

	while (1)
	{
		fscanf(fp, "%s %s %d", pers.name, pers.surname, &pers.year);

		if (feof(fp))
			break;

		printf("%s %s %d\n", pers.name, pers.surname, pers.year);
	}
	fclose(fp);
}

void menu(pos head)
{
	char choice;
	while (1) {
		printf("A - Append list\nB - Print list\nC - Add to end\nD - Find by surname\nE - Delete element\nF - Add after\nG - Add before\nH - Print list to file\nI - Read file\nX - Exit menu\n\n");
		scanf(" %c", &choice);

		switch (tolower(choice)) {
		case 'a':
			appendlist(head);
			break;
		case'b':
			printlist(head);
			break;
		case 'c':
			addtoend(head);
			break;
		case 'd':
			findbysurname(head);
			break;
		case 'e':
			deleteelement(head);
			break;
		case 'f':
			addafter(head);
			break;
		case 'g':
			addbefore(head);
			break;
		case 'h':
			printtofile(head);
			break;
		case 'i':
			readfile(head);
			break;
		case 'x':
			return;
			break;
		default:
			printf("Wrong letter!\n");
			break;
		}
	}
	return 0;
}