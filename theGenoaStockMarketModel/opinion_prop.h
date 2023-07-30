#pragma once
#ifndef OPINION_PROP_H
#define OPINION_PROP_H

#include "agent.h"
#include "matrix.h"

/* This function forms clusters amongst agents by resetting their buy
* probabilities to optain "sure buyers" and "sure sellers".
* NOTE: This is the opinion propagation mechanism for the OLD model only */
void opinion_prop(Agent* listOfAgents, int &N, double &globalBuyProb, Matrix<int> &clusters, 
				double &clusterActivateProbability, double clusterPairProbability, Matrix<int> &activatedClusterSize, int &t);

void clustering(int j, int i, int& N, Agent* listOfAgents, Matrix<int>& clusters, double clusterPairProbability);

void clusterActivation(Agent* listOfAgents, int& N, double& globalBuyProb,
						Matrix<int>& clusters, Matrix<int>& activatedClusterSize, int& t);

#endif // !OPINION_PROP_H
