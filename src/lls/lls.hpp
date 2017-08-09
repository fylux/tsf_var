#ifndef _LLS_H_
#define _LLS_H_

#include <iostream>
#include "mkl.h"

using namespace std;

class lls {
	private:
		float * a;
		float * b;
		unsigned int mA, nA;
		unsigned int mB, nB;

	public:
		/**
		Initialize the variables of the LLS system
		*/
		lls(unsigned int mA, unsigned int nA, float * a,
			unsigned int mB, unsigned int nB, float * b);
		/**
		Solve the system
		*/
		int solve();
};

#endif