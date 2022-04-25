/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
/*
 * Add your unoptimized implementation here
 */
/*   C = B × A × At + Bt × B
*/


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
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
/* R = A * At */
double *upper_X_lower(int N, double *A, double *B) {

	double *R = (double*)calloc(N * N, sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = j; k < N; k++) {
				R[i * N + j] += A[i * N + k] * A[j * N + k];
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

void printMatrix(int N, double *M) {

    for (int i = 0; i < N * N; i++) {
        printf("%f ", M[i]);
    }

}
/* R = A * B */

//sum += B[i * N + k] * At[k * N + j];

/*	for (i = 0; i < N; i++) {
		register double *orig_B = &B[i * N];
		register double *orig_fst = &fst[i * N]; 
		for (k = 0; k < N; k++) {
			register double idxB = orig_B[k];
			register double *orig_At = &At[k * N];
			for (j = 0; j <= k; j++) {
				orig_fst[j] += idxB * orig_At[j];
			}
		}
	}
*/
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
				//result+=N;
			}
		}
	}

	return R;
}

double *multiply_matrix(int N, double *A, double *B) {
    int i = 0, j = 0, k = 0;
    double *R = (double *)malloc(N * N * sizeof(double));

	// check memory allocation
	if (R == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		register double *orig_pa = A + i * N;
		for (j = 0; j < N; ++j) {
			register double res = 0.0;
			register double *pa = orig_pa;
			register double *pb = B + j;
			for (k = 0; k < N; ++k) {
				res += *pa * *pb;
				pa++;
				pb += N;
			}
			R[i * N + j] = res;
		}
	}

	return R;
}

/* Find transpose of a regular matrix */
double *transpose_matrix(int N, double *A) {
	int i, j;

	double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result[j * N + i] = A[i * N + j];
		}
	}

	return result;
}


int main() {
	
	/*   C = B × A × At + Bt × B */

	// R1 = B x A

	double A[] = {1, 2, 1, 0, 1, 2, 0, 0, 1};
	double B[] = {1, 2, 1, 2, 3, 1, 2, 1, 1};

	// At = A transpus
	double *At = transpose_matrix(3, A);

	double *R1 = multiply_matrix(3, A, At);
	printMatrix(3, R1);
	printf("\n");
	double *R2 = multiplication(3, A, At);
	printMatrix(3, R2);
	//if (R1 == NULL)
	//	return NULL;

	// At = A transpus
	//double *At = transpose_upper(3, A);
	//printMatrix(3, At);
	//if (At == NULL)
	//	return NULL;

	// Bt = B transpus
	/*double *Bt = transposed(3, B);
	//printMatrix(3, Bt); printf("\n");
	if (Bt == NULL)
		return NULL;*/

	// R2 = R1 * At -> R2 = B x A x At
    
	//double *R2 = multiplication_lower(3, R1, At);
	//printMatrix(3, R2);
	/*if (R2 == NULL)
		return NULL;*/

	// R3 = Bt x B
	//double *R3 = multiplication_with_first_transpose(3, B);
	//printMatrix(3, R3);
	//printMatrix(3, R3); printf("\n");
	//printMatrix(3, R3); printf("\n");

	//if (R3 == NULL)
		//return NULL;

	// R4 = R2 + R3 -> R4 = B × A × At + Bt × B 
	//double *R4 = addition(3, R2, R3);
	//printMatrix(3, R4); printf("\n");

	//if (R4 == NULL)
		//return NULL;
	
	free(R1);
	//free(R2);
	//free(R3);
	//free(At);
	//free(Bt);

	return 0;
}
