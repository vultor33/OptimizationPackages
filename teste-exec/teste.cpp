#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
  ifstream in_("point.txt");
  int n;
  vector<double> x;
  in_ >> n;
  x.resize(n);
  double aux = 0.0e0;
  for(int i=0; i<n; i++)
  {
    in_ >> x[i];
    aux += x[i] * x[i];
  }
  in_.close();

  remove("fitness.txt");
  ofstream out_("fitness.txt");
  out_ << setprecision(16) << aux << endl;
  out_.close();


  return 0;
}



