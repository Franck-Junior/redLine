/**
* \author Franck CLERGET
* \date 4 december 2015
* \struct config config.conf.h "The header config file for encoding"
* \brief
* At the start of the programm, each non-indexing file have to be indexed.
* If configuration changes, every files have to be indexed.
*
*/

char[50] PATH; // Path of the folder to index

/* ---------------  TEXT FILE CONFIGURATION --------------- */

int WORD_SIZE_MIN; // Minimum of letter to accept as a word ; Default value is : 3
int WORD_SIZE_MAX; // Maximum of letter to accept as a word
int TRESHOLD_OCCURENCE; // Only keep word which appear more than this number



/* ---------------  FUNCTION --------------- */

/**
* \fn void setConfiguration()
* \param no parameters
* \return non-return function
* \brief
* Set configuration variable of the programm.
*/
void setConfiguration();

/**
* \fn int isDifferent()
* \param no parameters
* \return 1 if it's a different configuration - 0 if it's the same configuration.
* \brief
* Compare with the file : .old_configuration.txt if the configuration have changed.
*/
int isDifferent();
