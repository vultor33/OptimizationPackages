#ifndef LOCALOPTIMIZATION_H
#define LOCALOPTIMIZATION_H

#include <vector>

class LocalOptimization
{
public:
	LocalOptimization();
	~LocalOptimization();

	double optimize(std::vector<double> &x, int fitType);

};

#endif
