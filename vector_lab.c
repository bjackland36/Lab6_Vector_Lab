/**
File: vector_lab.c
Date: 9/29/2026
Author: Blake Ackland
Description: Main runnable program for vector calculator. If ran with command-line argument '-h',
             the program will display a summary of usage before running. Handles all console IO.
             Prompts user and loops until 'quit' command is entered. Allows for adding & subtracting
             vectors as well as taking the dot and cross product between them. Additionally, scalar 
             multiplication of a vector. Uses the struct vector from vector.h and organizes multiple
             vector data in vector_data. Vector math defined in vector_functions.
Compile: gcc -Wall vector_functions.c vector_data.c vector_lab.c -o vector_lab
Run: ./vector_lab
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vector_functions.h"
#include "vector_data.h"
#include "vector.h"

//Take args to allow for '-h' command-line argument
int main(int argc, char *argv[])
{
    //Summarize usage when -h is an argument
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        printf("Usage of vector_lab:\n");
        printf("Enter vector commands such as 'a = 1 2 3' or 'a + b'\n");
        printf("Commands: -h, quit, list, clear\n\n");
    }

    //Print welcome message
    printf("Welcome to the Vector Calculator!\n");
    printf("Type '-h' to show commands\n\n");

    //Initialize variables
    char user_input[80];
    char *token1;
    char *token2;
    char *token3;
    char *token4;
    char *token5;
    vector currentVector;

    int active = 1;

    while (active)
    {
        //Prompt user
        printf("User> ");

        //get user input and check for read errors
        if (fgets(user_input, sizeof user_input, stdin) == NULL)
        {
            return 0; //End program if read errors
        }

        //When read is successful
        else
        {
            //Separate the input into tokens
            token1 = strtok(user_input, " ,\t\r\n");
            token2 = strtok(NULL, " ,\t\r\n");
            token3 = strtok(NULL, " ,\t\r\n");
            token4 = strtok(NULL, " ,\t\r\n");
            token5 = strtok(NULL, " ,\t\r\n");

            //Only handle input if the user typed chars
            if (token1 != NULL)
            {
                //Quit command
                if (strcmp(token1, "quit") == 0)
                {
                    active = 0; //End program
                }

                //Show the help commands
                else if (strcmp(token1, "-h") == 0)
                {
                    printf("Type 'quit' to quit\n");
                    printf("Type 'list' to list vectors in memory\n");
                    printf("Type 'clear' to clear vector memory\n");
                    printf("Use 'a + b', 'a - b', 'a * 2', '2 * a', 'a dot b', or 'a cross b'\n");
                    printf("Assignments: 'a = 1 2 3', 'a = b', 'a = b + c', or 'a = 2 * b'\n");
                }

                //List the vectors in memory
                else if (strcmp(token1, "list") == 0)
                {
                    int vectorCount = getVectCount();
                    
                    //If vector storage empty
                    if (vectorCount == 0)
                    {
                        printf("Vector storage is empty.\n");
                    }

                    //If storage not empty
                    else
                    {
                        for (int i = 0; i < vectorCount; i++)
                        {
                            currentVector = getVectAt(i);
                            printf("%c = %.2f, %.2f, %.2f\n", currentVector.name, currentVector.x, currentVector.y, currentVector.z);
                        }
                    }
                }

                //Clear the vector storage
                else if (strcmp(token1, "clear") == 0)
                {
                    clearStorage();
                    printf("Vector storage cleared\n");
                }

                //Display a vector by name
                else if (token2 == NULL)
                {
                    //Check if token 1 is 1 character
                    if (token1[1] == '\0')
                    {
                        currentVector = findVect(token1[0]);

                        if (currentVector.name == '\0') //findVect returned '\0' vector so it is not in storage
                        {
                            printf("Vector '%c' not found.\n", token1[0]);
                        }
                        else
                        {
                            printf("%c = %.2f, %.2f, %.2f\n", currentVector.name, currentVector.x, currentVector.y, currentVector.z);
                        }
                    }

                    //If not 1 character, print error
                    else
                    {
                        printf("Command not found. Type -h for commands.\n");
                    }
                }

                //Handle equality commands
                else if (strcmp(token2, "=") == 0)
                {
                    //Check if name is 1 character
                    if (token1[1] != '\0')
                    {
                        printf("Vector names must be one character.\n");
                    }

                    //Always needs a token3 so print error
                    else if (token3 == NULL)
                    {
                        printf("Use the form 'a = 1 2 3' or 'a = b'.\n");
                    }

                    //Check if there is an operator at token 4
                    else if (token4 != NULL && (strcmp(token4, "+") == 0 || strcmp(token4, "-") == 0))
                    {
                        //Check token3 is >1 char or token 5 is not there or token 5 is >1 char
                        if (token3[1] != '\0' || token5 == NULL || token5[1] != '\0')
                        {
                            printf("Use a vector expression such as 'a = b + c'.\n");
                        }

                        //Otherwise syntax is good
                        else
                        {
                            vector vect1 = findVect(token3[0]);
                            vector vect2 = findVect(token5[0]);

                            //Check that each vector exists
                            if (vect1.name == '\0')
                            {
                                printf("Vector '%c' not found.\n", token3[0]);
                            }
                            else if (vect2.name == '\0')
                            {
                                printf("Vector '%c' not found.\n", token5[0]);
                            }
                            
                            //If vectors do exist
                            else
                            {
                                vector newVect;

                                //Add if +, subtract if -
                                if (strcmp(token4, "+") == 0)
                                {
                                    newVect = add(vect1, vect2);
                                }
                                else
                                {
                                    newVect = sub(vect1, vect2);
                                }

                                newVect.name = token1[0];
                                int result = addVect(newVect);

                                //Handle addVect rejection
                                if (result == 0)
                                {
                                    printf("Vector was not added. Vector storage is full.\n");
                                }

                                //Display if vector was added or replaced
                                else
                                {
                                    if (result == 1)
                                    {
                                        printf("Vector '%c' added!\n", newVect.name);
                                    }
                                    else
                                    {
                                        printf("Vector '%c' replaced!\n", newVect.name);
                                    }

                                    printf("%c = %.2f, %.2f, %.2f\n", newVect.name, newVect.x, newVect.y, newVect.z);
                                }
                            }
                        }
                    }

                    //Multiplication operator in equality command
                    //Check for null because strcmp might crash the program if token4 is null
                    else if (token4 != NULL && strcmp(token4, "*") == 0)
                    {
                        if (token5 == NULL)
                        {
                            printf("Use the form 'a = b * 4' or 'a = 4 * b'.\n");
                        }
                        else
                        {
                            //Check if 1 number and 1 scalar
                            char *endFirst;
                            char *endLast;
                            double firstValue = strtod(token3, &endFirst);
                            int firstIsNumber;
                            
                            //Check if first argument after = is a number
                            if (endFirst != token3 && *endFirst == '\0')
                            {
                                firstIsNumber = 1;
                            }
                            else
                            {
                                firstIsNumber = 0;
                            }
                            vector sourceVect;
                            double scalar;
                            int valid = 1;

                            //token3 is a number
                            if (firstIsNumber)
                            {
                                if (token5[1] != '\0')
                                {
                                    printf("The value after * must be a one-character vector name.\n");
                                    valid = 0;
                                }
                                else
                                {
                                    sourceVect = findVect(token5[0]);
                                    scalar = firstValue;
                                }
                            }

                            //token3 is not 1 character
                            else if (token3[1] != '\0')
                            {
                                printf("Use a one-character vector name.\n");
                                valid = 0;
                            }

                            //Token3 is a single character
                            else
                            {
                                sourceVect = findVect(token3[0]);
                                scalar = strtod(token5, &endLast);

                                //token5 must be a number
                                if (endLast == token5 || *endLast != '\0')
                                {
                                    printf("The value after * must be a number.\n");
                                    valid = 0;
                                }
                            }

                            //Check valid syntax
                            if (valid)
                            {
                                //Check vector exists
                                if (sourceVect.name == '\0')
                                {
                                    printf("Source vector not found.\n");
                                }

                                //If vector exists, try to add new vector to storage
                                else
                                {
                                    vector newVect = mult(sourceVect, scalar);
                                    newVect.name = token1[0];
                                    int result = addVect(newVect);

                                    if (result == 0)
                                    {
                                        printf("Vector was not added. Vector storage is full.\n");
                                    }
                                    else
                                    {
                                        if (result == 1)
                                        {
                                            printf("Vector '%c' added!\n", newVect.name);
                                        }
                                        else
                                        {
                                            printf("Vector '%c' replaced!\n", newVect.name);
                                        }

                                        printf("%c = %.2f, %.2f, %.2f\n", newVect.name, newVect.x, newVect.y, newVect.z);
                                    }
                                }
                            }
                        }
                    }

                    //Assign one vectors value to another vector name
                    else if (token4 == NULL && token3[1] == '\0')
                    {
                        vector sourceVect = findVect(token3[0]);

                        //Check vector exists
                        if (sourceVect.name == '\0')
                        {
                            printf("Vector '%c' not found.\n", token3[0]);
                        }
                        else
                        {
                            sourceVect.name = token1[0];
                            int result = addVect(sourceVect);

                            if (result == 0)
                            {
                                printf("Vector was not added. Vector storage is full.\n");
                            }
                            else
                            {
                                if (result == 1)
                                {
                                    printf("Vector '%c' added!\n", sourceVect.name);
                                }
                                else
                                {
                                    printf("Vector '%c' replaced!\n", sourceVect.name);
                                }

                                printf("%c = %.2f, %.2f, %.2f\n", sourceVect.name, sourceVect.x, sourceVect.y, sourceVect.z);
                            }
                        }
                    }

                    //Handle null token4 & 5 when token3 is number
                    else if (token4 == NULL || token5 == NULL)
                    {
                        printf("Assignment needs three numbers: name = x y z\n");
                    }

                    //Assign values to a vector
                    else
                    {
                        char *endX;
                        char *endY;
                        char *endZ;
                        double x = strtod(token3, &endX);
                        double y = strtod(token4, &endY);
                        double z = strtod(token5, &endZ);

                        //Print error when vector values not allowed
                        if (endX == token3 || *endX != '\0' || endY == token4 || *endY != '\0' || endZ == token5 || *endZ != '\0')
                        {
                            printf("Invalid vector values; enter three numbers.\n");
                        }

                        //Add new vector when able
                        else
                        {
                            vector newVect = {.name = token1[0], .x = x, .y = y, .z = z};
                            int result = addVect(newVect);

                            if (result == 0)
                            {
                                printf("Vector was not added. Vector storage is full.\n");
                            }
                            else
                            {
                                if (result == 1)
                                {
                                    printf("Vector '%c' added!\n", newVect.name);
                                }
                                else
                                {
                                    printf("Vector '%c' replaced!\n", newVect.name);
                                }

                                printf("%c = %.2f, %.2f, %.2f\n", newVect.name, newVect.x, newVect.y, newVect.z);
                            }
                        }
                    }
                }

                //Handle operators besides scalar multiplication
                else if (strcmp(token2, "+") == 0 || strcmp(token2, "-") == 0 || strcmp(token2, "dot") == 0 || strcmp(token2, "cross") == 0)
                {
                    //Print error when vector names >1 char
                    if (token1[1] != '\0' || token3 == NULL || token3[1] != '\0')
                    {
                        printf("Use two single-character vector names, such as 'a + b'.\n");
                    }

                    //Decide logic from token2 operator and call functions from vector_functions
                    else
                    {
                        vector vect1 = findVect(token1[0]);
                        vector vect2 = findVect(token3[0]);

                        if (vect1.name == '\0')
                        {
                            printf("Vector '%c' not found.\n", token1[0]);
                        }
                        else if (vect2.name == '\0')
                        {
                            printf("Vector '%c' not found.\n", token3[0]);
                        }
                        else if (strcmp(token2, "+") == 0)
                        {
                            vector sum = add(vect1, vect2);
                            printf("(%c + %c) = %.2f, %.2f, %.2f\n", vect1.name, vect2.name, sum.x, sum.y, sum.z);
                        }
                        else if (strcmp(token2, "-") == 0)
                        {
                            vector difference = sub(vect1, vect2);
                            printf("(%c - %c) = %.2f, %.2f, %.2f\n", vect1.name, vect2.name, difference.x, difference.y, difference.z);
                        }
                        else if (strcmp(token2, "dot") == 0)
                        {
                            double dotProduct = dot(vect1, vect2);
                            printf("(%c dot %c) = %.2f\n", vect1.name, vect2.name, dotProduct);
                        }
                        else
                        {
                            vector crossProduct = cross(vect1, vect2);
                            printf("(%c cross %c) = %.2f, %.2f, %.2f\n", vect1.name, vect2.name, crossProduct.x, crossProduct.y, crossProduct.z);
                        }
                    }
                }

                //Handle scalar multiplication operator
                else if (strcmp(token2, "*") == 0)
                {
                    if (token3 == NULL)
                    {
                        printf("Use the form 'a * number' or 'number * a'.\n");
                    }

                    else
                    {
                        char *endFirst;
                        char *endScalar;
                        double firstValue = strtod(token1, &endFirst);
                        int firstIsNumber = endFirst != token1 && *endFirst == '\0';
                        vector vect1;
                        double scalar;
                        int valid = 1;

                        //Determine whether token1 or token3 is the scalar
                        if (firstIsNumber)
                        {
                            if (token3[1] != '\0')
                            {
                                printf("The second operand must be a one-character vector name.\n");
                                valid = 0;
                            }
                            else
                            {
                                vect1 = findVect(token3[0]);
                                scalar = firstValue;
                            }
                        }

                        //Error if token1 not number and more than 1 char
                        else if (token1[1] != '\0')
                        {
                            printf("Use a one-character vector name.\n");
                            valid = 0;
                        }

                        else
                        {
                            vect1 = findVect(token1[0]);
                            scalar = strtod(token3, &endScalar);

                            if (endScalar == token3 || *endScalar != '\0')
                            {
                                printf("The value after * must be a number.\n");
                                valid = 0;
                            }
                        }

                        //If valid syntax, call mult function
                        if (valid == 1)
                        {
                            if (vect1.name == '\0')
                            {
                                printf("Vector not found.\n");
                            }
                            else
                            {
                                vector product = mult(vect1, scalar);
                                printf("(%c * %.2f) = %.2f, %.2f, %.2f\n", vect1.name, scalar, product.x, product.y, product.z);
                            }
                        }
                    }
                }

                //Print error for all other incorrect commands
                else
                {
                    printf("Command not found. Type -h for commands.\n");
                }
            }
        }
    }
    //Default 0 return value
    return 0;
}