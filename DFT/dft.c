#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265

#define HIGH_LEVEL 5
#define LOW_LEVEL 0

//#define DEBUG

typedef struct complex_num
{
	double real;
	double imag;
} complex_num_t;

complex_num_t complex_add(complex_num_t num_a, complex_num_t num_b);
complex_num_t complex_mult(complex_num_t num_a, complex_num_t num_b);
complex_num_t complex_exp(double exp);

double sine(double arg);
double cosine(double arg);
long power(long base, long exp);

void dft(complex_num_t* time_domain, complex_num_t* transform);
void print_complex_vector(complex_num_t* vector, long size);

long N;

complex_num_t* time_samples;
complex_num_t* freq_samples;

complex_num_t* time_samples2;
complex_num_t* freq_samples2;

int main(int argc, char* argv[])
{
	N = power(2, 13);

	time_samples = (complex_num_t*) malloc(N * sizeof(complex_num_t));
	if(time_samples == NULL)
	{
		printf("Not enough memory!\n");
		exit(1);
	}

	freq_samples = (complex_num_t*) malloc(N * sizeof(complex_num_t));
	if(freq_samples == NULL)
	{
		printf("Not enough memory!\n");
		exit(1);
	}

	int i;
	for(i = 0; i < N; i++)
	{
		time_samples[i].real = (HIGH_LEVEL/((float)N))*i + LOW_LEVEL;
		time_samples[i].imag = 0;
	}

	memset(freq_samples, 0, N * sizeof(complex_num_t));

	#ifdef DEBUG
	printf("Testing DFT Naive:");
	printf("\n\n");
	#endif

	dft(time_samples, freq_samples);

	#ifdef DEBUG
	printf("\nDFT: \n");
	print_complex_vector(freq_samples, N);
	#endif

	FILE* file = fopen("tmp/dft/rDFT.txt", "w");
	if(file == NULL){
        printf("Error opening file!\n");
        exit(1);
	}

	for(i = 0; i < N; i++){
        fprintf(file, "%lf %lf\n", freq_samples[i].real, freq_samples[i].imag);
	}

	/// ------------------------------ DUPLICATION ------------------------------------------

	time_samples2 = (complex_num_t*) malloc(N * sizeof(complex_num_t));
	if(time_samples2 == NULL)
	{
		printf("Not enough memory!\n");
		exit(1);
	}

	freq_samples2 = (complex_num_t*) malloc(N * sizeof(complex_num_t));
	if(freq_samples2 == NULL)
	{
		printf("Not enough memory!\n");
		exit(1);
	}

	for(i = 0; i < N; i++)
	{
		time_samples2[i].real = (HIGH_LEVEL/((float)N))*i + LOW_LEVEL;
		time_samples2[i].imag = 0;
	}

	memset(freq_samples2, 0, N * sizeof(complex_num_t));

	dft(time_samples2, freq_samples2);

	file = fopen("tmp/dft/rDFT2.txt", "w");
	if(file == NULL){
        printf("Error opening file!\n");
        exit(1);
	}

	for(i = 0; i < N; i++){
        fprintf(file, "%lf %lf\n", freq_samples2[i].real, freq_samples2[i].imag);
	}

	/// ---------------------------- END OF DUPLICATION ------------------------------------------

	int isDifferent = 0;

	for(i = 0; i < N; i++){
        if(freq_samples[i].real != freq_samples2[i].real || freq_samples[i].imag != freq_samples2[i].imag){
            isDifferent++;
        }
	}

	if(isDifferent)
        printf("Fault detected!\n");
    else
        printf("Not found a single fault!\n");


	free(time_samples);
	free(freq_samples);
	free(time_samples2);
	free(freq_samples2);

	printf("FINALIZED!\n");

	return 0;
}

void dft(complex_num_t* time_domain, complex_num_t* transform)
{
	int i, j;
	for(i = 0; i < N; i++)
	{
		complex_num_t sum;
		sum.real = 0;
		sum.imag = 0;

		for(j = 0; j < N; j++)
		{
			complex_num_t time_val;
			time_val = time_domain[j];

			complex_num_t twiddle_factor;
			twiddle_factor = complex_exp(-2*PI*j*i/N);

			sum = complex_add(sum, complex_mult(time_val, twiddle_factor));
		}

		transform[i] = sum;
	}
}

complex_num_t complex_add(complex_num_t num_a, complex_num_t num_b)
{
	complex_num_t result;
	result.real = num_a.real + num_b.real;
	result.imag = num_a.imag + num_b.imag;

	return result;
}

complex_num_t complex_mult(complex_num_t num_a, complex_num_t num_b)
{
	complex_num_t result;
	result.real = (num_a.real * num_b.real) - (num_a.imag * num_b.imag);
	result.imag = (num_a.real * num_b.imag) + (num_a.imag * num_b.real);

	return result;
}

complex_num_t complex_exp(double exp) //pure imaginary
{
	complex_num_t result;
	result.real = cosine(exp);
	result.imag = sine(exp);

	return result;
}

void print_complex_vector(complex_num_t* vector, long size)
{
	long i;
	for(i = 0; i < size; i++)
	{
		printf("[%d]: %lf + i*%lf\n", i, vector[i].real, vector[i].imag);
	}
}

double sine(double arg)
{
	double result;
	double interm = arg;

	result = interm;

	interm = interm*arg*arg;
	result -= interm/6;

	interm = interm*arg*arg;
	result += interm/120;

	interm = interm*arg*arg;
	result -= interm/5040;

	interm = interm*arg*arg;
	result += interm/362880;

	return result;
}

double cosine(double arg)
{
	double result;
	double interm = 1;

	result = interm;

	interm = interm*arg*arg;
	result -= interm/2;

	interm = interm*arg*arg;
	result += interm/24;

	interm = interm*arg*arg;
	result -= interm/720;

	interm = interm*arg*arg;
	result += interm/40320;

	return result;
}

long power(long base, long exp)
{
	if(exp == 0)
	{
		return 1;
	}

	long result = base;

	int i;
	for(i = 1; i < exp; i++)
	{
		result = result*base;
	}

	return result;
}
