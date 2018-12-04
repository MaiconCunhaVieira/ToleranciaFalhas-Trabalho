#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#define DEBUG

void multiply(double** matrix_a, double** matrix_b, double** matrix_result);
void print_square_matrix(double** matrix, long size);

double **matrix_a;
double **matrix_b;
double **matrix_result;

double **matrix_a2;
double **matrix_b2;
double **matrix_result2;

long MATRIX_SIZE;

int main(int argc, char* argv[])
{
	MATRIX_SIZE = 700;

	srand(time(NULL));

	matrix_a = (double**) malloc(MATRIX_SIZE * sizeof(double*));
	matrix_b = (double**) malloc(MATRIX_SIZE * sizeof(double*));
	matrix_result = (double**) malloc(MATRIX_SIZE * sizeof(double*));

	if(matrix_a == NULL || matrix_b == NULL || matrix_result == NULL)
	{
		printf("Not enough memory!\n");
		exit(1);
	}

	int i;
	int j;
	for(i = 0; i < MATRIX_SIZE; i++)
	{
		matrix_a[i] = (double*) malloc(MATRIX_SIZE * sizeof(double));
		matrix_b[i] = (double*) malloc(MATRIX_SIZE * sizeof(double));
		matrix_result[i] = (double*) malloc(MATRIX_SIZE * sizeof(double));

		if(matrix_a[i] == NULL || matrix_b[i] == NULL || matrix_result[i] == NULL)
		{
			printf("Not enough memory!\n");
			exit(1);
		}
	}

    // READ A from file!
	FILE* fileA = fopen("a.txt", "r");
	if(fileA == NULL){
        printf("Error opening file a.txt!\n");
        exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            fscanf(fileA, "%lf ", &matrix_a[i][j]);
        }
	}
	fclose(fileA);
	//free(fileA);

	// READ B from file!
	FILE* fileB = fopen("b.txt", "r");
	if(fileB == NULL){
        printf("Error opening file b.txt!\n");
        exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            fscanf(fileB, "%lf ", &matrix_b[i][j]);
        }
	}
	fclose(fileB);
	//free(fileB);

	#ifdef DEBUG
	printf("Testing Matrix Multiplication...\n");
	printf("Matrix A:\n");
	print_square_matrix(matrix_a, MATRIX_SIZE);
	printf("\nMatrix B:\n");
	print_square_matrix(matrix_b, MATRIX_SIZE);
	#endif

	multiply(matrix_a, matrix_b, matrix_result);

	#ifdef DEBUG
	printf("\nMatrix result A*B:\n");
	print_square_matrix(matrix_result, MATRIX_SIZE);
	#endif

	// WRITE R to file!
	FILE* file = fopen("rMM.txt", "w");
	if(file == NULL){
        printf("Error opening file rMM.txt!\n");
        exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            fprintf(file, "%lf ", matrix_result[i][j]);
        }
        fprintf(file, "\n");
	}

	/// --------------------------------------------- DUPLICATION -----------------------------------------

	matrix_a2 = (double**) malloc(MATRIX_SIZE * sizeof(double*));
	matrix_b2 = (double**) malloc(MATRIX_SIZE * sizeof(double*));
	matrix_result2 = (double**) malloc(MATRIX_SIZE * sizeof(double*));

	if(matrix_a2 == NULL || matrix_b2 == NULL || matrix_result2 == NULL)
	{
		printf("Not enough memory!\n");
		exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++)
	{
		matrix_a2[i] = (double*) malloc(MATRIX_SIZE * sizeof(double));
		matrix_b2[i] = (double*) malloc(MATRIX_SIZE * sizeof(double));
		matrix_result2[i] = (double*) malloc(MATRIX_SIZE * sizeof(double));

		if(matrix_a2[i] == NULL || matrix_b2[i] == NULL || matrix_result2[i] == NULL)
		{
			printf("Not enough memory!\n");
			exit(1);
		}
	}

    // READ A from file!
	fileA = fopen("a.txt", "r");
	if(fileA == NULL){
        printf("Error opening file a.txt!\n");
        exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            fscanf(fileA, "%lf ", &matrix_a2[i][j]);
        }
	}
	fclose(fileA);

	// READ B from file!
	fileB = fopen("b.txt", "r");
	if(fileB == NULL){
        printf("Error opening file b.txt!\n");
        exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            fscanf(fileB, "%lf ", &matrix_b2[i][j]);
        }
	}
	fclose(fileB);

	multiply(matrix_a2, matrix_b2, matrix_result2);

	// WRITE R to file!
	file = fopen("rMM.txt", "w");
	if(file == NULL){
        printf("Error opening file rMM.txt!\n");
        exit(1);
	}

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            fprintf(file, "%lf ", matrix_result2[i][j]);
        }
        fprintf(file, "\n");
	}

	/// ------------------------------------------------- END OF DUPLICATION ---------------------------------------

	int isDifferent = 0;

	for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            if(matrix_result[i][j] != matrix_result2[i][j]){
                isDifferent++;
            }
        }
	}

	if(isDifferent)
        printf("Fault detected!\n");
	else
        printf("Not a single fault found!\n");

	printf("FINALIZED!\n");

	return 0;
}

void multiply(double** matrix_a, double** matrix_b, double** matrix_result)
{
	int i;
	int j;
	int k;

	for(i = 0; i < MATRIX_SIZE; i++)
	{
		for(j = 0; j < MATRIX_SIZE; j++)
		{
			double sum = 0;
			for(k = 0; k < MATRIX_SIZE; k++)
			{
				sum += matrix_a[i][k] * matrix_b[k][j];
			}

			matrix_result[i][j] = sum;
		}
	}
}

void print_square_matrix(double** matrix, long size)
{
	int i;
	int j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			printf("[%d][%d] = %lf\n", i, j, matrix[i][j]);
		}
	}
}
