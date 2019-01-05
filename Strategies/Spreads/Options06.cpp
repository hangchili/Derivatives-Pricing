#include "Options06.h"
#include "BinModel02.h"
#include <iostream>
#include <cmath>
using namespace std;
double EurOption::PriceByCRR(BinModel Model)
{
	double q = Model.RiskNeutProb();
	double ptr[100];
	for (int i = 0; i <= N; i++) { *(ptr + i) = Payoff(Model.S(N, i)); }
	for (int n = N - 1; n >= 0; n--)
	{
		for (int i = 0; i <= n; i++)
		{
			*(ptr + i) = (q*(*(ptr + i + 1)) + (1 - q)*(*(ptr + i))) / (1 + Model.GetR());
		}
	}
	return ptr[0];
}

int Call::GetInputData()
{
	cout << "Enter call option data:" << endl;
	int N;
	cout << "Enter steps to expiry N: "; cin >> N;
	SetN(N);
	cout << "Enter strike price K:    "; cin >> K;
	cout << endl;
	return 0;
}
double Call::Payoff(double z)
{
	if (z > K) return z - K;
	return 0.0;
}

int Put::GetInputData()
{
	cout << "Enter put spread data:" << endl;
	int N;
	cout << "Enter steps to expiry N: "; cin >> N;
	SetN(N);
	cout << "Enter strike price K:    "; cin >> K;
	cout << endl;
	return 0;
}
double Put::Payoff(double z)
{
	if (z < K) return K - z;
	return 0.0;
}


