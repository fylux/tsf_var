#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstring>

#include "../gen/genFromMatrix.hpp"
#include "../lls/lls.hpp"
#include "../util/Time.hpp"
#include "../util/vectorToPointer.hpp"
#include "../util/printMatrix.hpp"

using namespace std;

unsigned int nVars 	= 0;
unsigned int nVarsI = 0;
unsigned int nDepend = 0;
unsigned int nDependI = 0;
unsigned int nInstances = 0;
float noise = 0.0;

float nTraining = 1.0;


/**
Returns the norm of a m*n matrix
*/
float getVectorNorm(int m, int n, float * a) {
   	int i, j;
    float norm = 0.0;
    for( j = 0; j < n; ++j )
            for( i = 0; i < m; ++i )
            	norm += a[i*n+j] * a[i*n+j];
    
    return norm;
}

int main(int argc, char * argv[]) {
	Time t;
	t.start(1000000);

	//Arguments parsing
	for (int i = 1; i < argc - 1 ; i += 2) {
		if (strcmp(argv[i],"-training") == 0 )
			nTraining = atof(argv[i+1]);
		else {
			cerr << "Unknown argument " << argv[i] << endl;
			return -1;
		}
	}

	//Read main variables
	cin >> nVars;
	cin >> nDepend;
	cin >> nVarsI;
	cin >> nDependI;
	cin >> nInstances;

	cout << fixed << setprecision(3);

	
	const int totalVars = nVars + nVarsI;
	const int maxDepend = max(nDepend,nDependI);
	//Cols of A and rows of X
	int hMatrix = nDepend*nVars + nDependI*nVarsI + 1;
	//Total rows of A and B matrix
	const int rows = nInstances-maxDepend;
	//Rows for training
	const int rowsT = nTraining * rows;

	int mA = rows;
	int nA = hMatrix;
	int mB = rows;
	int nB = nVars;

	//Coherence checks
	if (mA < nA) {
		cerr << "More data is needed (m < n)" << endl;
		cerr << "M: " << mA << " N: " << nA << endl;
		return -1;
	}
	if (nTraining * rows <= maxDepend ) {
		cerr << "Insufficent training set" << endl;
		cout << nTraining << " "<<  rows << " " << maxDepend << endl;
		return -1;
	}
	if (nTraining < 0.0 || nTraining > 1.0) {
		cerr << "Invalidad training set" << endl;
		return -1;
	}


	vector<vector<float>> values(
		nInstances,
		vector<float>(totalVars)
		);

	vector<vector<float>> matrix(
		hMatrix,
		vector<float>(nVars)
		);

	//Read the data
	for (int i = 0; i < nInstances; ++i)
		for (int j = 0; j < totalVars; ++j)
			cin >> values[i][j];
	
	for (int i = 0; i < hMatrix; ++i)
		for (int j = 0; j < nVars; ++j)
			cin >> matrix[i][j];

	t.set();
	cout << "Time Reading: " << t.lastDiff() << endl;

/**************/

	#ifdef EXAHUSTIVE
	for (unsigned long long int r = pow(2,totalVars)-1; r > 0; --r) {

	vector<bool> conf(totalVars,false);
	
	nVars = 0;
	for (int i = 0; i < totalVars; ++i) {
		conf[i] = (r & ( 1 << i )) >> i;
		nVars += conf[i];
		cout << conf[i] << " ";
	}
	nVarsI = totalVars - nVars;

	int hMatrix = nDepend*nVars + nDependI*nVarsI + 1;
	int mA = rows;
	int nA = hMatrix;
	int mB = rows;
	int nB = nVars;

	#else
	vector<bool> conf(totalVars,true);
	for (int i = nVars; i < totalVars; ++i)
		conf[i]=false;

	#endif
	
	vector<vector<float>> matrixA (
		mA,
		vector<float>(nA)
		);

	vector<vector<float>> matrixB (
		mB,
		vector<float>(nB)
		);

	//Forecasting
	vector<vector<float>> matrixFC(
		nA,
		vector<float>(nB)
		);
	
	vector<vector<float>> valuesFC(
		nInstances,
		vector<float>(totalVars)
		);


	//////////////////////////////////////////////////////////////
	

	for (int i = 0; i < rowsT; ++i) { 
		int p = 0;
		for (int j = 0; j < totalVars; ++j) {
			if(conf[j]) {
				matrixB[i][p] = values[i + maxDepend][j];
				++p;
			}
		}
	}

	for (int z = 0; z < rowsT; ++z) {
		//Dependend Vars
		for (int i = 0; i < nDepend; ++i) {
			int p = 0;
			for (int j = 0; j < totalVars; ++j) {
				if (conf[j]) {
					matrixA[z][i * nVars + p] =
						values[z + (maxDepend - 1) - i][j];
					++p;
				}
			}
		}

		//Independend Vars
		for (int i = 0; i < nDependI; ++i) {
			int p=0;
			for (int j = 0; j < totalVars; ++j) {
				if (!conf[j]) {
					matrixA[z][nDepend * nVars + i * nVarsI + p] = 
						values[z + (maxDepend - 1) - i][j];
					++p;
				}
			}
		}
		
		//Const factor
		matrixA[z][hMatrix - 1] = 1;
	}
	//////////////////////////////////////////////////////////////

	//Matrix A and B for the LLS system
	float * A = vectorToPointer(matrixA);
	float * B = vectorToPointer(matrixB);

	t.set();
	
	//Solve LLS
	lls solver(mA,nA,A,mB,nB,B);
	int info = solver.solve();

	if (info != 0) {
		cerr << "Error " << info << " during LLS subroutine" << endl;
		printMatrix(matrixA);
		return -1;
	}

	#ifndef EXAHUSTIVE
 	cout << "Time Modeling: " << t.lastDiff() << endl;
	t.set();
	cout << "Time Solving: ";
	cout << t.lastDiff() << endl;
	#endif

	//Forecasting from obtained matrix
	for (int i = 0; i < nA; ++i)
		for (int j = 0; j < nB; ++j)
			matrixFC[i][j] = B[i*nB+j];

	for (int i = 0; i < nInstances; ++i)
		for (int j = 0; j < totalVars; ++j)
			valuesFC[i][j] = values[i][j];

	//Generated forecasted values
	genFromMatrix(rowsT, rows, nVars, nVarsI, nDepend,
					nDependI, valuesFC, matrixFC);


	#ifndef EXAHUSTIVE
	cout <<"Matrix X: " << endl;
	printMatrix(matrixFC);

	cout << "Original Matrix:" << endl;
	printMatrix(matrix);
	#endif

	cout << "RSS: (train)" << getVectorNorm(mB-nA,nB,&B[nA*nB]) / (rowsT*nB);

	//Residuals of forecasting
	float residual = 0.0;
	for (int i = 0; i < nInstances; ++i)
		for (int j = 0; j < totalVars; ++j)
			residual += pow(values[i][j]-valuesFC[i][j],2);

	residual = residual/((rows-rowsT)*nB);

	if (!isnan(residual) && !isinf(residual)) {
		cout << " RSS (forecast): " ;
		printf("%6.3f",residual);
	}
	cout << endl;

	free(A);
	free(B);

	#ifdef EXAHUSTIVE
	}
	#endif


	return 0;
}