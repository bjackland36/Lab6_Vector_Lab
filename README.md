# Lab6_Vector_Lab
**Last Update to README:**

10/20/2026 by Blake Ackland

## Description of Program:

This program is a vector calculator. When executed, the program will display a welcome message and a help command, followed by a user input prompt. If the program is invoked with command-line argument '-h' it will display a summary of program usage before running as it would otherwise. User can create new vectors and perform vector math. Vectors are stored in a dynamic array database. The database can be saved as a CSV file. Additionally, CSV files of proper format containing vector information on each line can be loaded into the program for use. This program implements add, subtract, scalar multiply, dot product, and cross product functionalities.

## Build Instructions:

This program provides a Makefile to make building this program easier. To build in Ubuntu, simply type 'make'. To build without the Makefile, run the following command: 'gcc -Wall vector_functions.c vector_data.c vector_lab.c file_parser.c -o vector_lab'

## Run Instructions:
To run this program, there is an option of './vector_lab' which will run the standard program, or './vector_lab -h' which will display a summary of program usage before running the standard program.

## Program Commands:

**This program supports the following commands:**
- 'quit' - terminates program
- 'load filename.csv' - load contents of a CSV file into vector storage
- 'save filename.csv' - load contents of current session vector storage into new CSV file
- 'list' - list vectors in current session's vector storage
- 'clear' - clear current session's vector storage

 _(For the following, characters and numbers are for example)_  
- 'a' - lists contents of vector a
- 'a = b' - copies values from vector b into vector a
- 'a + b' - returns sum of a + b   
- 'a = 1.0, 2.0, 3.0' - Assigns new values to vector a
- 'a = b + c' - performs b + c and copies sum to a
- 'a = 2 * b' - performs 2 * b and copies product to a
    
## Use of Dynamic Memory:
To store vectors during runtime, this program uses dynamic memory. In order to do so, an array of vectors named 'vectorStorage' is created in vector_data.c. The pointer to vectorStorage is initialized to NULL when the program begins, but when the first vector is added by the user, the malloc() function is used to assign a location in memory for vectorStorage. vectorStorage begins with a size of 2 vectors because the user may only choose to perform calculations between 2 vectors. In the event that a third vector is added, vectorStorage is reallocated using realloc() and the size of the array is doubled. This doubling of the array continues each time the size limit of the array is exceeded, in order to minimize the amount of realloc() calls. When the 'clear' command is invoked, vectorStorage is freed with the free() function. 'clear' is automatically invoked at program termination to ensure memory leaks are not possible. 

## Program Limitations:
- This program currently only supports 1 character names for vectors in memory.
- This program clears memory when 'load' command successfully finds file, meaning an invalid read still clears vector memory.
