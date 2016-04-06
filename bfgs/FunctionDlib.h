#ifndef FUNCTIONDLIB_H
#define FUNCTIONDLIB_H

#include <dlib/optimization.h>
#include <vector>

#include "Fitness.h"

typedef dlib::matrix<double, 0, 1> column_vector;

extern size_t countRestart;

class FunctionDlib
{
public:
	FunctionDlib(int size_in, int fitType_in)
	{
		size = size_in;
		fitType = fitType_in;
		Fitness fit_;
		restart = fit_.getRestartFitness();
		countRestart = 0;
	}

	~FunctionDlib(){}

	double operator() (const column_vector& arg) const
	{
		if (countRestart < restart.size())
		{
			countRestart++;
			return restart[countRestart - 1];
		}

		std::vector<double> x(size);
		for (int i = 0; i < size; i++)
			x[i] = arg(i);

		Fitness fit_;
		double fit = fit_.fit(x, fitType);
		fit_.writeRestart(fit);

		return  fit;
	}

private:
	int size;
	int fitType;
	std::vector<double> restart;

};

#endif





