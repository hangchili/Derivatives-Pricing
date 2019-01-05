#include "PathDepOption04.h"
#include <cmath>
void Rescale(SamplePath& S, double x)
{
	int m = S.size();
	for (int j = 0; j < m; j++) S[j] = x * S[j];
}
double PathDepOption::PriceByMC(BSModel Model, long N,double epsilon)
{
	double H = 0.0, Hsq = 0.0,Heps1=0.0,Heps2=0.0;
	SamplePath S(m);
	for (long i = 0; i < N; i++)
	{
		Model.GenerateSamplePath(T, m, S);
		H = (i / (i + 1.0))*H + Payoff(S) / (i + 1.0);
		Hsq = (i / (i + 1.0))*Hsq + pow(Payoff(S), 2.0) / (i + 1.0);
		Rescale(S, 1.0 + epsilon);
		Heps1 = (i / (i + 1.0))*Heps1 + Payoff(S) / (i + 1.0);
		Rescale(S, (1.0 - epsilon) / (1.0 + epsilon));
		Heps2 = (i / (i + 1.0))*Heps2 + Payoff(S) / (i + 1.0);
	}
	Price = exp(-Model.r*T)*H;
	delta = exp(-Model.r*T)*(Heps1 - H) / (Model.S0*epsilon);
	Gamma = exp(-Model.r*T)*(Heps1 - 2 * H + Heps2) / ((Model.S0*epsilon)*(Model.S0*epsilon));
	PricingError = exp(-Model.r*T)*sqrt(Hsq - H * H) / sqrt(N - 1.0);
	return Price;
}
double PathDepOption::PriceByVarRedMC(BSModel Model, long N, PathDepOption& CVOption,double epsilon)
{
	
    DifferenceOfOptions VarRedOpt(T, m, this, &CVOption);// address of the object VarRedOpt to this
	Price = VarRedOpt.PriceByMC(Model, N,epsilon) + CVOption.PriceByBSFormula(Model);
	delta = VarRedOpt.delta +CVOption.DeltaByBSFormula(Model);
	Gamma = VarRedOpt.Gamma+CVOption.GammaByBSFormula(Model);
	PricingError = VarRedOpt.PricingError;
	return Price;
}
double ArthmAsianCall::Payoff(SamplePath& S)
{
	double Ave = 0.0;
	for (int k = 0; k < m; k++) Ave = (k / (k + 1.0))*Ave + S[k] / (k + 1.0);
	if (Ave < K) return 0.0;
	return Ave - K;
}
