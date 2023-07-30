#pragma once
#ifndef TRADING_H
#define TRADING_H

#include "matrix.h"
#include "agent.h"

/* This function is simulating the trading mechanism
	INPUT: none required
	OUTPUT: the volume of trades conducted in this period*/
double trading(Matrix<double>* stockPrice, int N, Agent* listOfAgents, int t);

#endif // !TRADING_H