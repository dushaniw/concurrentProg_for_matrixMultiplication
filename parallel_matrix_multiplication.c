#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
	
#define N 1000	
double A[N][N], B[N][N], C[N][N]; // declaring pointers for matrices of NxN size
int rounds;

int main (int argc, char *argv[])
{
    /* TAKE # of observation rounds to run the multiplication */
	if (argc != 2) {
        printf("Please give a observation # (# of times to run the program) \n");
        exit(0);
    }
    rounds = (int) atof(argv[1]);
    if (rounds == 0){
        printf("Please give a valid # for observations \n");
        exit(0);	
    }	
	/* DECLARING VARIABLES */
	int l = 0;
	double sum_elapsed = 0.0;
	double round_sum[rounds];
	double standardDeviation = 0.0;

    while (rounds > l){	// FOR EACH OBSERVATION ROUND
    	int i, j, m; // indices for matrix multiplication
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

		/* TIME MEASURE FOR THE OBSERVATION */
		double en = omp_get_wtime();
		printf("Parallel Execution Time for observation %d: %lf\n",l,en - st);
		sum_elapsed += en - st;
    	round_sum[l] = en - st;
		l++;
	} 
	printf("Average Time in seconds for parallel matrix multiplication : %.6f\n",(float)(sum_elapsed/rounds));
    for (int c = 0; c < rounds; c++){
    	standardDeviation += pow(round_sum[c] - (sum_elapsed/rounds), 2);
    }
    printf("Standard Deviation for parallel matrix multiplication : %.6f\n",(float)(sqrt(standardDeviation/rounds)));
	return 0;
}




