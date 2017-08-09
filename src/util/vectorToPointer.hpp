#ifndef _VECTOR_TO_POINTER_H_
#define _VECTOR_TO_POINTER_H_

#include <cstdlib>
#include <vector>

using namespace std;

/**
Returns a copy of a vector as a pointer
*/
float * vectorToPointer(vector<float> v);

/**
Returns a copy of a 2D as a pointer
*/
float * vectorToPointer(vector<vector<float>> v);

#endif