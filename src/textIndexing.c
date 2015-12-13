/**
* \author Franck CLERGET
* \date 10 december 2015
* \file textIndexing.c
* \brief The function implementation about text indexing.h.
* Method to index : ls <fileName> | XXX.sh >> baseTextDescriptor.txt
* Where XXX.sh is the text indexing script.
* 2 implementation : one simple with word stockage and an other with a tree stokage
*/

/* ---------------  INCLUDES --------------- */
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include "textIndexing.h"
/* ---------------  FUNCTION --------------- */

/**
* \fn void indexText()
* \param char*
* \return non-return function
* \brief
* Index the file in parameter - Init the descriptor
*/
void indexText(char* fileName) {
setlocale(LC_CTYPE, "");
printf("debut du programme\n");
    FILE* file = NULL;
    textDescriptor myDescriptor;
    myDescriptor.thermList = malloc(sizeof(therm));
    therm initTherm;
    initTherm.word = "init";
	initTherm.occurence = 0;
    myDescriptor.thermList[0] = initTherm;
    myDescriptor.size = 1;
    file = fopen("../data/test.txt", "r");
    wint_t character;
    if (file != NULL) {
        do {
            character = fgetwc(file);
            if(character == '<') {
                skipBracket(file);
            }
            if(character != ' ' && character != '<') {
                ungetwc(character,file);
            }
            char* string = getNextWord(file);
            if(string != NULL) {
                addWordToDescriptor(&myDescriptor,string);
            }
        } while (character != WEOF);

        for (int i = 0; i < myDescriptor.size; i++) {
            printf("%s , occurence : %i\n",myDescriptor.thermList[i].word,myDescriptor.thermList[i].occurence);
        }
		char* result = descriptorToString(myDescriptor);
		printf("chaine de fin : %s\n",result);
		addToBaseDescriptor(result);
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
void addToBaseDescriptor(char* string) {
	if(strlen(string) > 1){

	char* redirectionCommand = " >> ../data/descripteur.txt";
	char* command = malloc(7+strlen(string)+strlen(redirectionCommand));
	command[0] = 'e';command[1] = 'c';command[2] = 'h';command[3] = 'o';command[4] = ' ';command[5] = '"';
	command = strcat(command,string);
	command = strcat(command,"\"");
	command = strcat(command,redirectionCommand);
	system(command);
	free(string);
	free(command);
	}
}

/**
* \fn void skipBracket()
* \param FILE*
* \return non-return function
* \brief
* After start reading a bracket this method will skip character until the end of the bracket
*/
void skipBracket(FILE* file) {
    wint_t characterReaded;
    do {
        characterReaded = fgetwc(file); // On lit le caractère
    } while (characterReaded != '>' && characterReaded != WEOF);

}

/**
* \fn void getNextWord()
* \param FILE*
* \return The string of the next word
* \brief
* Get the next word of the text - respect the configuration
*/
char* getNextWord(FILE* file) {
    wchar_t* string = malloc(1*sizeof(wchar_t));
    int size = 1;
    wchar_t character;
    wint_t characterReaded;
    characterReaded = fgetwc(file);
    while(characterReaded != ' ' && characterReaded != WEOF && characterReaded != '\n' && characterReaded != '<') {
        character = (wchar_t)characterReaded;
        string = realloc(string,++size*sizeof(wchar_t));
        string[size-2] = character;
        characterReaded = fgetwc(file);
	wprintf(L"char dans getword : %li\n",(unsigned)characterReaded);
    }
	if(characterReaded == '<'){
		ungetwc(characterReaded,file);
	}
    string[size-1] = '\0';
	if(string[0] == '\n' || (int)string[0] == 0 || wcslen(string) < 2 || wcslen(string) > 10){
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
	if(test != 0){
    myDescriptor->size++;
    if((myDescriptor->thermList = (therm*)realloc(myDescriptor->thermList,(myDescriptor->size)*sizeof(therm))) == NULL) {
        exit(0);
    }
    therm myTherm;
    myTherm.word = string;
	myTherm.occurence = 1;
    myDescriptor->thermList[myDescriptor->size-1] = myTherm;
	}
	else {
		free(string);
	}
}

/**
* \fn void freeMemory()
* \param textDescriptor*
* \return non-return function 
* \brief
* Clean the memory
*/
void freeMemory(textDescriptor* myDescriptor) {
    for (int i = 1; i < myDescriptor->size; i++) {
        free(myDescriptor->thermList[i].word);
    }
    free(myDescriptor->thermList);
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
char* descriptorToString(textDescriptor myDescriptor){
	char* toString = malloc(1);
	char* stringTmp = NULL;
	for (int i = 1; i < myDescriptor.size; i++) {
		if(myDescriptor.thermList[i].occurence > 2){
		stringTmp = myDescriptor.thermList[i].word;
		toString = realloc(toString,strlen(toString)+strlen(stringTmp)+2);
		toString = strcat(toString,stringTmp);
		toString = strcat(toString,";");
		}
	}
	return toString;
}

/**
* \fn void parseCharacter()
* \param wchar_t*
* \return char* of treated string
* \brief
* Do all treatment the string
*/
char* parseCharacter(wchar_t* string){
	wchar_t * corr = L"\0\0\x0A\0\x0D\0àAâAäAéEêEèEëEîIïIôOöOûUüUçC";
	for (int i = 0; i < wcslen(string); i++){
		for (int j = 0; j < 17; j++) {
			if(string[i] == corr[2*j]){
				string[i] = corr[2*j + 1];
			}
		}
	}
	for (int i = 0; i < wcslen(string); i++) {
		string[i] = tolower(string[i]);
	}
	char* newString = malloc(wcslen(string));
	wcstombs(newString,string,wcslen(string));
	return newString;
}
