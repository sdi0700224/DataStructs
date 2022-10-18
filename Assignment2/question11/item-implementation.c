#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#define RANDLIMIT 10000000


typedef struct ItemTag
{
    Key RegNum;
    String Name;
    String SurName;
}ItemNode;


Item ITEMrand(void)
{
    Item x;
    int n;

    n = rand() % RANDLIMIT;
    while(n <= 0)
    {
        n = rand() % RANDLIMIT;
    }
    x = malloc(sizeof(ItemNode));
    x->RegNum = n;
    x->Name = malloc(20*sizeof(char));
    strcpy(x->Name, "RandomName");
    x->SurName = malloc(20*sizeof(char));
    strcpy(x->SurName, "RandomSurname"); 
    return x; 
}


void ITEMscan(Item *Pointer)
{
    Item x;
    int i;
    char temp[20];

    x = malloc(sizeof(ItemNode));
    printf("\nPlese give Registration Number: \n");
    scanf("%d", &i);
    x->RegNum = i;
    for(int i=0; i<20; i++)
    {
        temp[i] = '\0';
    }
    printf("Plese give Student's name: \n");
    scanf("%s", temp);
    x->Name = malloc(20*sizeof(char));
    strcpy(x->Name, temp);
    for(int i=0; i<20; i++)
    {
        temp[i] = '\0';
    }
    printf("Plese give Student's surname: \n");
    scanf("%s", temp);
    x->SurName = malloc(20*sizeof(char));
    strcpy(x->SurName, temp);
    *Pointer = x;
    return;
}


void ITEMshow(Item Item)
{ 
    printf("Registration Number: %12d\t\t", Item->RegNum);
    printf("Name: %12s\t", Item->Name);
    printf("Surname: %12s\n", Item->SurName);
}


int GetKey(Item x)
{
    return x->RegNum;
}


void FreeItem(Item x)
{
    free(x->Name);
    free(x->SurName);
    free(x);
}