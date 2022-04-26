/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */

double* my_solver(int N, double *A, double *B) {

	double *fst = (double *)calloc(N * N, sizeof(double));

	int i;

	for (i = 0; i < N * N; i++) {
		fst[i] = B[i];
	}

	cblas_dtrmm(CblasRowMajor, CblasRight , CblasUpper, CblasTrans,
	CblasNonUnit, N, N, 1, A, N, fst, N);
	return NULL;

	return fst;
}
