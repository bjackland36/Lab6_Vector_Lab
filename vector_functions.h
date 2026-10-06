#ifndef VECTOR_FUNCTIONS_H
#define VECTOR_FUNCTIONS_H

#include "vector.h"

vector add(vector vector_1, vector vector_2);
vector sub(vector vector_1, vector vector_2);
double dot(vector vector_1, vector vector_2);
vector cross(vector vector_1, vector vector_2);
vector mult(vector vector, double scalar);

#endif