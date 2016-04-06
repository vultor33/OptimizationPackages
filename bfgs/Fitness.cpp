#include "Fitness.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

Fitness::Fitness(){}

Fitness::~Fitness(){}

double Fitness::fit(vector<double> &point, int type)
{
	switch (type)
	{
	case 0:
		return point[0] * point[0];
		break;

	case 1:
		return lennardJones(point);
		break;

	case 2:
		return custom(point);
		break;

	default:
		cout << "FITNESS FUNCTION NOT FOUND" << endl;
		exit(3);
	}
}

double Fitness::lennardJones(vector<double> &x)
{
	// x1 x2 x3 ... y1 y2 y3 ... z1 z2 z3
	int natm = x.size() / 3;
	double r, r2, r4, r6, r12;
	double vlj = 0.0e0;
	for (int i = 0; i < (natm - 1); i++)
	{
		for (int j = (i + 1); j < natm; j++)
		{
			r = sqrt(
				(x[i] - x[j])*(x[i] - x[j]) +
				(x[i + natm] - x[j + natm])*(x[i + natm] - x[j + natm]) +
				(x[i + 2 * natm] - x[j + 2 * natm])*(x[i + 2 * natm] - x[j + 2 * natm])
				);
			r2 = r * r;
			r4 = r2 * r2;
			r6 = r4 * r2;
			r12 = r6 * r6;
			vlj += 4.0e0 * (-1 / r6 + 1 / r12);
		}
	}
	return vlj;
}

double Fitness::custom(vector<double> &x)
{
	// write point.txt
	// run getFitness.x
	// read fitness.txt






	ofstream point_("point.txt");
	point_ << x.size() << endl;
	for (size_t i = 0; i < x.size(); i++)
	{
		point_ << setprecision(16) << x[i] << endl;
	}
	point_.close();

#ifdef WIN32
	system("getFitness.exe");
#else
	system("./getFitness.x");
#endif

	ifstream fit_("fitness.txt");
	double fit;
	fit_ >> fit;
	fit_.close();
	return fit;
}

vector<double> Fitness::getRestartFitness()
{
	vector<double> restart;
	if (!existFile("restart.bfgs"))
		return restart;

	ifstream res_("restart.bfgs");
	string auxline;
	double auxFit;
	while (getline(res_, auxline))
	{
		stringstream line;
		line << auxline;
		line >> auxFit;
		restart.push_back(auxFit);
	}

	return restart;
}

bool Fitness::existFile(string name)
{
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}

void Fitness::writeRestart(double fit)
{
	ofstream res_("restart.bfgs", ios::app);
	res_ << setprecision(16) << fit << endl;
	res_.close();
}