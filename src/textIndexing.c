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

#include "textIndexing.h"

/* ---------------  FUNCTION --------------- */

/**
* \fn void indexText()
* \param no parameters
* \return non-return function
* \brief
* Index the file in parameter - Init the descriptor
*/
void indexText(char* fileName){
    FILE* file = NULL;

    file = fopen("../data/test.txt", "r");
    int character;
    if (file != NULL)
    {
        do
        {
            character = fgetc(file); // On lit le caractère
            if(character == '<'){
                skipBracket(file);
            }
            if(character != ' ' && character != '<'){
                ungetc(character,file);
            }
            printf("CHAR : %c\n",character);
            printf("\nRESULT :\n");
            printf("%s\n\n",getNextWord(file));
        } while (character != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }

    fclose(file); // On ferme le fichier qui a été ouvert
}

/**
* \fn void addToBaseDescriptor()
* \param no parameters
* \return non-return function
* \brief
* Add the descriptor in the text descriptor base
*/
void addToBaseDescriptor(){

}

/**
* \fn void processIndexing()
* \param no parameters
* \return non-return function
* \brief
* Read file and process to indexing (also set descriptor variables)
*/
void processIndexing(char* fileName){

}

/**
* \fn void skipBracket()
* \param no parameters
* \return non-return function
* \brief
* After start reading a bracket this method will skip character until the end of the bracket
*/
void skipBracket(FILE* file){
    int characterReaded;
    do
    {
        characterReaded = fgetc(file); // On lit le caractère
    } while (characterReaded != '>'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

}

/**
* \fn void skipBracket()
* \param no parameters
* \return The string of the next word
* \brief
* Get the next word of the text - respect the configuration
*/
char* getNextWord(FILE* file){
    printf("START of get getNextWord\n");
    char* string;
    char list[] = {' ', EOF};
    char character;
    int characterReaded;
    characterReaded = fgetc(file);
    while(characterReaded != ' ' && characterReaded != EOF && characterReaded != '\n'){
        character = (char)characterReaded;
        printf("%c\n", character);
        //strcat foire voir pourquoi
        // regarder pour retourner une string correct
        characterReaded = fgetc(file);
    }
    printf("\n");
    return string;
}
