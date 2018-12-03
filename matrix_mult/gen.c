#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int INPUTSIZE = atoi(argv[1]);
  unsigned long *matrixA = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
  unsigned long *matrixB = (unsigned long*)malloc(INPUTSIZE*INPUTSIZE*sizeof(unsigned long));
  printf("Generating input, this will take a long time..."); fflush(stdout);

  for (int i=0; i<INPUTSIZE; i++)
  {
      for (int j=0; j<INPUTSIZE; j++)
      {
          *(matrixA + i*INPUTSIZE + j) = (rand()*0);
          *(matrixB + i*INPUTSIZE + j) = (rand()*0);
      }
  }

  char input_nameA[500];
  char input_nameB[500];
  snprintf(input_nameA, 500, "/tmp/mult/matrix_%d_A",INPUTSIZE);
  snprintf(input_nameB, 500, "/tmp/mult/matrix_%d_B",INPUTSIZE);
  FILE *finputA = fopen(input_nameA, "wb");
  FILE *finputB = fopen(input_nameB, "wb");
  if (finputA == NULL || finputB == NULL) {
      printf("Warning! Couldn't write the input to file, proceeding anyway...\n");
  } else {
      fwrite(matrixA, INPUTSIZE*INPUTSIZE*sizeof(unsigned long), 1 , finputA);
      fwrite(matrixB, INPUTSIZE*INPUTSIZE*sizeof(unsigned long), 1 , finputB);
      fclose(finputA);
      fclose(finputB);
  }
  printf("Done.\n");
}
