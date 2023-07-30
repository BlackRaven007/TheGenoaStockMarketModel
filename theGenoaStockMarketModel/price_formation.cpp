#include "price_formation.h"
#include "agent.h"
#include "supplyDemand.h"
#include <tuple>
#include <iostream>

double priceFormation(double marketPriceLast, int N, Agent* listOfAgents)
{

	// Price formation
	double pLower = 0;
	double pUpper = 10 * marketPriceLast;
	double p = 0;

	// Check whether demand f(pLower) > g(pLower) supply and f(pUpper) < g(pUpper) at beginning
	// Exit with old price if not
	double f1, f2, g1, g2;
	std::tie(f1, g1) = supplyDemand(pLower, N, listOfAgents);
	std::tie(f2, g2) = supplyDemand(pUpper, N, listOfAgents);

	if (f1 <= g1)
		p = 0;
	
	else if (f2 >= g2)
		p = 10 * marketPriceLast;
	
	else 
	{
		double pTest = (pUpper + pLower) / 2;
		double f, g;
		std::tie(f, g) = supplyDemand(pTest, N, listOfAgents);
		while (((pUpper - pLower) > (marketPriceLast / 1000)) && (f != g))
		{
			pTest = (pUpper + pLower) / 2;
			std::tie(f, g) = supplyDemand(pTest, N, listOfAgents);
			if (f > g)
				pLower = pTest;
			else
				pUpper = pTest;
		}
		p = pTest;
	}

	return p;
}