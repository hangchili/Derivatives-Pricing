#pragma once
#ifndef PathDepOption04_h
#define PathDepOption04_h
#include "BSModel01.h"
class PathDepOption
{
public:
	double T, Price, PricingError, delta,Gamma;
	int m;
	virtual double Payoff(SamplePath& S) = 0;
	double PriceByMC(BSModel Model, long N,double epsilon);//?epsilon
	double PriceByVarRedMC(BSModel Model, long N, PathDepOption& CVOption,double epsilon);
	virtual double PriceByBSFormula(BSModel Model) { return 0.0; }//can�t be pure virtual
	virtual double DeltaByBSFormula(BSModel Model) { return 0.0; }
	virtual double GammaByBSFormula(BSModel Model) { return 0.0; }
};
class DifferenceOfOptions : public PathDepOption
{
public:
	PathDepOption* Ptr1;//polymorphism
	PathDepOption* Ptr2;                                        
		DifferenceOfOptions(double T_, int m_, PathDepOption* Ptr1_, PathDepOption* Ptr2_)
	{
		T = T_; m = m_; Ptr1 = Ptr1_; Ptr2 = Ptr2_;
	}
	double Payoff(SamplePath& S)
	{
		return Ptr1->Payoff(S) - Ptr2->Payoff(S);
	}
};
class ArthmAsianCall : public PathDepOption
{
public:
	double K;
	ArthmAsianCall(double T_, double K_, int m_)
	{
		T = T_; K = K_; m = m_;
	}
	double Payoff(SamplePath& S);
};
#endif
