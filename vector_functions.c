#include "vector_functions.h"
#include "vector.h"

vector add(vector vector_1, vector vector_2)
{
    vector returnVect;
    returnVect.x = vector_1.x + vector_2.x;
    returnVect.y = vector_1.y + vector_2.y;
    returnVect.z = vector_1.z + vector_2.z;
    return returnVect;
}

vector sub(vector vector_1, vector vector_2)
{
    vector returnVect;
    returnVect.x = vector_1.x - vector_2.x;
    returnVect.y = vector_1.y - vector_2.y;
    returnVect.z = vector_1.z - vector_2.z;
    return returnVect;
}

double dot(vector vector_1, vector vector_2)
{
    double returnVal;
    returnVal = (vector_1.x * vector_2.x) + (vector_1.y * vector_2.y) + (vector_1.z * vector_2.z);
    return returnVal;
}

vector cross(vector vector_1, vector vector_2)
{
    vector returnVect;
    returnVect.x = vector_1.y * vector_2.z - vector_1.z * vector_2.y;
    returnVect.y = vector_1.z * vector_2.x - vector_1.x * vector_2.z;
    returnVect.z = vector_1.x * vector_2.y - vector_1.y * vector_2.x;
    return returnVect;
}

vector mult(vector vector_1, double scalar)
{
    vector returnVect;
    returnVect.name = vector_1.name;
    returnVect.x = vector_1.x * scalar;
    returnVect.y = vector_1.y * scalar;
    returnVect.z = vector_1.z * scalar;
    return returnVect;
}