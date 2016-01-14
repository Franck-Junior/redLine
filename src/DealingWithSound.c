#include "DealingWithSound.h"

int DEBUG=1;
char separator=';';

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
    fprintf(pListeBaseSon,"%s%c", fileName,separator);
    fprintf(pListeBaseSon, "%d%c", NOMBRE_INTERVALLES,separator);
    fprintf(pListeBaseSon, "%d%c", NOMBRE_ECHANTILLONS,separator);
    

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
                fprintf(pBaseDescriptorSon,"%d%c", count[k],separator);
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
        fprintf(pBaseDescriptorSon,"%d%c", count[k],separator);
        count[k]=0;
    }

    fprintf(pBaseDescriptorSon,"\n");
    if (currLine)
           free(currLine);

    fclose(pFileName);
    fclose(pBaseDescriptorSon);

    fprintf(pListeBaseSon, "%d%c", datasize,separator);
    fprintf(pListeBaseSon, "%d", currId);
    fprintf(pListeBaseSon, "\n");
    fclose(pListeBaseSon);
   
    
    return 1;//Success
}

void lineIntoArray(int* array,int arraySize, char* read ){

}

void avg(FILE* pBaseDescriptor, float *array,int searchedNOMBRE_INTERVALLES, int arraySize){
         char read[1024];
         fscanf(pBaseDescriptor, "%s", read);
        //printf("read = %s\n",read);
        //TODO function
        int achieved=0;
        while(arraySize > achieved && read[strlen(read)-1]==separator){
            int i=0;
            char temp[1024];
            strcpy(temp,""); 
            float done=-1.f;
            float currAvg=0.f;
            int tempInt;
            while(read[i+1]!=NULL){
                if(read[i]==separator){
                    tempInt=atoi(strncat(temp,read,i));
                    strcpy(temp,""); 
                    memcpy(read,&read[i+1],strlen(&read[i]));
                    currAvg+=done*tempInt;
                    done+=(2.f/((float)arraySize));
                    printf("done=%f\n",done);
                    i=0; 
                }
               // printf("read= %c\n",read[i]);
                i++;
        }
        //avg premiere ligne
        array[achieved]=currAvg;
        printf("Avg =%f\n",array[achieved]);
        achieved++;
        fscanf(pBaseDescriptor, "%s", read);
        printf("read = %s\n",read);
    }
    
}

int foundAudio(int searchedId,int searchedDataSize,int jingleId,int jingleDataSize, int searchedNOMBRE_INTERVALLES){
    FILE* pBaseDescriptorSonSearched = fopen("./sto/base_descripteur_son", "r");
    if (pBaseDescriptorSonSearched == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-1);  //Err opening pBaseDescriptorSon
    }


    //get to the off set of each descriptor
    char *currLine = NULL;
    size_t lenght = 0;
    ssize_t read;
    int doneSearched=0;
    int doneJingle=0;

    int foundSearch=0;
    int foundJingle=0;
    while ((read = getline(&currLine, &lenght, pBaseDescriptorSonSearched)) != -1) {
        if(!foundSearch)
            doneSearched+=read;
        if(!foundJingle)
            doneJingle+=read;
        
        //printf("Retrieved line of length %zu :\n", read);
        //printf("lu %s", currLine);
        if(atoi(currLine)==searchedId)
            foundSearch++;
        if(atoi(currLine)==jingleId)
            foundJingle++;
        if(foundSearch && foundJingle)
            break;
    }
    int offSetSearched=doneSearched;
    int offSetJingle=doneJingle;
    fseek(pBaseDescriptorSonSearched,0,SEEK_SET);
    FILE* pBaseDescriptorSonJingle=pBaseDescriptorSonSearched;

    fseek(pBaseDescriptorSonSearched,offSetSearched,SEEK_SET);
    fseek(pBaseDescriptorSonJingle,offSetJingle,SEEK_SET);

    float arraySearchForSearch[(searchedDataSize/NOMBRE_ECHANTILLONS)+1];
    float arrayJingleForSearch[(searchedDataSize/NOMBRE_ECHANTILLONS)+1];
    avg(pBaseDescriptorSonJingle,arrayJingleForSearch,searchedNOMBRE_INTERVALLES,(searchedDataSize/NOMBRE_ECHANTILLONS)+1);
    avg(pBaseDescriptorSonSearched,arrayJingleForSearch,searchedNOMBRE_INTERVALLES,(searchedDataSize/NOMBRE_ECHANTILLONS)+1);
    //now compute average on each line

    
    //fillFromBaseDescriptorSon(pBaseDescriptorSon, arrayJingleForSearch,)

    return 0;
}


void fillFromListeBaseSon(FILE* pListeBaseSon, char* searchedfileName,int *searchedNOMBRE_INTERVALLES, int* searchedNOMBRE_ECHANTILLONS,int* searchedDataSize,int *searchedId){
    char read[1024];
    fscanf(pListeBaseSon, "%s", read);
    //printf("read = %s\n",read);
    //TODO function
    int i=0;
    char temp[1024];
    strcpy(temp,""); 
    int done=0;
    while(read[i]!=NULL){
        if(read[i]==separator){
            switch(done){
                case 0:
                    strncat(temp,read,i);
                    strcpy(searchedfileName,temp);
                    break;
                case 1:
                    *searchedNOMBRE_INTERVALLES=atoi(strncat(temp,read,i));
                    break;
                case 2:
                    *searchedNOMBRE_ECHANTILLONS=atoi(strncat(temp,read,i));
                    break;
                case 3:
                    *searchedDataSize=atoi(strncat(temp,read,i));
                    break;                    
            }
            done++;
            strcpy(temp,""); 
            memcpy(read,&read[i+1],strlen(&read[i]));
            //printf("new read=%s\n",read);
            i=0; 
        }
       // printf("read= %c\n",read[i]);
        i++;
        if(read[i]==NULL){
            *searchedId=atoi(strncat(temp,read,i));
            strcpy(temp,"");
        }
    }
    /*if(DEBUG){
        printf("\n");
        printf("searchedfileName = %s\n", searchedfileName);
        printf("searchedNOMBRE_INTERVALLES = %d\n", *searchedNOMBRE_INTERVALLES);
        printf("searchedNOMBRE_ECHANTILLONS = %d\n", *searchedNOMBRE_ECHANTILLONS);
        printf("searchedDataSize = %d\n", *searchedDataSize);
        printf("searchedId = %d\n",*searchedId);
        printf("\n");
    }*/
}


int searchAudio(char *searched){

    FILE* pListeBaseSon = fopen("./sto/liste_base_son", "a+");
    if (pListeBaseSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-1);  //Err opening pListeBaseSon
    }

    //get the indexation data of searched
    char searchedfileName[TAILLE_MAX_CHEMIN]; 
    int searchedNOMBRE_INTERVALLES;
    int searchedNOMBRE_ECHANTILLONS;
    int searchedDataSize;
    int searchedId;
    int lastId=0;

    //Détermination  du nombre d'élément de la pListeBaseSon base fileName
    fseek(pListeBaseSon, -2,SEEK_END);
    fscanf(pListeBaseSon,"   %d", &lastId);
    rewind(pListeBaseSon);
    if(DEBUG)
            printf("lastId = %d \n",lastId); 

    int nFound=0;
    while(nFound!=-1 && nFound < lastId){
        nFound++;
        fillFromListeBaseSon(pListeBaseSon,searchedfileName,&searchedNOMBRE_INTERVALLES,&searchedNOMBRE_ECHANTILLONS,&searchedDataSize,&searchedId);
        if(strcmp(searchedfileName,searched)==0)
            nFound=-1;
        if(DEBUG)
            printf("searched %s currfileName %s \n",searched,searchedfileName); 
    }
    //searched not idexed
    if(nFound!=-1){
        if(DEBUG)
            printf("searched not idexed\n"); 
        return -1;
    }
    if(DEBUG)
            printf("found at id = %d\n",searchedId); 
    nFound=0;

    rewind(pListeBaseSon);

    char jinglefileName[TAILLE_MAX_CHEMIN]; 
    int jingleNOMBRE_INTERVALLES;
    int jingleNOMBRE_ECHANTILLONS;
    int jingleDataSize;
    int jingleId;
    for(int i=0;i<lastId;i++){
    //for each idexed file
        fillFromListeBaseSon(pListeBaseSon,jinglefileName,&jingleNOMBRE_INTERVALLES,&jingleNOMBRE_ECHANTILLONS,&jingleDataSize,&jingleId);
        //check if possible candidat
        if(jingleId != searchedId && jingleNOMBRE_INTERVALLES==searchedNOMBRE_INTERVALLES && jingleNOMBRE_ECHANTILLONS == searchedNOMBRE_ECHANTILLONS){
            switch(foundAudio(searchedId,searchedDataSize,jingleId,jingleDataSize, searchedNOMBRE_INTERVALLES)){
                case 1:
                printf("\nVotre searched correspond au fichier %s\n", jinglefileName);
                nFound++;
                break;

                case 0:
                //printf("\nVotre searched ne correspond pas au fileName %s\n", fileName);
                break;

                case -1:
                printf("\nErreur: Impossible d'ouvrir le descriteur\n\n");
                return -1; //Erreur
                break;

                case -2:
                printf("\nErreur: Le programme rencontre un probleme dans la recherche des fichiers\n\n");
                return -1; //Erreur
                break;

                case -3:
                printf("\nErreur: Le programme rencontre un probleme dans la recherche des fichiers\n\n");
                return -1; //Erreur
                break;

                default:
                printf("\nUne erreur inopinee s'est produite\n");
                return -1; //Erreur
                break;
            }
        }
    }

     if(nFound==0){
        printf("\nAucun fileName ne correspond a votre extrait %s\n", jinglefileName);
    }

    return nFound;  //renvoie le ombre de fichiers concluants

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