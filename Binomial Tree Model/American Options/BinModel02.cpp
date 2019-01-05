#include "BinModel02.h"
#include <iostream>
#include <cmath>
using namespace std;
double BinModel::RiskNeutProb()
{
	return (R - D) / (U - D);
}
double BinModel::S(int n, int i)
{
	return S0 * pow(1 + U, i)*pow(1 + D, n - i);
}
double BinModel::GetR()
{
	return R;
}
double BinModel::GetU()
{
	return U;
}
double BinModel::GetD()
{
	return D;
}
BinModel::BinModel(double S0_, double r, double sigma, double T, int N)
{
	S0 = S0_;
	U = exp((r - sigma * sigma / 2)*(T / N) + sigma * sqrt((T / N))) - 1;
	D = exp((r - sigma * sigma / 2)*(T / N) - sigma * sqrt((T / N))) - 1;
	R = exp(r*(T / N)) - 1;
}
int BinModel::GetInputData()
{



	//making sure that 0<S0, -1<D<U, -1<R
	if (S0 <= 0.0 || U <= -1.0 || D <= -1.0 || U <= D || R <= -1.0)
	{
		cout << "Illegal data ranges" << endl;
		cout << "Terminating program" << endl;
		return 1;
	}
	//checking for arbitrage
	if (R >= U || R <= D)
	{
		cout << "Arbitrage exists" << endl;
		cout << "Terminating program" << endl;
		return 1;
	}

	cout << "Input data checked" << endl;
	cout << "There is no arbitrage" << endl << endl;

	return 0;
}