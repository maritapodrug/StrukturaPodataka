#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024
#define MAX_POINTS 15

typedef struct student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}student;

double relativepoints(double abs)
{
	return ((double)abs / MAX_POINTS) * 100;
}

int rowcounter()
{
	FILE* fp = NULL;
	char buffer[MAX_SIZE] = { 0 };
	int count = 0;

	fp = fopen("imena.txt", "r");

	if (fp == 0)
	{
		printf("File not opened!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_SIZE, fp);
		count++;
	}
	fclose(fp);

	return count;
}

student* memallocandreadstudents(int numrow) {
	FILE* fp = NULL;
	student* st = NULL;
	int count = 0;

	st = (student*)malloc(numrow * sizeof(student));

	if(!st)
	{
		printf("Failed to allocate memory!");
		return -1;
	}
	
	fp = fopen("imena.txt", "r");

	if (fp == NULL)
	{
		printf("File not opened!");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s %s %lf", st[count].name, st[count].surname, &st[count].points);
		count++;
	}

	fclose(fp);

	return st;
}

void printstudents(int number, student* st)
{
	int i;

	printf("NAME\tSURNAME\tABS POINTS\tRELATIVE POINTS\n");

	for (i = 0; i < number; i++)
		printf("%s\t%s\t%lf\t%lf\n", st[i].name, st[i].surname, st[i].points, relativepoints(st[i].points));

}

int main()
{
	int count = rowcounter();
	student* student=NULL;

	if (count > 0) {
		student = memallocandreadstudents(count);
		printstudents(count, student);
		free(student);
	}

	return 0;

}
