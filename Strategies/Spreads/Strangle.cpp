#include "Strangle.h"
#include <iostream>
using namespace std;
int Strangle::GetInputData()
{
	cout << "Enter double-digital option data:" << endl;
	int N;
	cout << "Enter steps to expiry N: "; cin >> N;
	SetN(N);
	cout << "Enter parameter K1:      "; cin >> K1;
	cout << "Enter parameter K2:      "; cin >> K2;
	cout << endl;
	return 0;
}
double Strangle::Payoff(double z)
{
	if (z <= K1) return  K1-z;
	else
		if (K1  < z&&z <= K2) return 0.0;
		else return z-K2;
}