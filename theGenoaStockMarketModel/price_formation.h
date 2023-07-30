#pragma once
#ifndef PRICE_FORMATION_H
#define PRICE_FORMATION_H

#include "agent.h"

/* This function balances supply and demand to determine the current market
	price from the previous market prices
	Input: the price in period t-1
	Output: the price in period t*/
double priceFormation(double marketPriceLast, int N, Agent* listOfAgents);

#endif // !PRICE_FORMATION_H