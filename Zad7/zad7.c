/*7. Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_LENGTH 100
#define _CRT_SECURE_NO_WARNINGS

typedef struct directory* posdirectory;
typedef struct directory {
	char name[MAX_LENGTH];
	posdirectory subdir;
	posdirectory nextdir;
}directory;

typedef struct stack* posstack;
typedef struct stack {
	posdirectory currentdir;
	posstack nextstack;
}stack;

int menu(posdirectory, posstack);
int makedirectory(posdirectory, posstack);
int changedirectory(posdirectory, posstack);
void push(posdirectory, posstack);
posdirectory pop(posdirectory, posstack);
int printdirectories(posdirectory, posstack);

int main()
{
	directory directoryhead = { .name = {0},.subdir = NULL,.nextdir = NULL };
	stack stackhead = { .currentdir = NULL,.nextstack = NULL };
	posstack new;

	new = (posstack)malloc(sizeof(stack));

	new->currentdir = &directoryhead;
	new->nextstack = NULL;
	(&stackhead)->nextstack = new;

	menu(&directoryhead, &stackhead);

	free(new);

	return 0;
}

int makedirectory(posdirectory dirhead, posstack sthead)
{
	posdirectory newdir;
	posdirectory currentdir;
	char name[MAX_LENGTH] = {0};

	printf("Ime direktorija: ");
	scanf(" %s", name);

	currentdir = sthead->nextstack->currentdir;

	if (!currentdir)
	{
		printf("Error!");
		return -1;
	}

	newdir = (posdirectory)malloc(sizeof(directory));

	strcpy(newdir->name, name);
	newdir->subdir = NULL;
	newdir->nextdir = NULL;

	if (currentdir->subdir == NULL)
		currentdir->subdir = newdir;
	else
	{
		currentdir = currentdir->subdir;

		while (currentdir->nextdir != NULL && strcmp(currentdir->name, name) != 0)
			currentdir = currentdir->nextdir;

		newdir->nextdir = currentdir->nextdir;
		currentdir->nextdir = newdir;
	}
	return 0;
}

int changedirectory(posdirectory dirhead, posstack sthead)
{
	posdirectory currentdir;
	char name[MAX_LENGTH] = { 0 };

	printf("Ime direktorija: ");
	scanf(" %s", name);

	currentdir = sthead->nextstack->currentdir->subdir;

	while (currentdir != NULL && strcmp(currentdir->name, name) != 0)
		currentdir = currentdir->nextdir;

	if (currentdir != NULL)
		push(currentdir, sthead);
	else
		printf("\nDirektorij ne postoji!\n");

	return 0;

}

void push(posdirectory currentdir, posstack sthead)
{
	posstack new;

	new = (posstack)malloc(sizeof(stack));

	new->currentdir = currentdir;
	new->nextstack = sthead->nextstack;
	sthead->nextstack = new;
}

posdirectory pop(posdirectory dirhead, posstack sthead)
{
	posdirectory currentd = NULL;
	posstack temps = NULL;

	if (sthead->nextstack->currentdir == dirhead)
		return dirhead;
	else
	{
		temps = sthead->nextstack;
		currentd = temps->currentdir;
		sthead->nextstack = sthead->nextstack->nextstack;

		free(temps);

		return currentd;
	}

}

int printdirectories(posdirectory dir, posstack sthead)
{
	posdirectory currentd;

	currentd = sthead->nextstack->currentdir;

	if (!currentd)
	{
		printf("Error!");
		return -1;
	}

	currentd = currentd->subdir;

	while (currentd != NULL)
	{
		printf("%s\n", currentd->name);
		currentd = currentd->nextdir;
	}
	return 0;
}

int menu(posdirectory dirhead, posstack sthead)
{
	char choice;
	char name[MAX_LENGTH] = { 0 };
	posdirectory currentdir = NULL;

	while (1)
	{
		printf("\nA - md (Create directory)\nB - cd dir (Change directory)\nC - cd.. (Go up)\nD - dir (List contents)\nE - exit\n");
		scanf(" %c", &choice);

		switch (tolower(choice))
		{
		case 'a':
			makedirectory(dirhead, sthead);
			break;
		case 'b':
			changedirectory(dirhead, sthead);
			break;
		case 'c':
			pop(dirhead, sthead);

			currentdir = sthead->nextstack->currentdir;

			if (!currentdir)
			{
				printf("Error!");
				return -1;
			}

			if (currentdir == dirhead)
				printf("Nalazite se u root direktoriju.");
			else
				printf("Nalazite se u %s direktoriju.\n", currentdir->name);

			break;
		case'd':
			printdirectories(dirhead, sthead);
			break;
		case 'e':
			return 0;
		default:
			printf("Error!");
			break;
		}
	}
	return 0;
}
