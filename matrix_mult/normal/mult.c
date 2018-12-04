#include <stdio.h>
#include <stdlib.h>

void multiply(int INPUTSIZE, unsigned long *bufferA, unsigned long *bufferB, unsigned long *result){

 int i, j, k; 
 for (i = 0; i < INPUTSIZE; i++) 
 { 
     for (j = 0; j < INPUTSIZE; j++) 
     {
         *(result + i*INPUTSIZE + j ) = 0; 
         for (k = 0; k < INPUTSIZE; k++) 
             *(result + i*INPUTSIZE + j) += *(bufferA + i*INPUTSIZE + k) * *(bufferB + k*INPUTSIZE + j); 
     } 
 }
 return;

}

int main(int argc, char** argv){
  int INPUTSIZE = 600;
  char input_nameA[500];
  char input_nameB[500];
  char result_name[500];
  snprintf(input_nameA, 500, "/tmp/mult/matrix_%d_A",INPUTSIZE);
  snprintf(input_nameB, 500, "/tmp/mult/matrix_%d_B",INPUTSIZE);
  snprintf(result_name, 500, "/tmp/mult/result_%d",INPUTSIZE);
  
  FILE *finputA = fopen(input_nameA, "rb");
  FILE *finputB = fopen(input_nameB, "rb");
  FILE *fresult = fopen(result_name, "wb");

  if (finputA == NULL || finputB == NULL || fresult == NULL) {
      printf("Warning! Couldn't read the input to file\n");
      return 0;
  } 
  else {
     unsigned long *bufferA = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
     unsigned long *bufferB = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
     unsigned long *result = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
      
    fread(bufferA,INPUTSIZE*INPUTSIZE*sizeof(unsigned long),1,finputA);
    fread(bufferB,INPUTSIZE*INPUTSIZE*sizeof(unsigned long),1,finputB);

    multiply(INPUTSIZE,bufferA,bufferB,result);

    fwrite(result,INPUTSIZE*INPUTSIZE*sizeof(unsigned long),1,fresult);
  
    fclose(finputA);
    fclose(finputB);
    fclose(fresult);
    return 0;
  }
  return 0;

}
