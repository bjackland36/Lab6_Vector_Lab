/**
Date: 9/29/2026
Author: Blake Ackland
Description:
Compile: gcc -Wall vector_functions.c vector_data.c vector_lab.c -o vector_lab
Run: ./vector_lab
*/
//printf("%c = %.2f, %.2f, %.2f\n", currentVector.name, currentVector.x, currentVector.y, currentVector.z);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector_functions.h"
#include "vector_data.h"
#include "vector.h"

int main()
{
    char user_input[80];
    char *token1;
    char *token2;
    char *token3;
    char *token4;
    char *token5;
    vector currentVector;
    printf("Welcome to the Vector Calculator!\nType '-h' to show commands\n");
    int active = 1;
    while(active)
    {
        printf("User>");
        fgets(user_input, 80, stdin);
        char *token1 = strtok(user_input, " ,\t\r\n");
        char *token2 = strtok(NULL, " ,\t\r\n");
        char *token3 = strtok(NULL, " ,\t\r\n");
        char *token4 = strtok(NULL, " ,\t\r\n");
        char *token5 = strtok(NULL, " ,\t\r\n");
        if(token1 != NULL)
        {
            if(strcmp(token1, "quit") == 0)
            {
                return 0;
            }

            else if(strcmp(token1, "-h") == 0)
            {
                printf("Type 'quit' to quit\nType 'list' to list vectors in memory\nType 'clear' to clear vector memory\n");
            }

            else if(strcmp(token1, "list") == 0)
            {
                listVect();
            }

            else if(strcmp(token1, "clear") == 0)
            {
                clearStorage();
                printf("Memory cleared\n");
            }
            
            else if (token2 == NULL)
            {
                currentVector = findVect(token1[0]);
                if (currentVector.name == '\0')
                {
                    printf("Vector '%c' not found.\n", token1[0]);
                }
                else
                {
                    printf("%c = %.2f, %.2f, %.2f\n",
                        currentVector.name,
                        currentVector.x,
                        currentVector.y,
                        currentVector.z);
                }
            }

            else if(strcmp(token2, "=") == 0)
            {
                char vectName = token1[0];
                char *endX;
                char *endY;
                char *endZ;
                double x = strtod(token3, &endX);
                double y = strtod(token4, &endY);
                double z = strtod(token5, &endZ);
                if (endX == token3 || *endX != '\0' || endY == token4 || *endY != '\0' || endZ == token5 || *endZ != '\0')
                {
                    printf("Invalid vector values, please try again.\n");
                }
                else
                {
                    vector newVect = (vector){ .name = vectName, .x = x, .y = y, .z = z};
                    addVect(newVect);
                }
            }

            else if(strcmp(token2, "+") == 0)
            {
                vector sum;
                vector vect1 = findVect(token1[0]);
                if (vect1.name == '\0')
                {
                    printf("Vector '%c' not found.\n", token1[0]);
                }
                vector vect2 = findVect(token3[0]);
                if (vect2.name == '\0')
                {
                    printf("Vector '%c' not found.\n", token3[0]);
                }
                else
                {
                    sum = add(vect1, vect2);
                    printf("(%c + %c) = %.2f, %.2f, %.2f\n", vect1.name, vect2.name, sum.x, sum.y, sum.z);
                }
            }

            else if(strcmp(token2, "-") == 0)
            {
                vector difference;
                vector vect1 = findVect(token1[0]);
                if (vect1.name == '\0')
                {
                    printf("Vector '%c' not found.\n", token1[0]);
                }
                vector vect2 = findVect(token3[0]);
                if (vect2.name == '\0')
                {
                    printf("Vector '%c' not found.\n", token3[0]);
                }
                else
                {
                    difference = sub(vect1, vect2);
                    printf("(%c - %c) = %.2f, %.2f, %.2f\n", vect1.name, vect2.name, difference.x, difference.y, difference.z);
                }
            }

            else if(strcmp(token2, "*") == 0)
            {
                vector product;
                char *endScalar;
                double scalar = strtod(token3, &endScalar);
                vector vect1 = findVect(token1[0]);
                if (vect1.name == '\0')
                {
                    printf("Vector '%c' not found.\n", token1[0]);
                }
                else
                {
                    product = mult(vect1, scalar);
                    printf("(%c * %.2f) = %.2f, %.2f, %.2f\n", vect1.name, scalar, product.x, product.y, product.z);
                }
            }
        }
    }
}