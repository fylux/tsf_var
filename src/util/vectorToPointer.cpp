#include "vectorToPointer.hpp"

float * vectorToPointer(vector<float> v) {
	int s = v.size();
	float * r = (float *) malloc(sizeof(float)*s);
	for (int i = 0; i < s; ++i)
			r[i] = v[i];
	return r;
}

float * vectorToPointer(vector<vector<float>> v) {
	int s1 = v.size();
	int s2 = v[0].size();
	float * r = (float *) malloc(sizeof(float)*s1*s2);
	for (int i = 0; i < s1; ++i)
		for (int j = 0; j < s2; ++j) {
			r[i*s2+j] = v[i][j];
		}

	return r;
}