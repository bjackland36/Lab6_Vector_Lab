/**
File: vector.h
Author: Blake Ackland
Date: 9/29/2026
Description: Defines struct vector. Gives a vector a name,
             x, y, and z values (xyz are doubles).
 */
//Header guard
#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector
{
    char name; //Only single character name supported
    double x;
    double y;
    double z;
} vector;

#endif