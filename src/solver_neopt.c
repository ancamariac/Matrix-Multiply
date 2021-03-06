/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

#define MAX(A, B) ((A) > (B) ? (A) : (B))

/*
 * Add your unoptimized implementation here
 */
/*   C = B × A × At + Bt × B   */

/* R = A + B */
double *addition(int N, double *A, double *B) {

	int i = 0, j = 0;
	double *R = (double*)calloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL)
		return NULL;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			R[i * N + j] += A[i * N + j] + B[i * N + j]; 
		}
	}

	return R;
}

double *multiplication(int N, double *A, double *B) {

    int i = 0, j = 0, k = 0;
    double *result = (double *)calloc(N * N, sizeof(double));

	// check memory allocation
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			for (k = 0; k < N; ++k) {
				result[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}

	return result;
}

/* R = A * At */
double *upper_X_lower(int N, double *A) {

	int i = 0, j = 0, k = 0;
	double *R = (double*)calloc(N * N, sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = MAX(i, j); k < N; k++) {
				R[i * N + j] += A[i * N + k] * A[j * N + k];
			}
		}
	}

	return R;
}

double *multiplication_with_transpose(int N, double *A) {

	int i = 0, j = 0, k = 0;
	double *R = (double*)calloc(N * N, sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				R[i * N + j] += A[k * N + i] * A[k * N + j];
			}
		}
	}

	return R;
}

double *my_solver(int N, double *A, double* B) {
	
	/*   C = B × A × At + Bt × B */

	// R1 = A x At
	double *R1 = upper_X_lower(N, A);

	// R2 = B * R1 -> R2 = B x A x At
	double *R2 = multiplication(N, B, R1);

	// R3 = Bt x B
	double *R3 = multiplication_with_transpose(N, B);

	// R4 = R2 + R3 -> R4 = B × A × At + Bt × B 
	double *R4 = addition(N, R2, R3);
	
	free(R1);
	free(R2);
	free(R3);
	
	return R4;
}
