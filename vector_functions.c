/**
File: vector_functions.c
Author: Blake Ackland
Date: 9/29/2026
Description: Logic for vector math used in vector_lab. Functions: Add, subtract,
             scalar multiplication, dot product, and cross product. vector.h used
             for struct vector
 */
#include "vector_functions.h"
#include "vector.h"

//Adds two vectors and returns sum vector
vector add(vector vector_1, vector vector_2)
{
    vector returnVect;
    returnVect.x = vector_1.x + vector_2.x;
    returnVect.y = vector_1.y + vector_2.y;
    returnVect.z = vector_1.z + vector_2.z;
    return returnVect;
}

//Subtracts two vectors and returns difference vector
vector sub(vector vector_1, vector vector_2)
{
    vector returnVect;
    returnVect.x = vector_1.x - vector_2.x;
    returnVect.y = vector_1.y - vector_2.y;
    returnVect.z = vector_1.z - vector_2.z;
    return returnVect;
}

//Returns the dot product of two vectors
double dot(vector vector_1, vector vector_2)
{
    double returnVal;
    returnVal = (vector_1.x * vector_2.x) + (vector_1.y * vector_2.y) + (vector_1.z * vector_2.z);
    return returnVal;
}

//Returns the cross product of two vectors
vector cross(vector vector_1, vector vector_2)
{
    vector returnVect;
    returnVect.x = vector_1.y * vector_2.z - vector_1.z * vector_2.y;
    returnVect.y = vector_1.z * vector_2.x - vector_1.x * vector_2.z;
    returnVect.z = vector_1.x * vector_2.y - vector_1.y * vector_2.x;
    return returnVect;
}

//Multiplies a vector by a scalar and returns product vector
vector mult(vector vector_1, double scalar)
{
    vector returnVect;
    returnVect.name = vector_1.name;
    returnVect.x = vector_1.x * scalar;
    returnVect.y = vector_1.y * scalar;
    returnVect.z = vector_1.z * scalar;
    return returnVect;
}