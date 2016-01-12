/**
* \author Franck CLERGET
* \date 10 december 2015
* \file textIndexing.c
* \brief The function implementation about text indexing.h.
* 2 implementation : one simple with word stockage and an other with a tree stokage
*/

/* ---------------  INCLUDES --------------- */
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "textIndexing.h"
/* ---------------  FUNCTION --------------- */

/**
* \fn void indexText()
* \param FILE
* \return non-return function
* \brief
* Index the file in parameter - Init the descriptor
*/
void indexText(char* fileName) {
    setlocale(LC_CTYPE, "");
    textDescriptor myDescriptor;
    myDescriptor.thermList = malloc(sizeof(therm));
    therm initTherm;
    initTherm.word = "init";
    initTherm.occurence = 0;
    myDescriptor.thermList[0] = initTherm;
    myDescriptor.size = 1;

	FILE* file = fopen(fileName,"r");

    int character;
    if (file != NULL) {
        do {
            character = fgetc(file);
            if(character == '<') {
                skipBracket(file);
            }
            if(character != ' ' && character != '<') {
                ungetc(character,file);
            }
            char* string = getNextWord(file);
            if(string != NULL) {
                addWordToDescriptor(&myDescriptor,string);
            }
        } while (character != EOF);

        for (int i = 0; i < myDescriptor.size; i++) {
            printf("%s , occurence : %i\n",myDescriptor.thermList[i].word,myDescriptor.thermList[i].occurence);
        }
        char* result = descriptorToString(myDescriptor);
        addToBaseDescriptor(fileName,result);
    } else {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
    freeMemory(&myDescriptor);
    fclose(file); // On ferme le fichier qui a été ouvert
}

/**
* \fn void addToBaseDescriptor()
* \param char*
* \return non-return function
* \brief
* Add the descriptor in the text descriptor base
*/
void addToBaseDescriptor(char* fileName, char* string) {

    if(strlen(string) > 1) {
        char* redirectionCommand = " >> ../data/text_descriptor.txt";
        char* command = NULL;
        command = malloc(9+strlen(string)+strlen(redirectionCommand)+strlen(fileName));
        command[0] = 'e';
        command[1] = 'c';
        command[2] = 'h';
        command[3] = 'o';
        command[4] = ' ';
        command[5] = '"';
        command[6] = '\0';
        command = strcat(command,fileName);
        command = strcat(command,":");
        command = strcat(command,string);
        command = strcat(command,"\"");
        command = strcat(command,redirectionCommand);
        system(command);
        free(command); // bug
    }
    free(string);
}

/**
* \fn void skipBracket()
* \param FILE*
* \return non-return function
* \brief
* After start reading a bracket this method will skip character until the end of the bracket
*/
void skipBracket(FILE* file) {
    int characterReaded;
    do {
        characterReaded = fgetc(file);
    } while (characterReaded != '>' && characterReaded != EOF);

}

/**
* \fn void getNextWord()
* \param FILE*
* \return The string of the next word
* \brief
* Get the next word of the text - respect the configuration
*/
char* getNextWord(FILE* file) {
    char* string = malloc(1);
    int size = 1;
    char character;
    int characterReaded;
    characterReaded = fgetc(file);
    while(characterReaded != ' ' && characterReaded != EOF && characterReaded != '\n' && characterReaded != '<') {
        character = (char)characterReaded;
        string = realloc(string,++size*sizeof(char));
        string[size-2] = character;
        characterReaded = fgetc(file);
    }
    if(characterReaded == '<') {
        ungetc(characterReaded,file);
    }
    string[size-1] = '\0';
    if(string[0] == '\n' || (int)string[0] == 0 || strlen(string) < 4 || strlen(string) > 10) { // CONFIGURATION
        return NULL;
    }
    return parseCharacter(string);
}

/**
* \fn void addWordToDescriptor()
* \param textDescriptor*, char*
* \return non-return function
* \brief
* Add the word to Descriptor - Increase occurence if descriptor already contains word
*/
void addWordToDescriptor(textDescriptor* myDescriptor, char* string) {
    int test = containsWord(*myDescriptor,string);
    if(test != 0) {
        myDescriptor->size++;
        myDescriptor->thermList = (therm*)realloc(myDescriptor->thermList,(myDescriptor->size)*sizeof(therm));
        therm myTherm;
        myTherm.word = string;
        myTherm.occurence = 1;
        myDescriptor->thermList[myDescriptor->size-1] = myTherm;
    } else {
        free(string);
    }
}

/**
* \fn void freeMemory()
* \param textDescriptor
* \return non-return function
* \brief
* Clean the memory
*/
void freeMemory(textDescriptor* myDescriptor) {
    for (int i = 1; i < myDescriptor->size-1; i++) {
        free(myDescriptor->thermList[i].word);
    }
//free(myDescriptor->thermList);
}

/**
* \fn void containsWord()
* \param textDescriptor, char*
* \return 0 if the descriptor contains the word
* \brief
* Check if it contains the word
*/
int containsWord(textDescriptor myDescriptor, char* string) {
    int status = 1;
    for (int i = 1; i < myDescriptor.size; i++) {
        status = strcmp(myDescriptor.thermList[i].word,string);
        if (status == 0) {
            myDescriptor.thermList[i].occurence++;
            break;
        }
    }
    return status;
}

/**
* \fn void descriptorToString()
* \param textDescriptor
* \return char* of the descriptor
* \brief
* The string of the descriptor
*/
char* descriptorToString(textDescriptor myDescriptor) {
    int size = 0;
    char* toString = NULL;
    char* stringTmp = NULL;
	char buffer[1];
    int isFirst=0;
    for (int i = 1; i < myDescriptor.size; i++) {
        if(myDescriptor.thermList[i].occurence > 2) {
            if(isFirst == 0) {
                toString = myDescriptor.thermList[i].word;
                size = strlen(myDescriptor.thermList[i].word)+4;
                toString = realloc(toString,size);
                toString[size-4] = ',';
		sprintf(buffer, "%d", myDescriptor.thermList[i].occurence);
                toString = strcat(toString,buffer);
                toString[size-2] = ';';
                toString[size-1] = '\0';
                isFirst = 1;

            } else {
                stringTmp = myDescriptor.thermList[i].word;
                size += strlen(stringTmp)+4;
                toString = realloc(toString,size);
                toString = strcat(toString,stringTmp);
                toString = strcat(toString,",");
		sprintf(buffer, "%d", myDescriptor.thermList[i].occurence);
                toString = strcat(toString,buffer);
                toString = strcat(toString,";");
                toString = strcat(toString,"\0");
            }
        }
    }
	printf("toString : %s\n",toString);
    return toString;
}

/**
* \fn void parseCharacter()
* \param wchar_t*
* \return char* of treated string
* \brief
* Do all treatment the string
*/
char* parseCharacter(char* string) {
    int size = strlen(string)+1;
    wchar_t* newString = malloc(size*sizeof(wchar_t));
    mbstowcs(newString,string,size);
    newString[size-1] = '\0';
    wchar_t* corr = L"\0\0\x0A\0\x0D\0àAâAäAéEêEèEëEîIïIôOöOûUüUçC";
    for (int i = 0; i < wcslen(newString); i++) {
        for (int j = 0; j < 17; j++) {
            if(newString[i] == corr[2*j]) {
                newString[i] = corr[2*j + 1];
                break;
            }
        }
    }
    for (int i = 0; i < wcslen(newString); i++) {
        newString[i] = towlower(newString[i]);
    }
    free(string);
    string = NULL;
    string = malloc(size);
    wcstombs(string,newString,size);
    free(newString);
    string[size-1] = '\0';
    return string;
}

/**
* \fn void findTherm()
* \param char*, int
* \return char* the therm of the line
* \brief
* Is used inside findWord - Obtain each therm with this method
*/
char* findTherm(char* line,int position){

	const char s1[2] = ";";
	char *tokenLine = line;
	char *tokenTherm;
		
	tokenTherm = strtok(tokenLine,s1);
	int cpt = 0;
	while( tokenTherm != NULL ) 
	{
		
		if(cpt == position){
			return tokenTherm;
		}
		tokenTherm = strtok(NULL, s1);
		cpt++;
	}
		
	return NULL;
}

/**
* \fn void findWord()
* \param char*, int*
* \return search* the tab of file finded
* \brief
* Extract list of file finded
*/
search* findWord(char* word,int* size){

	FILE* file = fopen("../data/text_descriptor.txt","r");

	*size = 0;
	search* tabSearch = NULL;

	if (file != NULL) {
	    char line[256];

	/* Treat file line by line */
	    while (fgets(line, sizeof(line), file)) {
		const char s[2] = ":";
		const char s1[2] = ";";
		const char s2[2] = ",";
		char *tokenLine;
		char *file;
		char *endline = NULL;
		char *tokenTherm;
		char *tokenWord;
		tokenLine = strtok(line, s);
		file = tokenLine;
		tokenLine = strtok(NULL, s);
		int position = 0;
		while( tokenLine != NULL && *tokenLine != 10) 
		{
			/* Obtain next therm with findTherm */
			char* therm = findTherm(tokenLine,position);
			/* Separate the word and the occurence */
			char* thermWord= strsep(&therm,",");
			int thermOccurence = atoi(strsep(&therm,","));
			/* If the word match, his added to the list */
			if(thermWord != NULL){
				if(strcmp(thermWord,word) == 0) {
					fprintf(stderr,"find match \n");
					(*size)++;
					if(*size == 1){
						tabSearch = malloc((*size)*sizeof(search));
					}
					else {
						tabSearch = realloc(tabSearch,(*size)*sizeof(search));
					}
					tabSearch[(*size)-1].fileName = file;
					tabSearch[(*size)-1].wordSearch.word = thermWord;
					tabSearch[(*size)-1].wordSearch.occurence =  thermOccurence;

				}
			}
			tokenLine = strtok(NULL, s);
		}
	    }
	    fclose(file);
	}

	return tabSearch;
}

