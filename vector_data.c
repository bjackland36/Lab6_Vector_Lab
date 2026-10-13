/**
File: vector_data.c
Author: Blake Ackland
Date: 9/29/2026
Description: Vector storage/memory management. Allows for adding a vector to memory,
             clearing vector memory, find a vector in memory from its name, find how
             much of vector memory is used, and find vector based on its position in
             memory.
 */
#include "vector_data.h"

//Constant for 10 maximum vectors
#define MAX_VECTORS 10

//Static to avoid global variables while giving vector_data.c shared vars
static vector vectorStorage[MAX_VECTORS]; //vector storage space
static int storageUsed; //count of how much storage is used

//Adds a vector to the storage space
//Returns:
//0 = not added
//1 = new storage space used & vector added
//2 = existing vector replaced
int addVect(vector new)
{
    for (int i = 0; i < storageUsed; i++)
    {
        if (vectorStorage[i].name == new.name)
        {
            vectorStorage[i] = new;
            return 2;
        }
    }
    if (storageUsed >= MAX_VECTORS)
    {
        return 0;
    }
    vectorStorage[storageUsed] = new;
    storageUsed++;
    return 1;
}

//Finds vector values in storage based on name
//Returns vector with name '\0' if cannot find
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

//Clears vector storage storage
void clearStorage(void)
{
    storageUsed = 0;
}

//Returns number of vectors in storage
int getVectCount(void)
{
    return storageUsed;
}

//Returns vector based on memory index
vector getVectAt(int index)
{
    if (index < 0 || index >= storageUsed)
    {
        return (vector){ .name = '\0', .x = 0.0, .y = 0.0, .z = 0.0 };
    }

    return vectorStorage[index];
}