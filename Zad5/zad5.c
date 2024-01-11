#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#define MAX 100

typedef struct stack* pos;
typedef struct stack {
	int n;
	pos next;
}stack;

int readfile();
int postfixcalc(char*);
void push(pos, int);
int pop(pos);
int empty(pos);
void ispis(pos);
pos addop(pos);
int operation(int, int, char, int*);
void print(char*, pos, int);

int main()
{
	readfile();

	return 0;
}

int pop(pos top) {

	pos temp = NULL;
	int a = 0;

	if (top->next == NULL) {
		printf("Stack is empty!\n");
		return -1;
	}

	temp = top->next;
	a = temp->n;

	top->next = temp->next;

	free(temp);

	return a;
}

void push(pos top, int a)
{
	pos new = NULL;

	new = addop(new);

	if (!new)
	{
		printf("Error!");
		return;
	}

	new->n = a;
	new->next = top->next;
	top->next = new;
}

pos addop(pos new)
{
	new = (pos)malloc(sizeof(stack));
	return new;
}

int empty(pos top)
{
	if (top->next == NULL)
		return 1;
	else return 0;
}

int postfixcalc(char* line)
{

	stack top = { .n = 0,.next = NULL };
	char operat = '\0';
	int val = 0, bytes = 0, count = 0;
	int operand = 0, operand1 = 0, operand2 = 0, result = 0;

	while (strlen(line + bytes) > 0)
	{
		val = sscanf(line + bytes, " %d %n", &operand, &count);

		if (val == 1)
		{
			bytes += count;
			push(&top, operand);
		}

		else if (val == 0)
		{
			val = sscanf(line + bytes, " %c %n", &operat, &count);
			bytes += count;
			if (val == 1)
			{
				operand2 = pop(&top);
				operand1 = pop(&top);

				operation(operand1, operand2, operat, &result);
				

				push(&top, result);
			}
		}
		else return -1;

		print(line + bytes, &top, result);
	}
	return 0;
}
int readfile()
{
	FILE* fp = NULL;
	char line[MAX];

	fp = fopen("postfix.txt", "r");

	if (!fp) {
		printf("Could not read file!");
		return -1;
	}

	fgets(line, MAX, fp);
	
	printf("%s\n", line);

	fclose(fp);

	postfixcalc(line);

	return 0;
}

int operation(int a, int b, char o, int* res)
{
	switch (o)
	{
	case '+':
		*res = a + b;
		break;
	case '-':
		*res = a - b;
		break;
	case '*':
		*res = a * b;
		break;
	case '/':
		*res = a / b;
		break;
	default:
		printf("Error!");
		return -1;
		break;
	}
	return 0;
}

void print(char* left, pos top, int res)
{
	pos temp = top->next;

	printf("U stogu: ");

	while (temp != NULL)
	{
		printf("%d ", temp->n);
		temp = temp->next;
	}
	printf("\nPreostalo: %s\n", left);

	
	printf("Rezultat: %d\n\n", res);
}