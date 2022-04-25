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

	int i = 0, j = 0;
	double *R = (double*)malloc(N * N * sizeof(double));

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
    double *R = (double *)malloc(N * N * sizeof(double));

	if (R == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		register double *orig_pa = A + i * N;
		for (j = 0; j < N; ++j) {
			register double *orig_pa_cpy = orig_pa;
			register double *orig_pb = B + j;
			register double res = 0.0;
			for (k = 0; k < N; ++k) {
				res += *orig_pa_cpy * *orig_pb;
				orig_pa_cpy++;
				orig_pb += N;
			}
			R[i * N + j] = res;
		}
	}

	return R;
}

/* R = A * At */
double *upper_X_lower(int N, double *A) {

	int i = 0, j = 0, k = 0;
	double *R = (double*)malloc(N * N * sizeof(double));
	
    // check memory allocation
	if (R == NULL)
		return NULL;

	for (i = 0; i < N; i++) {
		register double *orig_pa = A + i * N;
		for (j = 0; j < N; j++) {
			register double *orig_pa_cpy = orig_pa + j;
			register double *orig_pb = A + j * N + j;
			register double res = 0.0;
			for (k = j; k < N; k++) {
				res += *orig_pa_cpy * *orig_pb;
				orig_pa_cpy++;
				orig_pb++;
				//R[i * N + j] += A[i * N + k] * A[j * N + k];
			}
		        R[i * N + j] = res;
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

double* my_solver(int N, double *A, double* B) {
	
	/*   C = B × A × At + Bt × B */

	// R1 = A x At
	double *R1 = upper_X_lower(N, A);
	
	if (R1 == NULL)
		return NULL;

	// R2 = B * R1 -> R2 = B x A x At
	double *R2 = multiplication(N, B, R1);

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
