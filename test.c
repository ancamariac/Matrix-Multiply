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

    // check memory allocation
	if (R == NULL)
		return NULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
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

	// check memory allocation
	if (R == NULL)
		return R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
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

	double A[] = {5, 1, 1, 0, 4, 2, 0, 0, 2};
	double B[] = {1, 2, 1, 3, 2, 1, 2, 1, 1};

	double *R1 = multiplication_upper(3, B, A);
	
	//if (R1 == NULL)
	//	return NULL;

	// At = A transpus
	double *At = transpose_upper(3, A);

	//if (At == NULL)
	//	return NULL;

	// Bt = B transpus
	double *Bt = transpose_upper(3, B);

	if (Bt == NULL)
		return NULL;

	// R2 = R1 * At -> R2 = B x A x At
    
	double *R2 = multiplication_lower(3, R1, At);
    printMatrix(3, R2);
    printf("\n");
    

	/*if (R2 == NULL)
		return NULL;

	// R3 = Bt x B
	double *R3 = multiplication_lower(N, B, Bt);

	if (R3 == NULL)
		return NULL;

	// R4 = R2 + R3 -> R4 = B × A × At + Bt × B 
	double *R4 = addition(N, R2, R3);
	printf("hei555");

	if (R4 == NULL)
		return NULL;
	
	free(R1);
	free(R2);
	free(R3);
	free(At);
	free(Bt);*/

	return 0;
}
