/*2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A.dinamièki dodaje novi element na poèetak liste,
B.ispisuje listu,
C.dinamièki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_LENGHT 100

struct _person;
typedef struct _person *position;
typedef struct _person {
	char name[MAX_LENGHT];
	char surname[MAX_LENGHT];
	int birthyear;
	position next;
}person;

position createperson();
position findlast(position head);
void appendlist(position head);
void menu(position head);
void printlist(position first);
void addtoend(position head);
void findperson(position head);
void printperson(position person);
void deleteperson(position head);
char* yoursurname();


int main(int argc, char **argv)
{
	person head = { .next = NULL,.name = {0},.surname = {0},.birthyear = 0 };
	menu(&head);
}

position createperson()
{
	position newperson = NULL;
	char name[MAX_LENGHT] = { 0 };
	char surname[MAX_LENGHT] = {0};
	int birthyear=0;

	newperson = (position)malloc(sizeof(person));

	if (newperson == 0)
	{
		printf("CANNOT ALLOCATE MEMORY!");
		return -1;
	}

	printf("Enter name:\n");
	scanf(" %s", name);
	printf("Enter surname:\n");
	scanf(" %s", surname);
	printf("Enter birth year:\n");
	scanf(" %d", &birthyear);

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthyear = birthyear;

	return newperson;
}

void appendlist(position head)
{
	position newperson = NULL;

	newperson = createperson();

	if (newperson)
	{
		newperson->next = head->next;
		head->next = newperson;
	}
}

void printlist(position first)
{
	if (!first)
		printf("ERROR!EMPTY LIST!");
	else
		for (; first != NULL; first = first->next)
		{
			printf("Name: %s\tSurname: %s\tBirthyear: %d\n", first->name, first->surname, first ->birthyear);
		}
}

position findlast(position head) {

	while (head->next != NULL)
		head = head->next;
	
	return head;
}

void addtoend(position head)
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

void printperson(position head)
{
	printf("Name: %s\tSurname: %s\tYear of birth: %d\n", head->name, head->surname, head->birthyear);
}

void findperson(position head)
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

void deleteperson(position head)
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
		if (head->next && strcmp(head->surname, surname) == NULL)
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

void menu(position head)
{
	char choice = '\0';
	while (1) {
		printf("Enter your choice:\n(a)Append list\n(b)Add to the end of the list\n(c)Search by surname\n(d)Delete person\n(e)Print list\n(x)Exit\n");
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
		case'x':
			break;
		default:printf("Wrong letter!");
			break;

		}
	}
}