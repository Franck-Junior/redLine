/**
* \author Franck CLERGET
* \date 4 december 2015
* \file textIndexing.h
* \brief The struct and function about text indexing.
* Method to index : ls <fileName> | XXX.sh >> baseTextDescriptor.txt
* Where XXX.sh is the text indexing script.
*/

/**
* \struct therm
* \brief
* therm contains a word with his occurence.
*/
struct therm {
    char[20] word;
    unsigned int occurence;
}

/**
* \struct textDescriptor
* \brief
* The text descriptor contains information about a specific text file.
*/
struct textDescriptor {
    therm[] thermList; // pourquoi pas utiliser une pile/file
};

/* ---------------  FUNCTION --------------- */

/**
* \fn void indexText()
* \param no parameters
* \return non-return function
* \brief
* Index the file in parameter
*/
void indexText();
