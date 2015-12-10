/**
* \author Franck CLERGET
* \date 4 december 2015
* \file textIndexing.h
* \brief The struct and function about text indexing.
* Method to index : ls <fileName> | XXX.sh >> baseTextDescriptor.txt
* Where XXX.sh is the text indexing script.
*/

#include <stdlib.h>
#include <stdio.h>

/**
* \struct therm
* \brief
* therm contains a word with his occurence.
*/
struct therm {
    char* word;
    unsigned int occurence;
};

/**
* \struct textDescriptor
* \brief
* The text descriptor contains information about a specific text file.
*/
struct textDescriptor {
    struct therm thermList; // pourquoi pas utiliser une pile/file
};

/* ---------------  FUNCTION --------------- */

/**
* \fn void indexText()
* \param no parameters
* \return non-return function
* \brief
* Index the file in parameter - Init the descriptor
*/
void indexText(char* fileName);

/**
* \fn void addToBaseDescriptor()
* \param no parameters
* \return non-return function
* \brief
* Add the descriptor in the text descriptor base
*/
void addToBaseDescriptor();

/**
* \fn void processIndexing()
* \param no parameters
* \return non-return function
* \brief
* Read file and process to indexing (also set descriptor variables)
*/
void processIndexing(char* fileName);

/**
* \fn void skipBracket()
* \param no parameters
* \return non-return function
* \brief
* After start reading a bracket this method will skip character until the end of the bracket
*/
void skipBracket(FILE* file);

/**
* \fn void skipBracket()
* \param no parameters
* \return The string of the next word
* \brief
* Get the next word of the text - respect the configuration
*/
char* getNextWord(FILE* file);
