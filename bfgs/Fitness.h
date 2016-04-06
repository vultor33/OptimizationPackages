#ifndef FITNESS_H
#define FITNESS_H

#include <vector>
#include <string>

class Fitness
{
public:
	Fitness();
	~Fitness();

	std::vector<double> getRestartFitness();

	void writeRestart(double fit);

	double fit(std::vector<double> &point, int type);

private:
	double lennardJones(std::vector<double> &x);
	double custom(std::vector<double> &x);

	bool existFile(std::string name);

};

#endif
