#include "genFromMatrix.hpp"

bool genFromMatrix(int start, int end, int nVars, int nVarsI,
			int nDepend, int nDependI, vector<vector<float>> & values,
			vector<vector<float>> matrix) {

	int hMatrix = nVars * nDepend + nVarsI * nDependI + 1;
	float * A = (float*) malloc(sizeof(float) * hMatrix);
	float * C = (float*) malloc(sizeof(float) * nVars);
	float * pMatrix = vectorToPointer(matrix);
	bool error = false;

	for (int i = start; i < end && !error; ++i) {
		int nA = 0;

		for (int j = 0; j < nDepend; ++j)
			for (int k = 0; k < nVars; ++k) {
				A[nA] = values[i - j - 1][k];
				nA++;
			}

		for (int j = 0; j < nDependI; ++j)
			for (int k = 0; k < nVarsI; ++k) {
				A[nA] = values[i - j - 1][k + nVars];
				nA++;
			}

		A[hMatrix-1] = 1.0;
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
		    		1, nVars, hMatrix, 1, A, hMatrix, 
		    		pMatrix, nVars, 0, 
		    		C, nVars);

		for (int w = 0; w < nVars; w++) {
			error = error || isinf(C[w]) ||  isnan(C[w]);
			values[i][w] = C[w];
		}	
	}

	free(A);
	free(C);
	free(pMatrix);
	
	return error;
} 