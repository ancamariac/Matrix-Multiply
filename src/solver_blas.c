/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */

/*   C = B × A × At + Bt × B   */

double* my_solver(int N, double *A, double *B) {

	int i = 0;

	double *R = (double*)malloc(N * N * sizeof(double));

    // check memory allocation
	if (R == NULL )
		return NULL;

	for (i = 0; i < N * N; i++) {
		R[i] = B[i];
	}

	/*   C = B × A × At + Bt × B */

	// R = B x A DxC
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit,
		N, N, 1, A, N, R, N);

	// R = R x At = B x A x At 
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit,
		N, N, 1, A, N, R, N);

	// R = Bt x B + R = B × A × At + Bt × B
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, 
	    N, N, N, 1.0, B, N, B, N, 1.0, R, N);

	return R;
}
