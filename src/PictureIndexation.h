#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void nBitQuantificator(FILE * FichierQuantif, int n, int pixelLevel);
/**
 *quantifies a pixel level to n bit given on the parameter, then returns the n bits in the array T
 */
void Quantification(FILE* Image, int n);
/**
 *realizes a quantification on every pixel of the picture and return the results in a file
 */
void histogramme(FILE* Image, int niv, char chemin[100], int H, int L, int id);
/**
 *computes a file histogramme from a file and returns the picture descriptor in the descriptor base file located in the directory given in the parameter
 */
int comparison(int niv, FILE* Histo1, FILE* Histo2);
/**
 * compares two histo and spot the similarities of two pictures
 */
int file1comparedTofile2(int niv, char chemin[100], int id1, int id2);
/**
 * compares two selected pictures by giving their descriptor id in the parameters and the histogramme level
 * and giving in "chemin" the file descriptor with its path
 * it then returns the result
 */
void textDescriptorLinker(char fileName[], char chemin[100], int id);
/**
 *links the name of the descriptor with the file name and saves it in the link base
 * chemin is the path of the directory of LISTE_BASE_IMAGE
 */
int blackandWhiteIndexation(char cheminlocal[100], int nbdesc);
/*
 * launch an automatic indexation of all black and white images. cheminlocal is the path of the directory where are to pictures to index.
 */

int colorIndexation(char cheminlocal[100], int nbdesc);

void descToFileName(int id, char chemin[100], char currentfile[100]);
/**
 * converts a descriptor id into a fileName
 * currentfile is the result of the conversion
 * option selects the type of file : whether it's colored or not
 * chemin is the path of the "LISTE_BASE_IMAGE" directory
 */
int fileNameToDesc(char chemin[100], char fileName[100]);
/*
 * the other way around : return the desc id of of file which name is given in the parameter
 */
int file1Tofile2comparison(int niv, char chemin[100],char fileName1[50], char fileName2[50]);
/**
 * compares two selected pictures by giving their name in the parameters and the histogramme level
 * and giving in "chemin" the file descriptor path
 * it then returns the result
 */
void researchPictures(int niv, char fileName[50], char fileNamefound[50]);
/*
 * on mettra le chemin du dossier du fichier à chercher en paramètre. ou pas. Pour faire l'implémentation globale, fait en sorte que 
 * l'utilisateur normale accède directement à la recherche en fait une indexation auto préalable :Voir l'interface et tous ce qu'arélien a fait
 */