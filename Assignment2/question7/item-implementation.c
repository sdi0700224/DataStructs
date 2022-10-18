#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"


typedef struct ItemTag
{
    Key RegNum;
    String Name;
    String SurName;
}ItemNode;


Item ITEMrand(void) //Creates random item
{
    Item x;

    x = malloc(sizeof(ItemNode));
    x->RegNum = rand();
    x->Name = malloc(20*sizeof(char));
    strcpy(x->Name, "RandomName");
    x->SurName = malloc(20*sizeof(char));
    strcpy(x->SurName, "RandomSurname"); 
    return x; 
}


void ITEMscan(Item *Pointer)    //Reads item from user
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


void ITEMshow(Item Item)    //Prints item
{ 
    printf("Registration Number: %12d\t\t", Item->RegNum);
    printf("Name: %12s\t", Item->Name);
    printf("Surname: %12s\n", Item->SurName);
}

int GetKey(Item x)  //Get item's Key
{
    return x->RegNum;
}

void FreeItem(Item x)   //Frees item information
{
    free(x->Name);
    free(x->SurName);
    free(x);
}

Item ITEMgen(int a) //Generates item with specific Key
{
    Item x;

    x = malloc(sizeof(ItemNode));
    x->RegNum = a;
    x->Name = malloc(20*sizeof(char));
    strcpy(x->Name, "Name");
    x->SurName = malloc(20*sizeof(char));
    strcpy(x->SurName, "Surname"); 
    return x; 
}