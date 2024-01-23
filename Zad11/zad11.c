#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 
#define MAX_SIZE 1024
#define HASH_SIZE 11

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

typedef struct _hash* HashPointer;

typedef struct _hash {

    countryPosition nextHashEl[HASH_SIZE];

}Hash;

int ReadFilecountry(countryPosition countryHead);
countryPosition CreateListNode(char* countryName);
cityPosition CreateTreeNode(char* cityName, int population);
cityPosition InsertSortTree(cityPosition cityRoot, int population, char* cityName);
int InsertSortList(countryPosition listHead, countryPosition newCity);
int PrintCountry(countryPosition countryHead);
cityPosition CityInorder(cityPosition cityRoot);
Hash CreateHash();
int CalculateHashKey(char* countryName);
int InsertCountryHash(Hash* hash, countryPosition newCountry, int key);
int PrintCountriesHash(Hash* hash);

int main() {

    country countryHead = { .countryName = {0}, .nextCountry = NULL, .cityRoot = NULL, .cityHead = NULL, .left = NULL, .right = NULL };
    country countryRoot = { .countryName = {0}, .nextCountry = NULL, .cityRoot = NULL, .cityHead = NULL, .left = NULL, .right = NULL };
    char countryName[MAX_SIZE] = { 0 };
    double population = 0;

    countryPosition hash = (countryPosition)malloc(sizeof(countryPosition) * 11);

    ReadFilecountry(&countryHead);

}

Hash CreateHash() {

    Hash hash;

    for (int i = 0; i < HASH_SIZE; i++)
        hash.nextHashEl[i] = NULL;

    return hash;

}
int CalculateHashKey(char* countryName) {

    int ascii = 0;
    int key = 0;

    for (int i = 0; i < 5; i++)
        ascii += countryName[i];

    key = ascii % HASH_SIZE;

    return key;

}

int InsertCountryHash(Hash* hash, countryPosition newCountry, int key) {


    if (hash->nextHashEl[key] == NULL)
        hash->nextHashEl[key] = newCountry;

    else
    {
        InsertSortList(hash->nextHashEl[key], newCountry);


    }
    return 0;

}

int PrintCountriesHash(Hash* hash) {

    countryPosition currentCountry = NULL;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        currentCountry = hash->nextHashEl[i];
        while (currentCountry != NULL)
        {
            printf("\n%s\n", currentCountry->countryName);
            CityInorder(currentCountry->cityRoot);
            currentCountry = currentCountry->nextCountry;
        }

    }
}

int ReadFilecountry(countryPosition countryHead) {

    FILE* countryAllFilepointer = NULL;
    FILE* countryFilepointer = NULL;
    char countryName[MAX_SIZE] = { 0 }, countryNameFile[MAX_SIZE] = { 0 }, cityName[MAX_SIZE] = { 0 }, strPopulation[MAX_SIZE] = { 0 };
    double population = 0;
    countryPosition newCountry;
    city cityRoot;
    int key = 0;
    Hash hash;

    hash = CreateHash();

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

        key = CalculateHashKey(countryName);

        if (InsertCountryHash(&hash, newCountry, key) != 0)
            return -1;


    }
    fclose(countryAllFilepointer);
    PrintCountriesHash(&hash);
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


int InsertSortList(countryPosition listHead, countryPosition newCountry) {

    countryPosition currentcountry = listHead;

    while (currentcountry->nextCountry != NULL && strcmp(currentcountry->nextCountry->countryName, newCountry->countryName) < 0)
        currentcountry = currentcountry->nextCountry;

    newCountry->nextCountry = currentcountry->nextCountry;
    currentcountry->nextCountry = newCountry;

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













