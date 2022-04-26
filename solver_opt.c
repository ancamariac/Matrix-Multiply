/*
 * Tema 2 ASC
 * 2022 Spring
 */

#include "utils.h"

#define MAX(A, B) ((A) > (B) ? (A) : (B))

/*
 * Add your optimized implementation here
 */
/*   C = B × A × At + Bt × B   */

/* R = A + B */
double *addition(int N, double *A, double *B) {

	int i = 0;
	double *R = (double*)malloc(N * N * sizeof(double));

	// check memory allocation
	if (R == NULL)
		return NULL;

	int N2 = N * N;
	
	for (i = 0; i < N2; i++) {
		R[i] = A[i] + B[i];
	}

	return R;
}

double *multiplication(int N, double *A, double *B) {

    int i = 0, j = 0, k = 0;
    double *R = (double *)calloc(N * N, sizeof(double));

	// check memory allocation
	if (R == NULL) {
		return NULL;
	}

	for (i = 0; i < N; i++) {

		register double *orig_a = A + i * N;
		register double *result = R + i * N; 
		
		for (k = 0; k < N; k++) {

			register double *pa = orig_a + k; 
			register double *pb = B + k * N;

			for (j = 0; j < N; j++) {
				result[j] += *pa * *(pb + j);
			}
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
		register int iN = i * N;
		register double *orig_pa = A + iN;

		for (j = i; j < N; j++) {

			register double res = 0.0;
			register int max = MAX(i, j);
			register double *pa = orig_pa + max;
			register double *pb = A + j * N + max;
			register int jN = j * N;

			for (k = max; k < N; k++) { 

				res += *pa * *pb;
				pa++;
				pb++;

			}

			R[iN + j] = res;
			R[jN + i] = res;
		}
	}

	return R;
}

double *multiplication_with_transpose(int N, double *A) {

	int i = 0, j = 0, k = 0;
	double *R = (double*)malloc(N * N * sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (i = 0; i < N; i++) {

		register double *orig_pa = A + i;
		register int iN = i * N;

		for (j = i; j < N; j++) {

			register double res = 0.0;
			register double *pa = orig_pa;
			register double *pb = A + j;
			register int jN = j * N;

			for (k = 0; k < N; k++) {
				res += *pa * *pb;
				pa += N;
				pb += N;
			}
			
			R[iN + j] = res;
			R[jN + i] = res;
		}
	}

	return R;
}

double* my_solver(int N, double *A, double* B) {
	
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
