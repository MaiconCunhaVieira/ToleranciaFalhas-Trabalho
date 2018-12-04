#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int INPUTSIZE = atoi(argv[1]);
  char input_nameA[500];
  char input_nameB[500];
  char result_name[500];
  snprintf(input_nameA, 500, "matrix_%d_A",INPUTSIZE);
  snprintf(input_nameB, 500, "matrix_%d_B",INPUTSIZE);
  snprintf(result_name, 500, "result_%d",INPUTSIZE);
  FILE *finputA = fopen(input_nameA, "rb");
  FILE *finputB = fopen(input_nameB, "rb");
  FILE *fresult = fopen(result_name, "rb");
  if (finputA == NULL || finputB == NULL) {
      printf("Warning! Couldn't read the input to file, proceeding anyway...\n");
  } else {
     unsigned long *buffer = (unsigned long*)malloc(sizeof(unsigned long));
      
     printf("%s\n",input_nameA);
     for (int i=0; i<INPUTSIZE; i++)
     {
         for(int j=0; j<INPUTSIZE; j++)
         {  
            fread(buffer,sizeof(unsigned long),1,finputA);
            printf("%lu ",*buffer);
         }
         printf("\n");
     }

     printf("%s\n",input_nameB);
     for (int i=0; i<INPUTSIZE; i++)
     {
         for(int j=0; j<INPUTSIZE; j++)
         {  
            fread(buffer,sizeof(unsigned long),1,finputB);
            printf("%lu ",*buffer);
         }
         printf("\n");
     }

     if(fresult != NULL) {
       printf("%s\n",result_name);
       for (int i=0; i<INPUTSIZE; i++)
       {
           for(int j=0; j<INPUTSIZE; j++)
           {  
              fread(buffer,sizeof(unsigned long),1,fresult);
              printf("%lu ",*buffer);
           }
           printf("\n");
       }
       fclose(fresult);
     }
  
  fclose(finputA);
  fclose(finputB);
  printf("Done.\n");
  }
}
