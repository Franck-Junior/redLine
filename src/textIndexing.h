/**
* \author Franck CLERGET
* \date 4 december 2015
* \file textIndexing.h
* \brief The struct and function about text indexing.
*/

#include <stdlib.h>
#include <stdio.h>

/**
* \struct therm
* \brief
* therm contains a word with his occurence.
*/
typedef struct {
    char* word;
    unsigned int occurence;
} therm;

/**
* \struct textDescriptor
* \brief
* The text descriptor contains information about a specific text file.
*/
typedef struct {
    therm* thermList;
    int size;
} textDescriptor;

typedef struct {
    therm wordSearch;
    char* fileName;
} search;


/* ---------------  FUNCTION --------------- */

/**
* \fn void indexText()
* \param FILE
* \return non-return function
* \brief
* Index the file in parameter - Init the descriptor
*/
void indexText(char* fileName);

/**
* \fn void addToBaseDescriptor()
* \param char*
* \return non-return function
* \brief
* Add the descriptor in the text descriptor base
*/
void addToBaseDescriptor(char* fileName, char* string);

/**
* \fn void skipBracket()
* \param FILE*
* \return non-return function
* \brief
* After start reading a bracket this method will skip character until the end of the bracket
*/
void skipBracket(FILE* file);

/**
* \fn void getNextWord()
* \param FILE*
* \return The string of the next word
* \brief
* Get the next word of the text - respect the configuration
*/
char* getNextWord(FILE* file);

/**
* \fn void addWordToDescriptor()
* \param textDescriptor*, char*
* \return non-return function
* \brief
* Add the word to Descriptor - Increase occurence if descriptor already contains word
*/
void addWordToDescriptor(textDescriptor* myDescriptor, char* string);

/**
* \fn void freeMemory()
* \param textDescriptor
* \return non-return function
* \brief
* Clean the memory
*/
void freeMemory(textDescriptor* myDescriptor);

/**
* \fn void containsWord()
* \param textDescriptor, char*
* \return 0 if the descriptor contains the word
* \brief
* Check if it contains the word
*/
int containsWord(textDescriptor myDescriptor, char* string);

/**
* \fn void descriptorToString()
* \param textDescriptor
* \return char* of the descriptor
* \brief
* The string of the descriptor
*/
char* descriptorToString(textDescriptor myDescriptor);

/**
* \fn void parseCharacter()
* \param wchar_t*
* \return char* of treated string
* \brief
* Do all treatment the string
*/
char* parseCharacter(char* string);

/**
* \fn void findTherm()
* \param char*, int
* \return char* the therm of the line
* \brief
* Is used inside findWord - Obtain each therm with this method
*/
char* findTherm(char* line,int position);

/**
* \fn void findWord()
* \param char*, int*
* \return search* the tab of file finded
* \brief
* Extract list of file finded
*/
search* findWord(char* word,int* size);

/**
* \fn void getIndexingFile()
* \param int*
* \return char** the tab of file finded
* \brief
* Extract list of ndexed file
*/
char** getIndexingFile(int* size);
