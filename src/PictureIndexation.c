#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// #include<indexationImage.h>

void nBitQuantificator(int n, int pixelLevel, int*T){
  int j;
  pixelLevel = pixelLevel-(int)pow(2,7);
  for(j = 7; j > 7-n; j--){
      if(pixelLevel >= 0)
	*(T+7-j) =  1;
      else{
	*(T+7-j) =  0;
	pixelLevel = pixelLevel+(int)pow(2,j);
      }
      pixelLevel = pixelLevel-(int)pow(2,j-1);
        
  }

}
  
// void Quantification (File* F, File* Quant, int n){
//   F fopen("sijdeiz","r");
//   Quant fopen("sijdsdeiz","w");
//   int tab[8];
//   while(!eof(F)){
//     fscanf(F,"%d",pixelLevel);
//     nBitQuantificator(2,pixelLevel,tab);
//     fprintf(Quant,"%d",tab);  
//   }
//   fclose(F);
// }

int main(void){
 int i,T[8]={0};
 
 nBitQuantificator(8,3,T);
 for(i = 0; i < 8; i++){
   printf("Poids %d : %d\n",7-i,*(T+i));
 }
 return 0;
 
}