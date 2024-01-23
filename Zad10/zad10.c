#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 
#define MAX_SIZE 1024

typedef struct _city* cityPosition;

typedef struct _country* countryPosition;
typedef struct _country {

    char countryName[MAX_SIZE];
    countryPosition nextCountry;
    cityPosition cityRoot;
    cityPosition cityHead;
    countryPosition left;
    countryPosition right;

}country;

typedef struct _city {

    char cityName[MAX_SIZE];
    double population;
    cityPosition left;
    cityPosition right;
    cityPosition nextCity;

}city;

int ReadFilecountry(countryPosition countryHead);
int ReadFilecountry2(countryPosition countryRoot);
countryPosition CreateListNode(char* countryName);
cityPosition CreateListNode2(char* cityName, int population);
cityPosition CreateTreeNode(char* cityName, int population);
countryPosition CreateTreeNode2(char* countryName);
cityPosition InsertSortTree(cityPosition cityRoot, int population, char* cityName);
countryPosition InsertSortTree2(countryPosition countryRoot, countryPosition newCountry);
int InsertSortList(countryPosition listHead, countryPosition newCity);
int InsertSortList2(cityPosition listHead, char* cityName, double population);
int PrintCountry(countryPosition countryHead);
countryPosition CountryInorder(countryPosition countryRoot);
cityPosition CityInorder(cityPosition cityRoot);
int PrintCity(cityPosition cityHead);
cityPosition CityPopulation(cityPosition cityRoot, double population);
int FindCountry(countryPosition countryHead, char* countryName, double population);
countryPosition FindCountry2(countryPosition countryRoot, char* countryName, double population);
int CityPopulation2(cityPosition cityHead, double population);





int main() {

    country countryHead = { .countryName = {0}, .nextCountry = NULL, .cityRoot = NULL, .cityHead = NULL, .left = NULL, .right = NULL };
    country countryRoot = { .countryName = {0}, .nextCountry = NULL, .cityRoot = NULL, .cityHead = NULL, .left = NULL, .right = NULL };
    char countryName[MAX_SIZE] = { 0 };
    double population = 0;

    ReadFilecountry(&countryHead);
    PrintCountry(&countryHead);
    ReadFilecountry2(&countryRoot);
    CountryInorder(&countryRoot);

    printf("\nDržava, broj stanovnika: ");
    scanf("%s %lf", countryName, &population);
    FindCountry(&countryHead, countryName, population);

    FindCountry2(&countryRoot, countryName, population);

}

int ReadFilecountry(countryPosition countryHead) {

    FILE* countryAllFilepointer = NULL;
    FILE* countryFilepointer = NULL;
    char countryName[MAX_SIZE] = { 0 }, countryNameFile[MAX_SIZE] = { 0 }, cityName[MAX_SIZE] = { 0 }, strPopulation[MAX_SIZE] = { 0 };
    double population = 0;
    countryPosition newCountry;
    city cityRoot;


    countryAllFilepointer = fopen("drzave.txt", "r");
    if (!countryAllFilepointer)
        return -1;

    while (fscanf(countryAllFilepointer, "%s %s%*c", countryName, countryNameFile) == 2)
    {
        newCountry = CreateListNode(countryName);
        if (newCountry == NULL)
            return -1;

        countryFilepointer = fopen(countryNameFile, "r");

        while (fscanf(countryFilepointer, "%50[^,]%*c%s%*c", cityName, strPopulation) == 2) 
        {
            population = atof(strPopulation); 

            if (newCountry->cityRoot == NULL)
            {
                newCountry->cityRoot = CreateTreeNode(cityName, population);
                if (newCountry->cityRoot == NULL)
                    return -1;
            }
            else
            {
                if (InsertSortTree(newCountry->cityRoot, population, cityName) != newCountry->cityRoot)
                    return -1;
            }
        }
        fclose(countryFilepointer);
        InsertSortList(countryHead, newCountry);

    }
    fclose(countryAllFilepointer);
}

int ReadFilecountry2(countryPosition countryRoot) {

    FILE* countryAllFilepointer = NULL;
    FILE* countryFilepointer = NULL;
    char countryName[MAX_SIZE] = { 0 }, countryNameFile[MAX_SIZE] = { 0 }, cityName[MAX_SIZE] = { 0 }, strPopulation[MAX_SIZE] = { 0 };
    double population = 0;
    countryPosition newCountry = NULL;

    countryAllFilepointer = fopen("drzave.txt", "r");
    if (!countryAllFilepointer)
        return -1;

    while (fscanf(countryAllFilepointer, "%s %s%*c", countryName, countryNameFile) == 2)
    {
        if (strcmp(countryRoot->countryName, "\0") == 0)
        {
            strcpy(countryRoot->countryName, countryName);
            newCountry = countryRoot;
        }
        else
        {
            newCountry = CreateTreeNode2(countryName);
            if (!newCountry)
                return -1;

        }
        newCountry->cityHead = CreateListNode2("\0", 0);
        countryFilepointer = fopen(countryNameFile, "r");


        while (fscanf(countryFilepointer, "%50[^,]%*c%s%*c", cityName, strPopulation) == 2);
        {
            fscanf(countryFilepointer, "%s %s", cityName, strPopulation);
            population = atof(strPopulation);

            if (InsertSortList2(newCountry->cityHead, cityName, population) != 0)
                return -1;
        }

        fclose(countryFilepointer);
        if (countryRoot != newCountry)
            InsertSortTree2(countryRoot, newCountry);
    }
    fclose(countryAllFilepointer);

}

countryPosition CreateListNode(char* countryName) {

    countryPosition newCity = (countryPosition)malloc(sizeof(country));

    if (!newCity)
        return NULL;

    strcpy(newCity->countryName, countryName);  
    newCity->nextCountry = NULL;
    newCity->cityHead = NULL;
    newCity->cityRoot = NULL;
    newCity->left = NULL;
    newCity->right = NULL;

    return newCity;
}

cityPosition CreateListNode2(char* cityName, int population) {

    cityPosition newCity = (cityPosition)malloc(sizeof(city));

    if (!newCity)
        return NULL;

    strcpy(newCity->cityName, cityName);
    newCity->nextCity = NULL;
    newCity->population = population;
    newCity->left = NULL;
    newCity->right = NULL;

    return newCity;

}
cityPosition CreateTreeNode(char* cityName, int population) {

    cityPosition newCity = (cityPosition)malloc(sizeof(city));

    if (!newCity)
        return NULL;

    strcpy(newCity->cityName, cityName);
    newCity->population = population;
    newCity->left = NULL;
    newCity->right = NULL;

    return newCity;

}

countryPosition CreateTreeNode2(char* countryName) {

    countryPosition newCountry = (countryPosition)malloc(sizeof(country));

    if (!newCountry)
        return NULL;

    strcpy(newCountry->countryName, countryName);
    newCountry->cityRoot = NULL;
    newCountry->cityHead = NULL;
    newCountry->left = NULL;
    newCountry->right = NULL;

    return newCountry;
}


cityPosition InsertSortTree(cityPosition cityRoot, int population, char* cityName) {

    if (cityRoot == NULL)
        return CreateTreeNode(cityName, population);

    else if (population < cityRoot->population)
        cityRoot->left = InsertSortTree(cityRoot->left, population, cityName);

    else if (population > cityRoot->population)
        cityRoot->right = InsertSortTree(cityRoot->right, population, cityName);

    else
    {
        if (strcmp(cityName, cityRoot->cityName) < 0)
            cityRoot->left = InsertSortTree(cityRoot->left, population, cityName);
        else
            cityRoot->right = InsertSortTree(cityRoot->right, population, cityName);

    }

    return cityRoot;
}

countryPosition InsertSortTree2(countryPosition countryRoot, countryPosition newCountry) {

    if (countryRoot == NULL)
        return newCountry;

    else if (strcmp(newCountry->countryName, countryRoot->countryName) < 0)
        countryRoot->left = InsertSortTree2(countryRoot->left, newCountry);

    else if (strcmp(newCountry->countryName, countryRoot->countryName) > 0)
        countryRoot->right = InsertSortTree2(countryRoot->right, newCountry);

    return countryRoot;

}


int InsertSortList(countryPosition listHead, countryPosition newCity) {

    countryPosition currentcountry = listHead;

    while (currentcountry->nextCountry != NULL && strcmp(currentcountry->nextCountry->countryName, newCity->countryName) < 0)
        currentcountry = currentcountry->nextCountry;

    newCity->nextCountry = currentcountry->nextCountry;
    currentcountry->nextCountry = newCity;

    return 0;

}

int InsertSortList2(cityPosition CityHead, char* cityName, double population) {

    cityPosition currentCity = CityHead;
    cityPosition newCity = CreateListNode2(cityName, population);
    if (!newCity)
        return -1;

    while (currentCity->nextCity != NULL && currentCity->nextCity->population < newCity->population)
        currentCity = currentCity->nextCity;

    newCity->nextCity = currentCity->nextCity;
    currentCity->nextCity = newCity;

    return 0;
}

int PrintCountry(countryPosition countryHead) {

    countryPosition currentCountry = countryHead->nextCountry;

    while (currentCountry != NULL)
    {
        printf("%s\n", currentCountry->countryName);
        CityInorder(currentCountry->cityRoot);
        printf("\n");
        currentCountry = currentCountry->nextCountry;
    }

}

cityPosition CityInorder(cityPosition cityRoot) {

    if (cityRoot == NULL)
        return cityRoot;

    CityInorder(cityRoot->left);
    printf("- %s\n", cityRoot->cityName);
    CityInorder(cityRoot->right);
}

countryPosition CountryInorder(countryPosition countryRoot) {

    if (countryRoot == NULL)
        return countryRoot;

    CountryInorder(countryRoot->left);
    printf("\n");
    printf("%s\n", countryRoot->countryName);
    PrintCity(countryRoot->cityHead);
    CountryInorder(countryRoot->right);
}

int PrintCity(cityPosition cityHead) {

    cityPosition currentCity = cityHead->nextCity;

    while (currentCity != NULL)
    {
        printf("%s\n", currentCity->cityName);
        currentCity = currentCity->nextCity;
    }
}

int FindCountry(countryPosition countryHead, char* countryName, double population) {

    countryPosition currentCountry = countryHead->nextCountry;

    while (currentCountry != NULL && strcmp(currentCountry->countryName, countryName) != 0)
        currentCountry = currentCountry->nextCountry;

    if (currentCountry != NULL && strcmp(currentCountry->countryName, countryName) == 0)
    {
        printf("\n%s\n", currentCountry->countryName);
        CityPopulation(currentCountry->cityRoot, population);

    }
}

cityPosition CityPopulation(cityPosition cityRoot, double population) {

    if (cityRoot == NULL)
        return cityRoot;

    CityPopulation(cityRoot->left, population);
    if (cityRoot->population > population)
        printf("-%s\n", cityRoot->cityName);
    CityPopulation(cityRoot->right, population);

}

countryPosition FindCountry2(countryPosition countryRoot, char* countryName, double population) {

    if (countryRoot == NULL)
        return countryRoot;

    FindCountry2(countryRoot->left, countryName, population);
    if (strcmp(countryRoot->countryName, countryName) == 0)
    {
        printf("-%s\n", countryRoot->countryName);
        CityPopulation2(countryRoot->cityHead, population);
    }
    FindCountry2(countryRoot->right, countryName, population);
}

int CityPopulation2(cityPosition cityHead, double population) {
    cityPosition currentCity = cityHead->nextCity;

    while (currentCity != NULL)
    {
        if (currentCity->population > population)
            printf("\n%s\n", currentCity->cityName);

        currentCity = currentCity->nextCity;
    }
}