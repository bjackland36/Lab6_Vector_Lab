/**
File: file_parser.c
Author: Blake Ackland
Date: 10/20/2026
Description:
*/
//  /home/acklandb/GitProjects/Lab6_Vector_Lab/tst.csv
#include "file_parser.h"

//Adds vectors from CSV file to vector storage
//Return:
//0 = Success
//1 = File not found
//2 - Incorrectly formatted csv
int loadFile(const char *filename)
{
    char line[256];
    char *token1;
    char *token2;
    char *token3;
    char *token4;
    char *endTok2;
    char *endTok3;
    char *endTok4;
    vector new;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        return 1;
    }

    while (fgets(line, sizeof line, file) != NULL)
    {
        //Ignore UTF-8 byte order mark in Excel
        if ((unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB && (unsigned char)line[2] == 0xBF)
        {
            memmove(line, line + 3, strlen(line + 3) + 1);
        }

        token1 = strtok(line, ",\r\n");
        token2 = strtok(NULL, ",\r\n");
        token3 = strtok(NULL, ",\r\n");
        token4 = strtok(NULL, ",\r\n");

        if (token1 != NULL && token2 != NULL && token3 != NULL && token4 != NULL)
        {
            new = (vector){ .name = token1[0], .x = strtod(token2, &endTok2), .y = strtod(token3, &endTok3), .z = strtod(token4, &endTok4) };
            addVect(new);
        }
        else if (token1 != NULL)
        {
            clearStorage();
            fclose(file);
            return 2;
        }
    }

    fclose(file);
    return 0;
}

//Takes vectors from vector storage and puts them in CSV file
//Return:
//0 - Success
//1 - Failure
int saveFile(const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        return 1;
    }

     for (int i = 0; i < getVectCount(); i++)
    {
        vector currentVect = getVectAt(i);

        if (currentVect.name != '\0')
        {
            fprintf(file, "%c,%f,%f,%f\n", currentVect.name, currentVect.x, currentVect.y, currentVect.z);
        }
    }

    fclose(file);
    return 0;
}