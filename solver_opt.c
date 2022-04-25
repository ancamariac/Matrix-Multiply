/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
/*   C = B × A × At + Bt × B   */

/* R = A + B */
double *addition(int N, double *A, double *B) {

	double *R = (double*)malloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		register double res = 0;
		for (int j = 0; j < N; j++) {
			res += A[i * N + j] + B[i * N + j]; 
		}
		R[i * N + j] = res;
	}

	return R;
}

/* R = At * A */
double *multiplication_with_transpose(int N, double *A) {

	double *R = (double*)calloc(N * N, sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				R[i * N + j] += A[k * N + i] * A[k * N + j];
			}
		}
	}

	return R;
}
/* UPPER TRIANGULAR MATRIX FUNCTIONS */

double *multiplication_upper(int N, double *A, double *U) {

	double *R = (double*)calloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL)
		return R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < j + 1; k++) {
				R[i * N + j] += A[i * N + k] * U[k * N + j];
			}
		}
	}

	return R;
}

double *multiplication_lower(int N, double *A, double *L) {

	double *R = (double*)calloc(N * N, sizeof(double));

	// Lt = L transpus
	double *Lt = (double*)calloc(N * N, sizeof(double));

	if (Lt == NULL)
		return NULL;

	// transpose for upper tr matrix
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			Lt[j * N + i] = L[i * N + j];
		}
	}

	// check memory allocation
	if (R == NULL)
		return R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = j; k < N; k++) {
				R[i * N + j] += A[i * N + k] * Lt[k * N + j];
			}
		}
	}

	return R;
}

double* my_solver(int N, double *A, double* B) {
	
	/*   C = B × A × At + Bt × B */

	// R1 = B x A
	double *R1 = multiplication_upper(N, B, A);
	
	if (R1 == NULL)
		return NULL;

	// R2 = R1 * At -> R2 = B x A x At
	double *R2 = multiplication_lower(N, R1, A);

	if (R2 == NULL)
		return NULL;

	// R3 = Bt x B
	double *R3 = multiplication_with_transpose(N, B);

	if (R3 == NULL)
		return NULL;

	// R4 = R2 + R3 -> R4 = B × A × At + Bt × B 
	double *R4 = addition(N, R2, R3);

	if (R4 == NULL)
		return NULL;
	
	free(R1);
	free(R2);
	free(R3);
	
	return R4;	
}
