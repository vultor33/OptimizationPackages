#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "LocalOptimization.h"

using namespace std;

int main()
{
	LocalOptimization bfgs_;
	ifstream initial_("initialPoint.txt");
	int nVar;
	initial_ >> nVar;
	vector<double> x(nVar);
	for (int i = 0; i < nVar; i++)
		initial_ >> x[i];

	double finalFit = bfgs_.optimize(x, 2);

	ofstream best_("bestPoint.txt");
	best_ << setprecision(16) << finalFit << endl << endl;
	for (int i = 0; i < nVar; i++)
		best_ << setprecision(16) << x[i] << endl;

	return 0;
}

/*
GENERATE FITNESS
	ifstream point_("point.txt");
	int nVar;
	point_ >> nVar;
	vector<double> x(nVar);
	double aux = 0.0e0;
	for (int i = 0; i < nVar; i++)
	{
		point_ >> x[i];
		aux += x[i] * x[i];
	}
	point_.close();
	ofstream fit_("fitness.txt");
	fit_ << setprecision(16) << aux << endl;
	fit_.close();
	return 0;
*/