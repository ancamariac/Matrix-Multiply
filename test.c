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

	// check memory allocation
	if (R == NULL)
		return NULL;

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
	double *At = (double*)calloc(N * N, sizeof(double));

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//At[j * N + i] = A[i * N + j];
			for (int k = 0; k < N; k++) {
				R[i * N + j] += A[i * N + k] * B[k * N + j];
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
	double *Lt = (double*)calloc(N * N, sizeof(double));


	// check memory allocation
	if (R == NULL)
		return R;

	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			// compute the transposed of L
			//Lt[j * N + i] = L[i * N + j];
			for (int k = j; k < N; k++) {
				R[i * N + j] += A[i * N + k] * L[k * N + j];
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
		for (int j = i; j < N; j++) {
			R[j * N + i] = U[i * N + j];
		}
	}

	return R;
}

void printMatrix(int N, double *M) {

    for (int i = 0; i < N * N; i++) {
        printf("%f ", M[i]);
    }

}

int main() {
	
	/*   C = B × A × At + Bt × B */

	// R1 = B x A

	double A[] = {1, 2, 1, 0, 1, 3, 0, 0, 1};
	double B[] = {1, 2, 1, 2, 3, 1, 2, 1, 1};

	double *R1 = multiplication_upper(3, B, A);
	printMatrix(3, R1);
	//if (R1 == NULL)
	//	return NULL;

	// At = A transpus
	double *At = transpose_upper(3, A);
	//printMatrix(3, At);
	//if (At == NULL)
	//	return NULL;

	// Bt = B transpus
	double *Bt = transposed(3, B);
	//printMatrix(3, Bt); printf("\n");
	if (Bt == NULL)
		return NULL;

	// R2 = R1 * At -> R2 = B x A x At
    
	double *R2 = multiplication_lower(3, R1, At);
	//printMatrix(3, R2);
	/*if (R2 == NULL)
		return NULL;*/

	// R3 = Bt x B
	double *R3 = multiplication(3, Bt, B);
	//printMatrix(3, R2); printf("\n");
	//printMatrix(3, R3); printf("\n");

	//if (R3 == NULL)
		//return NULL;

	// R4 = R2 + R3 -> R4 = B × A × At + Bt × B 
	double *R4 = addition(3, R2, R3);
	//printMatrix(3, R4); printf("\n");

	if (R4 == NULL)
		return NULL;
	
	free(R1);
	free(R2);
	free(R3);
	free(At);
	free(Bt);

	return 0;
}
