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

    /// ----------------------------------- DUPLICATION -----------------------------------

    char result_name2[500];
    snprintf(result_name2, 500, "/tmp/mult/result_%d_2", INPUTSIZE);

    FILE* finputA2 = fopen(input_nameA, "rb");
    FILE* finputB2 = fopen(input_nameB, "rb");
    FILE* fresult2 = fopen(result_name, "wb");

    unsigned long *bufferA2 = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
    unsigned long *bufferB2 = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
    unsigned long *result2 = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));

    fread(bufferA2, INPUTSIZE*INPUTSIZE*sizeof(unsigned long),1,finputA);
    fread(bufferB2, INPUTSIZE*INPUTSIZE*sizeof(unsigned long),1,finputB);

    multiply(INPUTSIZE, bufferA2, bufferB2, result2);

    fwrite(result2, INPUTSIZE*INPUTSIZE*sizeof(unsigned long),1,fresult);

    fclose(finputA2);
    fclose(finputB2);
    fclose(fresult2);

    int i = 0;
    int j = 0;

    int isDifferent = 0;

    for(i = 0; i < INPUTSIZE; i++){
        for(j = 0; j < INPUTSIZE; j++){
            if(*(result + i*INPUTSIZE + j) != *(result2 + i*INPUTSIZE + j)){
                isDifferent++;
            }
        }
    }

    if(isDifferent){
        printf("Fault detected!\n");
        FILE* fault_detected = fopen("/tmp/mult/fault_detected.txt", "w");
        fprintf(fault_detected, "%d\n", isDifferent);
    }
    else{
        printf("Not a single fault found!\n");
    }


    /// ---------------------------- END OF DUPLPICATION -----------------------------------
    return 0;
  }
  return 0;

}
