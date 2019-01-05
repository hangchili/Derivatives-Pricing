#include "BSModel01.h"
#include "GmtrAsianCall.h"
#include"PathDepOption04.h"
#include <iostream>
using namespace std;
int main()
{
	double S0 = 100.0, r = 0.03, sigma = 0.2;
	BSModel Model(S0, r, sigma);

	double T = 1.0 / 12.0, K = 100.0;
	int m = 30;

	ArthmAsianCall Option(T, K, m);
	GmtrAsianCall  CVOption(T, K, m);

	long N = 30000;
	double epsilon = 0.001;
	Option.PriceByVarRedMC(Model, N, CVOption, epsilon);
	cout << "Arithmetic call price by VarRedMC  = " << Option.Price << endl
		<< "Error = " << Option.PricingError << endl
		<< "Gamma = " << Option.Gamma << endl
		<< "delta = " << Option.delta << endl << endl;

	Option.PriceByMC(Model, N, epsilon);
	cout << "Price by direct MC = " << Option.Price << endl
		<< "Error = " << Option.PricingError << endl
		<< "Gamma = " << Option.Gamma << endl
		<< "delta = " << Option.delta << endl;
	return 0;
}