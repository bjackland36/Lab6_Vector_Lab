/**
File: vector_data.h
Author: Blake Ackland
Date: 9/29/2026
Description: Header file for vector_data.c
 */
 //Header guard
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H

#include "vector.h"

int addVect(vector new);
vector findVect(char name);
void clearStorage(void);
int getVectCount(void);
vector getVectAt(int index);

#endif