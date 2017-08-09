#ifndef _TIME_H_
#define _TIME_H_

#include <chrono>

using namespace std;

class Time {
	private:
		chrono::time_point<chrono::high_resolution_clock> startPoint;
		chrono::time_point<chrono::high_resolution_clock> lastPoint;
		chrono::time_point<chrono::high_resolution_clock> currentPoint;
		unsigned int factor;

	public:
		/**
		Initialize the timer with a factor to divide nanoseconds
		*/
		void start(unsigned int factor=1);
		/**
		Set a new time point
		*/
		void set();
		/**
		Returns the time elapsed between the beginning and the
		last time point
		*/
		long unsigned int diff(); //Milliseconds
		/**
		Returns the time elapsed between the last two time points
		*/
		long unsigned int lastDiff(); //Milliseconds
};
#endif