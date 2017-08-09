#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <random>
#include <vector>

#include "genFromMatrix.hpp"
#include "../util/Time.hpp"
#include "../util/printMatrix.hpp"


using namespace std;

unsigned int nVars 	= 0;
unsigned int nVarsI = 0;
unsigned int nDepend = 0;
unsigned int nDependI = 0;
unsigned int nInstances = 0;
float noise = 0.0;

bool error;
int attemps = 3;

//Random values generators
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> disData(-10, 10);
uniform_real_distribution<float> disMatrix(-1, 1);
uniform_real_distribution<float> disDefaultNoise(-0.01, 0.01);

int main(int argc, char ** argv) {
	Time t;
	t.start(1000000);
	
	//Arguments parsing
	for (int i = 1; i < argc - 1; i += 2) {

		if (strcmp(argv[i],"-var") == 0 )
			nVars = atoi(argv[i+1]);
		else if (strcmp(argv[i],"-ivar") == 0 )
			nVarsI = atoi(argv[i+1]);
		else if (strcmp(argv[i],"-dep") == 0 )
			nDepend = atoi(argv[i+1]);
		else if (strcmp(argv[i],"-idep") == 0 )
			nDependI = atoi(argv[i+1]);
		else if (strcmp(argv[i],"-instances") == 0 )
			nInstances = atoi(argv[i+1]);
		else if (strcmp(argv[i],"-noise") == 0 ) 
			noise = atof(argv[i+1]);
		else {
			cerr << "Unknown argument " << argv[i] << endl;
			return -1;
		}
	}

	//Coherence checks
	if (!nVars || !nDepend || !nInstances || 
		(nVarsI > 0 && nDependI == 0) || 
		(nVarsI == 0 && nDependI > 0)) {
		cerr << "Missing arguments" << endl;
		cerr << "./gen -var N -dep N -instances N [-ivar N -idep N] [-noise R]" << endl;
		return -1;
	}
	if (noise > 1.0 || noise < 0.0) {
		cerr << "Invalid noise value" << endl;
		return -1;
	}

	if (nInstances <= max(nDepend,nDependI)) {
		cerr << "More instances are required" << endl;
		return -1;
	}


	const int totalVars = nVars + nVarsI;
	const int hMatrix = nDepend * nVars + nDependI * nVarsI + 1;

	vector<vector<float>> values(
		nInstances,
		vector<float>(totalVars)
		);


	vector<vector<float>> matrix(
		hMatrix,
		vector<float>(nVars)
		);

	vector<vector<float>> valuesI(
		nInstances,
		vector<float>(nVarsI)
		);

	vector<vector<float>> matrixI(
		nDependI * nVarsI + 1,
		vector<float>(nVarsI)
		);

	//Try again if number generated were too big or small
	do { 
		error = false;
		attemps--;

		if (nVarsI > 0) {
			//Generate random values
			for (int i = 0; i < nVarsI; ++i) {
				for (int j = 0; j < nInstances; ++j)
					valuesI[j][i] = disData(gen);
			}


			//We use the variable nDependI although it could be random
			//Initial indepedent values
			/*for (int i = 0; i < nVarsI; ++i) {
				float randValue = disData(gen);
				for (int j = 0; j < nDependI; ++j)
					valuesI[j][i] = disData(gen);//randValue + disDefaultNoise(gen) * randValue;
			}

			//Matrix X for independente values
			for (int i = 0; i < nDependI * nVarsI + 1 ; ++i)
				for (int j = 0; j < nVarsI ; ++j) {
					int diagonalDeviation = ((i-j)*(i-j)+1);
					matrixI[i][j] =  0.1+disMatrix(gen)/diagonalDeviation;
				}

			//Indepedent values from Matrix
			error = genFromMatrix(nDependI, nInstances,
								  nVarsI, 0, nDependI, 0,
								  valuesI, matrixI);
			*/
			//Copy the values generated
			for (int i = 0; i < nInstances; ++i)
				for(int j = 0; j < nVarsI; ++j)
					values[i][nVars + j] = valuesI[i][j];
		}

		//Matrix "X"
		for (int i = 0; i < hMatrix; ++i)
			for (int j = 0; j < nVars ; ++j) {
				int diagonalDeviation = ((i-j)*(i-j)+1);
				matrix[i][j] =  disMatrix(gen)/diagonalDeviation;
			}

		//Initial values
		for (int i = 0; i < nVars; ++i) {
			float randValue = disData(gen);
			for (int j = 0; j < max(nDepend,nDependI); ++j)
				values[j][i] = randValue + disDefaultNoise(gen) * randValue;
		}



		//Values from Matrix
		error = genFromMatrix(max(nDepend,nDependI), nInstances,
								nVars, nVarsI, nDepend, nDependI,
								values, matrix);

	} while(error && attemps >= 0);

	if (error) {
		cerr << "Error, too big or too little numbers were produced" << endl;
		return -1;
	}

	//File output
	cout << nVars << endl;
	cout << nDepend << endl;
	cout << nVarsI << endl;
	cout << nDependI << endl;
	cout << nInstances << endl;

	cout << fixed << setprecision(6);

	uniform_real_distribution<float> disCustomNoise(-noise, noise);

	//Data generated
	for (int i = 0; i < nInstances; ++i) {
		for (int j = 0; j < totalVars ; ++j)
			cout << values[i][j] + values[i][j] * disCustomNoise(gen) << " ";
		cout << endl;
	}


	//Matrix that generated the data
	printMatrix(matrix);

	t.set();
	cout << endl << "Time: " << t.diff() << " ms" << endl;
	
	return 0;
}
