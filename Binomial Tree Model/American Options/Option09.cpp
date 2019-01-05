#include "Option09.h"
#include "BinModel02.h"
#include "BinLattice02.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;
double EurOption::PriceByCRR(BinModel Model)
{
	double q = Model.RiskNeutProb();
	int N = GetN();
	vector<double> Price(N + 1);
	for (int i = 0; i <= N; i++)
		Price[i] = Payoff(Model.S(N, i));
	for (int n = N - 1; n >= 0; n--)
	{
		for (int i = 0; i <= n; i++)
			Price[i] = (q*Price[i + 1] + (1 - q)*Price[i]) / (1 + Model.GetR());
	}
	return Price[0];
}

double EurOption::PriceByCRRHW6(BinModel Model, BinLattice<double>& Xtree, BinLattice<double>& Ytree)
{
	int i, j, N = GetN();
	Xtree.SetN(N - 1);
	Ytree.SetN(N - 1);
	vector<double>price(N + 1);
	for (i = 0; i <= N; ++i)
		price[i] = Payoff(Model.S(N, i));
	for (i = N - 1; i >= 0; --i)
		for (j = 0; j <= i; ++j)
		{
			Xtree.SetNode(i, j, ((price[j + 1] - price[j]) / (Model.S(i + 1, j + 1) - Model.S(i + 1, j))));
			Ytree.SetNode(i, j, ((price[j + 1] - Xtree.GetNode(i, j)*Model.S(i + 1, j + 1)) / (1 + Model.GetR())));
			price[j] = Xtree.GetNode(i, j)*Model.S(i, j) + Ytree.GetNode(i, j);
		}
	return price[0];

}


double AmOption::PriceBySnell(BinModel Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree)
{
	double q = Model.RiskNeutProb();
	int N = GetN();
	PriceTree.SetN(N);
	StoppingTree.SetN(N);
	double ContVal;
	for (int i = 0; i <= N; i++)
	{
		PriceTree.SetNode(N, i, Payoff(Model.S(N, i)));
		StoppingTree.SetNode(N, i, 1);
	}
	for (int n = N - 1; n >= 0; n--)
	{
		for (int i = 0; i <= n; i++)
		{
			ContVal = (q*PriceTree.GetNode(n + 1, i + 1) + (1 - q)*PriceTree.GetNode(n + 1, i)) / (1 + Model.GetR());
			PriceTree.SetNode(n, i, Payoff(Model.S(n, i)));
			StoppingTree.SetNode(n, i, 1);
			if (ContVal > PriceTree.GetNode(n, i))
			{
				PriceTree.SetNode(n, i, ContVal);
				StoppingTree.SetNode(n, i, 0);
			}
			else if (PriceTree.GetNode(n, i) == 0.0)
			{
				StoppingTree.SetNode(n, i, 0);
			}
		}
	}
	return PriceTree.GetNode(0, 0);
}
int Call::GetInputData(int N_, double K_)
{

	SetN(N_);
	SetK(K_);


	return 0;
}
double Call::Payoff(double z)
{
	if (z > K) return z - K;
	return 0.0;
}
int Put::GetInputData(int N_, double K_)
{
	SetN(N_);
	SetK(K_);
	return 0;
}
double Put::Payoff(double z)
{
	if (z < K) return K - z;
	return 0.0;
}
