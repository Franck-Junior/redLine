#ifndef __DEALINGWITHSOUND_H__
#define __DEALINGWITHSOUND_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
    
extern int TAILLE_MAX_CHEMIN;
extern int NOMBRE_ECHANTILLONS;
extern int NOMBRE_INTERVALLES;

int IndexFileAudio(char fileName[]);

int searchAudio(char *searched);

 typedef struct WAVE{
     //[Bloc de déclaration d'un fichier au format WAVE]
    char FileTypeBlocID[4];    //(4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46) 4
    int32_t FileSize;          //(4 octets) : Taille du fichier moins 8 octets 8
    char FileFormatID [4];     // (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45) 12

    //[Bloc décrivant le format audio]
    char FormatBlocID [4];     //(4 octets) : Identifiant «fmt » 16
    int32_t BlocSize;          // (4 octets) : Nombre d'octets du bloc - 8 20

    int16_t AudioFormat  ;     //(2 octets) : Format du stockage dans le fichier 22
    int16_t NbrCanaux;      //(2 octets) : Nombre de canaux 24
    int32_t Frequence  ;       //(4 octets) : Fréquence d'échantillonnage (en hertz) [11025, 22050, 44100 et éventuellement 48000 et 96000] 28
    int32_t BytePerSec ;       //(4 octets) : Nombre d'octets à lire par seconde (Frequence * BytePerBloc). 32
    int16_t BytePerBloc;       //(2 octets) : Nombre d'octets par bloc d'échantillonnage (tous canaux confondus : NbrCanaux * BitsPerSample/8).34
    int16_t BitsPerSample;     //(2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24) 36

     //[Bloc des données]
    char DataBlocID [4];       //(2 octets) : Constante «data»  (0x64,0x61,0x74,0x61) 40
    int32_t  DataSize;         //(4 octets) : Nombre d'octets des données (i.e. "Data[]", i.e. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement).
    void* DATA;         //Données
} wave;

// index fileName 
/*
open files fileName, base_descripteur_son, liste_base_son
get data into WAVE, check if everything alright
write descripteur into base_descripteur
update liste_base_son
*/
//int IndexFile(char fileName[]);

//int compare_son(char nom_son[], char nom_son_test[]);

//int recherche_son(char extrait[]);


/*
1 - 4   "RIFF"  Marks the file as a riff file. Characters are each 1 byte long.
5 - 8   File size (integer)   Size of the overall file - 8 bytes, in bytes (32-bit integer). Typically, you'd fill this in after creation.
9 -12   "WAVE"  File Type Header. For our purposes, it always equals "WAVE".
13-16   "fmt "  Format chunk marker. Includes trailing null
17-20   16  Length of format data as listed above
21-22   1   Type of format (1 is PCM) - 2 byte integer
23-24   2   Number of Channels - 2 byte integer
25-28   44100   Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). Sample Rate = Number of Samples per second, or Hertz.
29-32   176400  (Sample Rate * BitsPerSample * Channels) / 8.
33-34   4   (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo
35-36   16  Bits per sample
37-40   "data"  "data" chunk header. Marks the beginning of the data section.
41-44   File size (data)  Size of the data section.
Sample values are given above for a 16-bit stereo source. 

NOTES IMPORTANTES :  Les octets des mots sont stockés sous la forme  (i.e., en "little endian")
*/

#endif