#include "BinLattice02.h"
#include "BinModel02.h"
#include "Option09.h"
#include <iostream>
using namespace std;
int main()
{
	double S0 = 106.0;
	double r = 0.058;
	double sigma = 0.46;
	double T = (double)9 / 12;
	double K = 100.0;
	int N = 8;
	BinLattice<double>PriceTree;
	BinLattice<bool>StoppingTree;
	Call option1;
	BinModel Model(S0, r, sigma, T, N);
	if (Model.GetInputData() == 1)
		return 1;
	option1.GetInputData(N, K);
	cout << setiosflags(ios::fixed) << setprecision(5);
	cout << "S0 = " << S0 << endl;
	cout << "r = " << r << endl;
	cout << "sigma = " << sigma << endl;
	cout << "T = " << T << endl;
	cout << "K = " << K << endl;
	cout << "N = " << N << endl;
	cout << "U = " << Model.GetU() << endl;
	cout << "D = " << Model.GetD() << endl;
	cout << "R = " << Model.GetR() << endl;
	cout << "American call option price =" << option1.PriceBySnell(Model, PriceTree, StoppingTree);
	return 0;
}

/*

Input data checked
There is no arbitrage

S0 = 106.00000
r = 0.05800
sigma = 0.46000
T = 0.75000
K = 100.00000
N = 8
U = 0.14610
D = -0.13526
R = 0.00545
American call option price =21.33399
C:\Users\hansl\source\repos\HW7\x64\Debug\HW7.exe (process 11880) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/