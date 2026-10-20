/**
File: file_parser.c
Author: Blake Ackland
Date: 10/20/2026
Description:
*/
#include "file_parser.h"

//Adds vectors from CSV file to vector storage
//Return:
//0 = Success
//1 = Failure
int loadFile(const char *filename)
{
    vector new;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof line, file) != NULL)
    {
        char input = line;
        token1 = strtok(input, " ,\t\r\n");
        token2 = strtok(NULL, " ,\t\r\n");
        token3 = strtok(NULL, " ,\t\r\n");
        token4 = strtok(NULL, " ,\t\r\n");

        new = (vector){ .name = token1, .x = strtod(token2, &endTok2), .y = strtod(token3, &endTok3), .z = strtod(token4, &endTok4) };
        addVect;
    }

    fclose(file);
    return 0;
}

//Takes vectors from vector storage and puts them in CSV file
int saveFile(const char *filename);
{

}