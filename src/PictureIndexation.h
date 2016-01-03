#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void nBitQuantificator(FILE * FichierQuantif, int n, int pixelLevel); 
/**
 *quantifies a pixel level to n bit given on the parameter, then returns the n bits in the array T
 */ 
void Quantification(FILE* Image, int n, int H, int L); 
/**
 *realizes a quantification on every pixel of the picture and return the results in a file
 */
void histogramme(FILE* Image, int niv, int H, int L, int id); 
// /**
//  *computes a file histogramme from a file and return the result on another file
//  */
// void PictureDescriptor(FILE* Histo, char[] id, int* descriptor, FILE* descBase); 
// /**
//  *returns the picture descriptor in the descriptor base file
//  */
// void textDescriptorLinker(char fileName[], char id[], FILE* IDNAME); 
// /**
//  *links the name of the descriptor with the file name and saves it in the link base
//  */
// void comparison(FILE Histo1, FILE Histo2);
// /**
//  * compare two histo and spot the similarities of two pictures
//  */


