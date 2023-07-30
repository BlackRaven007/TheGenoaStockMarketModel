#include "supplyDemand.h"
#include "agent.h"
#include <tuple>
#include <iostream>

std::tuple<double, double> supplyDemand(double p, int N, Agent* listOfAgents) {
	// Supply/Demand values for given price p
	double f = 0;
	double g = 0;

	for (int i = 0; i < N; i++) 
	{
		// Buy orders if agent is buyer and reservation price >= marketPrice
		if ((listOfAgents[i].getBuyUpperLimit() >= p) && (listOfAgents[i].getIsBuyer()))
			f = f + listOfAgents[i].getBuyQuant();

		// Sell orders if agent is seller and reservation price <= marketprice
		else if ((listOfAgents[i].getSellLowerLimit() <= p) && (listOfAgents[i].getIsSeller()))
			g = g + listOfAgents[i].getSellQuant();

	}	

	return { f,g };
}