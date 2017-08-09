#include "Time.hpp"

void Time::start(unsigned int factor) {
	startPoint = chrono::high_resolution_clock::now();
	currentPoint = startPoint;
	lastPoint = startPoint;
	this->factor = factor;
}

void Time::set() {
	lastPoint = currentPoint;
	currentPoint = chrono::high_resolution_clock::now();
}


long unsigned int Time::diff() {
	return chrono::duration_cast<chrono::nanoseconds>(currentPoint-startPoint).count()/factor;
}

long unsigned int Time::lastDiff() {
	return chrono::duration_cast<chrono::nanoseconds>(currentPoint-lastPoint).count()/factor;
}