#pragma once
#ifndef SUPPLYDEMAND_H
#define SUPPLYDEMAND_H

#include "agent.h"
#include <tuple>

/* This function determines the supply and demand for a given market price
	INPUT: the current market price p
	OUTPUT: the aggregate demand and aggregate supply in the market model*/
std::tuple<double, double> supplyDemand(double p, int N, Agent* listOfAgents);

#endif // !SUPPLYDEMAND_H