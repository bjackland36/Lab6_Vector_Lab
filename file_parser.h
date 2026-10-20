/**
File: file_parser.h
Author: Blake Ackland
Date: 10/20/2026
Description: Header file for file_parser.c
 */
 //Header guard
#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <stdio.h>
#include "vector_data.h"
#include "vector.h"

int loadFile(const char *filename);
int saveFile(const char *filename);

#endif