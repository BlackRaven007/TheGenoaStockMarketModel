#pragma once
#ifndef MARKET_H
#define MARKET_H

#include "agent.h"
#include "matrix.h"
#include "matrix3D.h"

enum class Version {NEW,OLD};

// Market function initialisation
void market(Version version, bool trade, bool histVola, bool opinionProp,
			bool shortSelling, int timePeriod, int agents, bool plots);

// Performs a specific Opinion Propagation operation depending on wheather it is a NewMarket 
// model or not
void opinionPropergation(bool OPINION_PROPAGATION_CLUSTERS, bool NEWMARKET, Agent* listOfAgents,
						int& N, double& globalBuyProb, Matrix<int>& clusters, double clusterPairProbability,
						double& clusterActivateProbability,Matrix<int>& activatedClusterSize, 
						int& t, Matrix3D<int>* cells);

// Randomly sets the buyers and sellers in a list of agents
void setBuyersOrSeller(Agent* listOfAgents, bool SHORTSELLING, double shortSigma,
						Matrix<int>& shortSale, int& t, int n);

#endif // !MARKET_H
