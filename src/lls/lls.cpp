#include "lls.hpp"

lls::lls(unsigned int mA, unsigned int nA, float * a,
		 unsigned int mB, unsigned int nB, float * b) {

	this->nA = nA;
	this->mA = mA;
	this->nB = nB;
	this->mB = mB;
	this->a = a;
	this->b = b;
}

int lls::solve() {

	return LAPACKE_sgels(LAPACK_ROW_MAJOR
					,'N'
					,mA //rows A
					,nA //cols A
					,nB //cols B
					,a
					,nA //leading dimension A
					,b
					,nB); //leading dimension B*/
}