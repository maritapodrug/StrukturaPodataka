/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 100

typedef struct el* pos;
typedef struct el{
	int n;
	int e;
	pos next;
}el;

int readfile(pos,pos);
int separate(char*, pos);
int printpol(pos);
int multiplypol(pos, pos, pos);
int sumpol(pos, pos, pos);
pos addel(pos, int, int);
int inputsort(pos, pos);
int freepol(pos, pos);
int deleteel(pos);
int addend(pos,pos);

int main()
{
	el head1 = { .n = 0,.e = 0,.next = NULL };
	el head2 = { .n = 0,.e = 0,.next = NULL };
	el headmul = { .n = 0,.e = 0,.next = NULL };
	el headsum = { .n = 0,.e = 0,.next = NULL };

	readfile(&head1, &head2);

	printpol(&head1);
	printf("\n");
	printpol(&head2);

	multiplypol(&head1, &head2, &headmul);
	printf("\n");

	printpol(&headmul);
	printf("\n");

	sumpol(&head1, &head2, &headsum);
	printpol(&headsum);

	freepol(&head1, &head2);
	return 0;
}

int sumpol(pos head1, pos head2, pos headsum)
{
	pos temp1 = head1->next;
	pos temp2 = head2->next;
	int sumcoef = 0;

	while (temp1 != NULL && temp2 != NULL)
	{
		if (temp1->e == temp2->e)
		{
			sumcoef = temp1->n + temp2->n;
			if (sumcoef != 0)
				addel(headsum, sumcoef, temp1->e);

			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->e > temp2->e)
		{
			addel(headsum, temp1->n, temp1->e);
			temp1 = temp1->next;
		}
		else
		{
			addel(headsum, temp2->n, temp2->e);
			temp2 = temp2->next;
		}
	}

	while (temp1 != NULL)
	{
		addel(headsum, temp1->n, temp1->e);
		temp1 = temp1->next;
	}

	while (temp2 != NULL)
	{
		addel(headsum, temp2->n, temp2->e);
		temp2 = temp2->next;
	}
	return 0;
}

int multiplypol(pos head1, pos head2, pos headmul)
{
	pos temp1 = head1->next;
	pos temp2 = head2->next;
	pos newel = NULL;
	int mulcoef = 0, mulpot = 0;

	while (temp1 != NULL)
	{
		while (temp2 != NULL)
		{
			mulcoef = temp1->n * temp2->n;
			mulpot = temp1->e + temp2->e;
			newel = addel(headmul, mulcoef, mulpot);

			temp2 = temp2->next;
		}
		temp1 = temp1->next;
		temp2 = head2->next;
	}
	return 0;
}

int readfile(pos head1, pos head2)
{
	FILE* fp = NULL;
	char line[MAX_LINE];
	int coef = 0, pot = 0;

	fp = fopen("polinomi.txt", "r");

	if (fp == NULL)
	{
		printf("File not opened!");
		return -1;
	}

	fgets(line, MAX_LINE, fp);
	separate(line, head1);
	fgets(line, MAX_LINE, fp);
	separate(line, head2);
	printf("\n");

	fclose(fp);
	return 0;
}

int separate(char* line, pos head)
{
	int coef = 0, pot = 0, val = 0, count = 0;

	while (sscanf(line + count, "%dx^%d %n", &coef, &pot, &val) == 2)
	{
		count += val;

		addel(head, coef, pot);
	}

	return 0;
}


pos addel(pos head, int coef, int pot)
{
	pos new = NULL;

	new = (pos)malloc(sizeof(el));

	if (new == NULL)
	{
		printf("Could not allocate memory!");
		return 0;
	}

	new->n = coef;
	new->e = pot;

	inputsort(head, new);

	return new;
}

int inputsort(pos head, pos new)
{
	pos current = head;

	if (!new)
		return -1;

	while (current->next != NULL && current->next->e > new->e)
		current = current->next;

	if (current->next != NULL)
	{
		if (current->next->e < new->e)
			addend(current, new);

		else
		{
			current->next->n += new->n;
			free(new);

			if (current->next->n == 0)
				deleteel(head);
		}
	}
	else
		addend(current, new);
	return 0;
}

int addend(pos current, pos new)
{
	if (current->next == NULL)
	{
		new->next = NULL;
		current->next = new;
	}
	else {
		new->next = current->next;
		current->next = new;
	}
	return 0;
}

int deleteel(pos head)
{
	pos current = head;
	pos temp = NULL;

	while (current != NULL && current->next != NULL && current->next->n != 0)
		current = current->next;

	if (current->next->n == 0)
	{
		temp = current->next;
		current->next = current->next->next;
		free(temp);
	}
	return 0;
}

int freepol(pos head1, pos head2)
{
	pos current1 = head1->next;
	pos current2 = head2->next;
	pos temp = NULL;

	while (current1 != NULL)
	{
		temp = current1;
		current1 = current1->next;
		free(temp);
	}

	while (current2 != NULL)
	{
		temp = current2;
		current2 = current2->next;
		free(temp);
	}
	return 0;
}

int printpol(pos head) 
{
	pos temp = head->next;

	while (temp != NULL)
	{
		printf("%dx^%d ", temp->n, temp->e);
		temp = temp->next;
	}
	return 0;
}

