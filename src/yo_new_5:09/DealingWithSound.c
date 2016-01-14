#include "DealingWithSound.h"

int NOMBRE_INTERVALLES = 40; //<10000000, %2==0

int DEBUG=1;

typedef struct Scientific{
    int mantisse;
    int exposant;
}Scientific;

Scientific *normalization(char* in, Scientific *sc){
    
    char mantisseString[8];//8
    mantisseString[0]=in[3];
    
    for(int i=5;i<12;i++)
        mantisseString[i-4]=in[i];

    sc->mantisse=atoi(mantisseString);
    if(in[2]!=" ")
        sc->mantisse=sc->mantisse*-1;

    sc->exposant=atoi(&(in[15]));

    return sc;
}

    
int getIntervalle(Scientific sc){
    
    int result=sc.mantisse;
    //adjust size of mantisse by exposant
    for(int i=1;i<=sc.exposant;i++)
        result=result/10; 
    
    //max result possible==99999999, min 999,
    int pas=1000000/NOMBRE_INTERVALLES;

    result=result/pas;

    if(result < 0)
        result=NOMBRE_INTERVALLES+result-1;

    return result;
}

// index fileName trying to deal with txt files
int IndexFileAudio(char fileName[]){

    // open files fileName, base_descripteur_son, liste_base_son
    errno = 0;
    FILE* pFileName = fopen(fileName, "r");
    if(pFileName  == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-1);   //Err opening fileName
    }
    FILE* pBaseDescriptorSon = fopen("./sto/base_descripteur_son", "a+");
    if (pBaseDescriptorSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-2);  //Err opening pBaseDescriptorSon
    }
    FILE* pListeBaseSon = fopen("./sto/liste_base_son", "a+");
    if (pListeBaseSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-3);  //Err opening pListeBaseSon
    }

    //update liste_base_son
    int currId = 0;
    int lastId=0;
    fseek(pListeBaseSon, -2,SEEK_END);
    fscanf(pListeBaseSon,"   %d", &lastId);
    printf("lastID=%d\n",lastId);
    currId = lastId+1;
    fprintf(pListeBaseSon,"%s;", fileName);
    fprintf(pListeBaseSon, "%d;", NOMBRE_INTERVALLES);
    fprintf(pListeBaseSon, "%d;", NOMBRE_ECHANTILLONS);
    

    //write descripteur into base_descripteur

    //go to the end of pBaseDescriptorSon to write the new descriptor
    fseek(pBaseDescriptorSon,0,SEEK_END);//go to the end 

    //go to the start of pFileName
    fseek(pFileName,0,SEEK_SET);

    fprintf(pBaseDescriptorSon,"%d\n", currId);

    int count[NOMBRE_INTERVALLES];
    for(int k=0;k<NOMBRE_INTERVALLES;k++)
        count[k]=0;

    char *currLine = NULL;
    size_t lenght = 0;
    ssize_t read;
    Scientific currSc;
    int done=0;
    //datasize in value read
    int datasize=0;

    while ((read = getline(&currLine, &lenght, pFileName)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("lu %s", currLine);
        normalization(currLine,&currSc);
        done++;
        count[getIntervalle(currSc)]++;
        if(done==NOMBRE_ECHANTILLONS){
            //write in descriptor
            for(int k=0;k<NOMBRE_INTERVALLES;k++){
                fprintf(pBaseDescriptorSon,"%d;", count[k]);
                count[k]=0;
            }
            fprintf(pBaseDescriptorSon,"\n");
            done=0;
        }
        datasize++;
        //printf("calculer %d/(10^%d) \n",currSc.mantisse, currSc.exposant );

    }
    //write the last not NOMBRE_ECHANTILLONS size count
    for(int k=0;k<NOMBRE_INTERVALLES;k++){
        fprintf(pBaseDescriptorSon,"%d;", count[k]);
        count[k]=0;
    }

    fprintf(pBaseDescriptorSon,"\n");
    if (currLine)
           free(currLine);

    fclose(pFileName);
    fclose(pBaseDescriptorSon);

    fprintf(pListeBaseSon, "%d;", datasize);
    fprintf(pListeBaseSon, "%d", currId);
    fprintf(pListeBaseSon, "\n");
    fclose(pListeBaseSon);
   
    
    return 1;//Success
}
/*
TODO TRYING TO DEAL WITH WAVE

void printWAVE(wave inWave){
    printf("FileTypeBlocID = %s\n", inWave.FileTypeBlocID);
    printf("FileSize = %d\n", inWave.FileSize);
    printf("FileFormatID = %s\n", inWave.FileFormatID);
    printf("FormatBlocID = %s\n", inWave.FormatBlocID);
    printf("BlocSize = %d\n", inWave.BlocSize);
    printf("AudioFormat = %d\n", inWave.AudioFormat);
    printf("NbrCanaux = %d\n", inWave.NbrCanaux);
    printf("Frequence = %d\n", inWave.Frequence);
    printf("BytePerSec = %d\n", inWave.BytePerSec);
    printf("BytePerBloc = %d\n", inWave.BytePerBloc);
    printf("BitsPerSample =%d\n", inWave.BitsPerSample);
    printf("DataBlocID = %s\n", inWave.DataBlocID);
    printf("DataSize = %d\n", inWave.DataSize);
}
   

// index fileName trying to deal with wave files
int IndexFile(char fileName[]){

    // open files fileName, base_descripteur_son, liste_base_son
    errno = 0;
    FILE* pFileName = fopen(fileName, "rb");
    if(pFileName  == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-1);   //Err opening fileName
    }
    FILE* pBaseDescriptorSon = fopen("./sto/base_descripteur_son", "a+");
    if (pBaseDescriptorSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-2);  //Err opening pBaseDescriptorSon
    }
    FILE* pListeBaseSon = fopen("./sto/liste_base_son", "a+");
    if (pListeBaseSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-3);  //Err opening pListeBaseSon
    }

    //write descripteur into base_descripteur

    wave currWave;
    
    fread(&currWave.FileTypeBlocID, 4, 1, pFileName);
    if((currWave.FileTypeBlocID[0] != 'R') || (currWave.FileTypeBlocID[1] != 'I') || (currWave.FileTypeBlocID[2] != 'F') || (currWave.FileTypeBlocID[3] != 'F')){
           return -4;  //Err not RIFF
    }

    fread(&currWave.FileSize, 4, 1, pFileName);

    fread(&currWave.FileFormatID, 4, 1, pFileName);
    if((currWave.FileFormatID[0] != 'W') || (currWave.FileFormatID[1] != 'A') || (currWave.FileFormatID[2] != 'V') || (currWave.FileFormatID[3] != 'E')){
           return -5; // Err not WAVE
    }

    fread(&currWave.FormatBlocID, 4, 1, pFileName);
    fread(&currWave.BlocSize, 4, 1, pFileName);
    fread(&currWave.AudioFormat, 2, 1, pFileName);
    fread(&currWave.NbrCanaux, 2, 1, pFileName);
    fread(&currWave.Frequence, 4, 1, pFileName);
    fread(&currWave.BytePerSec, 4, 1, pFileName);
    fread(&currWave.BytePerBloc, 2, 1, pFileName);
    fread(&currWave.BitsPerSample, 2, 1, pFileName);
    fread(&currWave.DataBlocID, 4, 1, pFileName);
    fread(&currWave.DataSize, 4, 1, pFileName);
    if(DEBUG)
        printWAVE(currWave);
    
    //get DataSize, should be 36 bytes after the start, and should be 4 bytes long
    /*  VERSION WITHOUT WAVE
    int32_t DataSize;
    TODO fseek(pBaseDescriptorSon,40,SEEK_SET);
    fread(&DataSize, 4, 1, pFileName);
    
    if(DEBUG)
        printf("Datasize %d \n", DataSize);

    long* DATA = (long*)malloc(sizeof(long)*NOMBRE_ECHANTILLONS);
    */

    /*
    //go to the end of pBaseDescriptorSon to write the new descriptor
    fseek(pBaseDescriptorSon,0,SEEK_END);//go to the end 

    int position=currWave.FileSize-currWave.DataSize;
    fseek(pFileName,position,SEEK_SET);

    if(DEBUG){
        printf("on se place %d-%d = %d \n octets dans le fichier a indexer\n",currWave.FileSize, currWave.DataSize,position);
    }
    //nb_bits modulo nb_bits per windows +1 for reminder
    NOMBRE_FENETRES=(((currWave.DataSize)*8)/(currWave.BitsPerSample*NOMBRE_ECHANTILLONS))+1;
    if(DEBUG){
        printf("NOMBRE_FENETRES calcul: ((%d)*8)modulo(%d*%d) +1 \n",currWave.DataSize,currWave.BitsPerSample,NOMBRE_ECHANTILLONS);
        printf("NOMBRE_FENETRES = %d \n", NOMBRE_FENETRES);
        printf("Le fichier fait %d octets de données,soi %d bits, donc %d fenêtre de %d élements chacun de %d bits, on allou donc %d*%d*%d=%dbits dans data\n",currWave.DataSize,(currWave.DataSize)*8,NOMBRE_FENETRES,NOMBRE_ECHANTILLONS,currWave.BitsPerSample,currWave.BitsPerSample,NOMBRE_FENETRES,NOMBRE_ECHANTILLONS,NOMBRE_FENETRES*NOMBRE_ECHANTILLONS*currWave.BitsPerSample);
    }

    float lenght=1.f/(float)NOMBRE_INTERVALLES;

    int count[NOMBRE_ECHANTILLONS];
    for(int k=0;k<NOMBRE_ECHANTILLONS;k++)
        count[k]=0;

    //allocate BitsPerSample*NOMBRE_ECHANTILLONS*NOMBRE_FENETRES/8 bytes
    //currWave.DATA = (void*)malloc(currWave.BitsPerSample*NOMBRE_ECHANTILLONS*NOMBRE_FENETRES/8);
    currWave.DATA = (void*)malloc(currWave.DataSize);

    fread(currWave.DATA, (currWave.BitsPerSample)/8, NOMBRE_ECHANTILLONS*NOMBRE_FENETRES, pFileName);
    for(int i=0; i < NOMBRE_FENETRES; i++){
        for(int k=NOMBRE_ECHANTILLONS; k>0; k--){
            //count[]++;
            //printf("%f;",*(float*)(currWave.DATA+(NOMBRE_ECHANTILLONS-k+NOMBRE_ECHANTILLONS*i)*currWave.BitsPerSample));
            //fprintf(pBaseDescriptorSon, "%f;" ,*(float*)(currWave.DATA+(NOMBRE_ECHANTILLONS-k+NOMBRE_ECHANTILLONS*i)*currWave.BitsPerSample));
            fprintf(pBaseDescriptorSon, "%c;" ,*(char*)(currWave.DATA+(NOMBRE_ECHANTILLONS-k+NOMBRE_ECHANTILLONS*i)));
        }
            //fprintf(pBaseDescriptorSon, "%d;" ,count[k]);
        //fprintf(pBaseDescriptorSon, "\n");
    }

    fclose(pFileName);
    fclose(pBaseDescriptorSon);
   
    //update liste_base_son
    int currId = 0;
    int lastId=0;
    fseek(pListeBaseSon, -4,SEEK_END);
    fscanf(pListeBaseSon,"   %d", &lastId);
    currId = lastId+1;
    fprintf(pListeBaseSon,"%s;", fileName);
    fprintf(pListeBaseSon, "%d;", currWave.DataSize/NOMBRE_ECHANTILLONS/4);
    fprintf(pListeBaseSon, "%d;", NOMBRE_FENETRES);
    fprintf(pListeBaseSon, "%d;", currId);
    fprintf(pListeBaseSon, "\n");
    fclose(pListeBaseSon);
    
    return 1;//Success
}
*/