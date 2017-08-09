#include "printMatrix.hpp"

void printMatrix(int m, int n, float* v ) {
    int i, j;
    for( i = 0; i < m; ++i ) {
            for( j = 0; j < n; ++j ) 
            	printf("%6.6f ", v[i*n+j] );
            printf("\n");
    }
    printf("\n");
}

void printMatrix(vector<vector<float>> v ) {
    int m = v.size();
    int n = v[0].size();
    for(int i = 0; i < m; ++i ) {
            for(int j = 0; j < n; ++j ) 
            	printf("%6.6f ", v[i][j] );
            printf("\n");
    }
    printf("\n");
}