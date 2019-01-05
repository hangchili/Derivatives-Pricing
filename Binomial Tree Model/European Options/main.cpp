#include "BinLattice02.h"
#include "BinModel02.h"
#include "Option09.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	BinModel Model;
	if (Model.GetInputData() == 1) return 1;

	ofstream fout;
	fout.open("Results.txt");

	Call Option1;
	Put  Option2;
	Option1.GetInputData();
	Option2.GetInputData();
	BinLattice<double> PriceTree;
	BinLattice<double> XTree;
	BinLattice<double> YTree;
	BinLattice<double> PTree;
	BinLattice<double> QTree;
	fout << "S0 = " << Model.GetS0() << endl
		<< "U = " << Model.GetU() << endl
		<< "D = " << Model.GetD() << endl
		<< "R = " << Model.GetR() << endl;

	fout << "N = " << Option1.GetN() << endl
		<< "K = " << Option1.GetK() << endl;

	fout << "European call prices by PriceByCRR:"
		<< Option1.PriceByCRR(Model) << endl << endl;

	fout << "European call prices by PriceByCRRHW6:"
		<< Option1.PriceByCRRHW6(Model, XTree, YTree)
		<< endl << endl;
	fout << "Stock positions in replicating strategy:" << endl << endl;
	XTree.Display(fout);
	fout << "Money market account positions in replicating strategy:"<< endl << endl;
	YTree.Display(fout);

	fout << "N = " << Option1.GetN() << endl
		<< "K = " << Option1.GetK() << endl;
	

	fout << "European Put prices by PriceByCRR:"
		<< Option2.PriceByCRR(Model) << endl << endl;

	fout << "European Put prices by PriceByCRRHW6:"
		<< Option2.PriceByCRRHW6(Model, PTree, QTree)
		<< endl << endl;
	fout << "Stock positions in replicating strategy:" << endl << endl;
	PTree.Display(fout);
	fout << "Money market account positions in replicating strategy:" << endl << endl;
	QTree.Display(fout);
}
