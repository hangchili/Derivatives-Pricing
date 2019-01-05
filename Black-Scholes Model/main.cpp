#include"EurCall.h"
#include <iostream>
using namespace std;
int main()
{
	double S0 = 100.0, r = 0.03, sigma = 0.2;
	double T = 1.0 / 12.0, K = 100.0;
	EurCall Option(T,K);

	cout << "Price = " << Option.PriceByBSFormula(S0, sigma, r) << endl
		 << "Vega = " << Option.VegaByBSFormula(S0, sigma, r) << endl
		 << "Gamma = " << Option.GammaByBSFormula(S0, sigma, r) << endl
		 << "delta = " << Option.DeltaByBSFormula(S0, sigma, r) << endl << endl;

	return 0;
}
