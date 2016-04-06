#include "LocalOptimization.h"

#include <dlib/optimization.h>
#include <iostream>

#include "FunctionDlib.h"

using namespace std;
using namespace dlib;

size_t countRestart; //GLOBAL

LocalOptimization::LocalOptimization(){}

LocalOptimization::~LocalOptimization(){}

double LocalOptimization::optimize(std::vector<double> &x, int fitType)
{
	int size = x.size();
	column_vector starting_point(size);
	for (int i = 0; i < size; i++)
		starting_point(i) = x[i];

	double fit = find_min_using_approximate_derivatives(
		bfgs_search_strategy(),
		objective_delta_stop_strategy(1e-6),
		FunctionDlib(size, fitType),
		starting_point, 
		-1.0e99,
		1.0e-7);

	for (int i = 0; i < size; i++)
		x[i] = starting_point(i);

	return fit;
}


