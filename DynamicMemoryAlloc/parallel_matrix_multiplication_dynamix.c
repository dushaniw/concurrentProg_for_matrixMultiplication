
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
	
//#define N 1000	
int rounds;
int N = 0; // no of columns and rows of a matrix
double **A, **B, **C; // declaring pointers for matrices of NxN size

void getArguments(int argc, char *argv[]);

int main (int argc, char *argv[])
{
	/* DECLARING VARIABLES */
	int i, j, m; // indices for matrix multiplication
	double t_1; // Execution time MEASURES
	getArguments(argc,argv);

	/* ALLOCATE MEMORY FOR MATRIX A */
	A = (double **) malloc( sizeof(double *) * N);
	for(i = 0;i < N; i++)
	{
		A[i] = (double *) malloc(sizeof(double *) * N);
	}

	/* ALLOCATE MEMORY FOR MATRIX B */
	B = (double **) malloc( sizeof(double *) * N);
	for(i = 0;i < N; i++)
	{
		B[i] = (double *) malloc(sizeof(double *) * N);
	}

	/* ALLOCATE MEMORY FOR MATRIX C */
	C = (double **) malloc( sizeof(double *) * N);
	for(i = 0;i < N; i++)
	{
		C[i] = (double *) malloc(sizeof(double *) * N);
	}

	/* FILLING MATRICES WITH RANDOM NUMBERS */
	srand ( time(NULL) );
	for(i = 0;i < N;i++) {
		for(j = 0;j < N;j++) {
			A[i][j] = (rand() % 10);
			B[i][j] = (rand() % 10);
		}
	}
	
	double st = omp_get_wtime();
	#pragma omp parallel for private(m,j)
	for(i = 0;i < N;i++) {
		for(j = 0;j < N;j++) {
			C[i][j] = 0.; // set initial value of resulting matrix C = 0
			for(m = 0;m < N;m++) {
				C[i][j] = A[i][m] * B[m][j] + C[i][j];
			}
		}
	}

	/* TIME MEASURE */
	double en = omp_get_wtime();
	printf("Parallel: %lf\n",en - st);

	/* FREE MEMORY */
	for(i = 0;i < N; i++){
		free(A[i]);
	}
	free(A);
	for(i = 0;i < N; i++){
		free(B[i]);
	}
	free(B);
	for(i = 0;i < N; i++){
		free(C[i]);
	}
	free(C);
}

void getArguments(int argc, char *argv[]){
	// Check the N
	if (argc != 2) {
        printf("Please give a valid number for N\n");
        exit(0);
    }
    N = (int) strtol(argv[1], (char **) NULL, 10);
    if (N == 0) {
    	printf("Please give a number for N more than 0\n");
        exit(0);	
    }
    rounds = (int) strtol(argv[2], (char **) NULL, 10);
    if (rounds == 0){
        printf("Please give a valid # for observations 0\n");
        exit(0);	
    }
}
    


