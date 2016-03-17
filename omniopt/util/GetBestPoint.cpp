#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream non_("nondominated_pop.out");
	int nvar;
	cout << "digite o numero de variaveis:  ";
	cin >> nvar;

	string auxline;
	double minFit = 1.0e99;
	double auxFit;
	vector<double> point(nvar);

	getline(non_,auxline);
	getline(non_,auxline);
	while(getline(non_,auxline))
	{
		stringstream line;
		line << auxline;
		line >> auxFit;
		if(auxFit < minFit)
		{
			minFit = auxFit;
			for(int i=0; i<nvar; i++)
				line >> point[i];
		}
	}
	non_.close();

	ofstream of_("bestpoint.txt");
	of_ << setprecision(16) << auxFit << endl;
	of_ << nvar << endl;
	for(int i=0; i<nvar; i++)
		of_ << setprecision(16) << point[i] << endl;
	of_.close();

	return 0;
}


