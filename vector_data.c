#include <stdio.h>
#include "vector.h"
#define MAX_VECTORS 10
static vector vectorStorage[MAX_VECTORS];
static int storageUsed;

void addVect(vector new)
{
    for (int i = 0; i < storageUsed; i++)
    {
        if (vectorStorage[i].name == new.name)
        {
            vectorStorage[i] = new;
            printf("Vector '%c' replaced!\n", new.name);
            return;
        }
    }
    if (storageUsed >= MAX_VECTORS)
    {
        printf("Vector storage full.\n");
        return;
    }
    vectorStorage[storageUsed] = new;
    storageUsed++;
    printf("Vector '%c' added!\n", new.name);
}

vector findVect(char name)
{
    for (int i = 0; i < storageUsed; i++)
    {
        if (vectorStorage[i].name == name)
        {
            return vectorStorage[i];
        }
    }
    return (vector){ .name = '\0', .x = 0.0, .y = 0.0, .z = 0.0 };
}

void clearStorage()
{
    storageUsed = 0;
}

void listVect()
{
    for (int i = 0; i < storageUsed; i++)
    {
        printf("%c = %.2f, %.2f, %.2f\n", vectorStorage[i].name, vectorStorage[i].x, vectorStorage[i].y, vectorStorage[i].z);
    }
}