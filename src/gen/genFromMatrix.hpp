#ifndef _GEN_FROM_MATRIX_H_
#define _GEN_FROM_MATRIX_H_

#include <cmath>

#include "mkl.h"
#include "../util/vectorToPointer.hpp"

using namespace std;

/**
Generate values from initial values and a matrix. Returns 
if no error ocurred
*/
bool genFromMatrix(int start, int end, int nVars, int nVarsI,
			int nDepend, int nDependI, vector<vector<float>> & values,
			vector<vector<float>> matrix);
#endif