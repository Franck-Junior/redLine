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
 *computes a file histogramme from a file and returns the picture descriptor in the descriptor base file
 */
int comparison(int niv, FILE* Histo1, FILE* Histo2);
/**
 * compares two histo and spot the similarities of two pictures
 */
void textDescriptorLinker(char fileName[], char chemin[100], int id);
/**
 *links the name of the descriptor with the file name and saves it in the link base
 */
int file1comparedTofile2(int niv, char chemin[100], int id1, int id2);
/**
 * compares two selected pictures by giving their descriptor id in the parameters and the histogramme level
 */
int blackandWhiteIndexation(char cheminlocal[100], int nbdesc);
int colorIndexation(char cheminlocal[100], int nbdesc);
// int researchPictures(int niv, int id);
void researchPictures(char fileRef[100], int niv,char chemin[100], char fileRes[100]);
void descToFileName(int id, char chemin[100], char currentfile[100], int option);
/**
 * converts a descriptor id into a fileName
 */
int file1Tofile2comparison(int niv, char chemin[100],int id1,int id2);

