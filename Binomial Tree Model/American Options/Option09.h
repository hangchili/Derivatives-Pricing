#pragma once
#ifndef Option09_h
#define Option09_h
#include "BinLattice02.h"
#include "BinModel02.h"
class Option
{
private:
	int N; //steps to expiry
public:
	void SetN(int N_) { N = N_; }
	int GetN() { return N; }
	virtual double Payoff(double z) = 0;
};

class EurOption : public virtual Option
{
public:
	//pricing European option
	double PriceByCRR(BinModel Model);
	double PriceByCRRHW6(BinModel model, BinLattice<double>& Xtree, BinLattice <double> & Ytree);
};

class AmOption : public virtual Option
{
public:
	//pricing American option
	double PriceBySnell(BinModel Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree);
};

class Call : public EurOption, public AmOption
{
private:
	double K; //strike price
public:
	void SetK(double K_) { K = K_; }
	int GetInputData(int N_, double K_);
	double Payoff(double z);
	double GetK() { return K; }
};

class Put : public EurOption, public AmOption
{
private:
	double K; //strike price
public:
	void SetK(double K_) { K = K_; }
	int GetInputData(int N_, double K_);
	double Payoff(double z);
	double GetK() { return K; }
};

#endif 


