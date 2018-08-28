#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

#define PI 3.14159265

#define HIGH_LEVEL 5
#define LOW_LEVEL 0

#define DEBUG

typedef struct complex_num
{
	double real;
	double imag;
} complex_num_t;

complex_num_t complex_add(complex_num_t num_a, complex_num_t num_b);
complex_num_t complex_sub(complex_num_t num_a, complex_num_t num_b);
complex_num_t complex_mult(complex_num_t num_a, complex_num_t num_b);
complex_num_t complex_exp(double exp);

double sine(double arg);
double cosine(double arg);
long power(long base, long exp);

void fft(complex_num_t* time_domain, complex_num_t* transform, int size, int stride);
void print_complex_vector(complex_num_t* vector, long size);

long N;

complex_num_t* time_samples;
complex_num_t* freq_samples;

int main(int argc, char* argv[])
{
    if(argc != 2)
	{
		printf("Pass the parameter N of sample size 2^N as parameter only!\n");
		exit(1);
	}

	N = atoi(argv[1]);
	N = power(2, N);
	//N = power(2, 12);

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
	printf("Testing FFT:");
	printf("\n\n");
	#endif

	fft(time_samples, freq_samples, N, 1);

	#ifdef DEBUG
	printf("\nFFT: \n");
	print_complex_vector(freq_samples, N);
	#endif

	free(time_samples);
	free(freq_samples);

	printf("FINALIZED!\n");

	return 0;
}

void fft(complex_num_t* time_domain, complex_num_t* transform, int size, int stride)
{
	if(size == 1)
		transform[0] = time_domain[0];

	else
	{
		fft(time_domain, transform, size/2, 2*stride);
		fft(time_domain + stride, transform + size/2, size/2, 2*stride);

		int k = 0;
		for(k = 0; k <= size/2 - 1; k++)
		{
			complex_num_t t = transform[k];

			complex_num_t twiddle_factor;
			twiddle_factor = complex_exp(-2*PI*k/size);

			complex_num_t mult_term = complex_mult(twiddle_factor, transform[k+size/2]);

			transform[k] = complex_add(t, mult_term);
			transform[k+size/2] = complex_sub(t, mult_term);
		}
	}
}

complex_num_t complex_add(complex_num_t num_a, complex_num_t num_b)
{
	complex_num_t result;
	result.real = num_a.real + num_b.real;
	result.imag = num_a.imag + num_b.imag;

	return result;
}

complex_num_t complex_sub(complex_num_t num_a, complex_num_t num_b)
{
	complex_num_t result;
	result.real = num_a.real - num_b.real;
	result.imag = num_a.imag - num_b.imag;

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
		printf("[%ld]: %lf + i*%lf\n", i, vector[i].real, vector[i].imag);
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
