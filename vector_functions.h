/**
File: vector_functions.h
Author: Blake Ackland
Date: 9/29/2026
Description: Header file for vector_functions.c
 */
 //Header guard
#ifndef VECTOR_FUNCTIONS_H
#define VECTOR_FUNCTIONS_H

#include "vector.h"

vector add(vector vector_1, vector vector_2);
vector sub(vector vector_1, vector vector_2);
double dot(vector vector_1, vector vector_2);
vector cross(vector vector_1, vector vector_2);
vector mult(vector vector, double scalar);

#endif