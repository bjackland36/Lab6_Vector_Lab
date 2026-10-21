/**
File: file_parser.c
Author: Blake Ackland
Date: 10/20/2026
Description: This program provides load and save functionalities for vector_lab.c.
             loadFile checks for file existence, then goes through each line and
             adds new vectors to storage if file is properly formatted. Error codes
             are returned when the file is not found or when the file is improperly
             formatted. saveFile simply creates a new file and fills each line with
             data from each vector in proper form to be called in load later on.
AI use disclosure: Lines xx-xx of this program were developed with the use of AI to
                   fix a bug where the first character on a file imported from Excel
                   was read as a byte order mark rather than a letter.
*/
#include "file_parser.h"

//Adds vectors from CSV file to vector storage
//Return:
//0 = Success
//1 = File not found
//2 - Incorrectly formatted csv
int loadFile(const char *filename)
{
    //Read a maximum of 256 chars
    char line[256];
    char *token1;
    char *token2;
    char *token3;
    char *token4;
    char *endTok2;
    char *endTok3;
    char *endTok4;
    vector new;
    //Open file to read
    FILE *file = fopen(filename, "r");

    //Return error if file is null
    if (file == NULL)
    {
        return 1;
    }

    //For each line that is not null, read contents and add vectors to memory
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

        //Check for all tokens otherwise format error
        if (token1 != NULL && token2 != NULL && token3 != NULL && token4 != NULL)
        {
            new = (vector){ .name = token1[0], .x = strtod(token2, &endTok2), .y = strtod(token3, &endTok3), .z = strtod(token4, &endTok4) };
            addVect(new);
        }
        else if (token1 != NULL)
        {
            //Clear storage otherwise partial file will be in memory
            clearStorage();
            fclose(file);
            return 2;
        }
    }

    //Close file and return successfully
    fclose(file);
    return 0;
}

//Takes vectors from vector storage and puts them in CSV file
//Return:
//0 - Success
//1 - Failure
int saveFile(const char *filename)
{
    //Open file to write
    FILE *file = fopen(filename, "w");

    //Return error if cannot open
    if (file == NULL)
    {
        return 1;
    }

    //Get each vector from memory and format it properly into a file
    for (int i = 0; i < getVectCount(); i++)
    {
        vector currentVect = getVectAt(i);

        if (currentVect.name != '\0')
        {
            fprintf(file, "%c,%f,%f,%f\n", currentVect.name, currentVect.x, currentVect.y, currentVect.z);
        }
    }

    //Close file and return successfully
    fclose(file);
    return 0;
}