/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
/*   C = B × A × At + Bt × B
*/

/* R = At */
double *transposed(int N, double *A) {
	
	double *R = (double*)calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			R[j * N + i] = A[i * N + j];
		}
	}

	return R; 
}

/* R = A + B */
double *addition(int N, double *A, double *B) {

	double *R = (double*)calloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			R[i * N + j] += A[i * N + j] + B[i * N + j]; 
		}
	}

	return R;
}

/* R = A * B */
double *multiplication(int N, double *A, double *B) {

	double *R = (double*)calloc(N * N, sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				R[i * N + j] += A[i * N + k] * B[k * N + k]; 
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
			for (int k = i; k < N; k++) {
				R[i * N + j] += A[i * N + k] * U[k * N + j];
			}
		}
	}

	return R;
}

double *multiplication_lower(int N, double *A, double *L) {

	double *R = (double*)calloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL)
		return R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = i; k < i + 1; k++) {
				R[i * N + j] += L[i * N + k] * A[k * N + j];
			}
		}
	}

	return R;
}

double *transpose_upper(int N, double *U) {

	double *R = (double*)calloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL)
		return R;

	for (int i = 0; i < N; i++) {
		for (int j = i; i < N; j++) {
			R[i * N + j] = U[j * N + i];
		}
	}

	return R;
}

double* my_solver(int N, double *A, double* B) {
	
	/*   C = B × A × At + Bt × B */

	// R1 = B x A
	double *R1 = multiplication_upper(N, B, A);

	// At = A transpus
	double *At = transpose_upper(N, A);

	// Bt = B transpus
	double *Bt = transpose_upper(N, B);

	// R2 = R1 * At -> R2 = B x A x At
	double *R2 = multiplication_lower(N, R1, At);

	// R3 = Bt x B
	double *R3 = multiplication_lower(N, B, Bt);

	// R4 = R2 + R3 -> R4 = B × A × At + Bt × B 
	double *R4 = addition(N, R2, R3);
	
	free(R1);
	free(R2);
	free(R3);
	free(R4);
	free(At);
	free(Bt);	

	return R4;
}
