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
void histogramme(FILE* Image, int niv, int H, int L, int id); 
/**
 *computes a file histogramme from a file and returns the picture descriptor in the descriptor base file
 */
void textDescriptorLinker(char fileName[], int id); 
/**
 *links the name of the descriptor with the file name and saves it in the link base
 */
int comparison(int niv, FILE* Histo1, FILE* Histo2);
/**
 * compares two histo and spot the similarities of two pictures
 */
int file1comparedfile2(int niv, int id1, int id2);
/**
 * compares two selected pictures by giving their descriptor id in the parameters
 */
int BlackandWhiteIndexation();
int ColorIndexation();

