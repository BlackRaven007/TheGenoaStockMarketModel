#include "opinion_prop.h"
#include "agent.h"
#include "matrix.h"
#include "mathsFunc.h"

void opinion_prop(Agent* listOfAgents, int &N, double &globalBuyProb, Matrix<int> &clusters,
				double &clusterActivateProbability, double clusterPairProbability, Matrix<int> &activatedClusterSize, int &t)
{
	// Pairing: defining which agents belong to a cluster

	// Reset last buyProb at first (changed for activated clusters)
	listOfAgents[N-1].SetBuyProb(globalBuyProb);

	for (int i = 0; i < N - 1 ; i++) 
	{
		// Reset all buyProb to globalBuyProb (changed for activated clusters)
		listOfAgents[i].SetBuyProb(globalBuyProb);

		for (int j = i + 1; j < N; j++)
		{
			clustering(j, i, N, listOfAgents, clusters, clusterPairProbability);
		}
	}

	// Cluster activation: activate a single cluster of agents
	if (randomNumber() < clusterActivateProbability)
		clusterActivation(listOfAgents, N, globalBuyProb, clusters, activatedClusterSize, t);
}


void clustering(int j, int i, int& N, Agent* listOfAgents, Matrix<int>& clusters, double clusterPairProbability)
{
	// Form pair with Pa
	if (((randomNumber() < clusterPairProbability)
		&& (listOfAgents[i].getCluster() != listOfAgents[i].getCluster()))
		|| listOfAgents[i].getCluster() == 0) 
	{
		/* Form pair :
		* If i agent is member of cluster:
		* set j agent (and all his cluster members)
		* to i cluster (and free j cluster) */
		if (listOfAgents[i].getCluster() != 0) 
		{
			if (listOfAgents[j].getCluster() != 0) 
			{
				clusters.setVal((int)listOfAgents[j].getCluster(), 0, 0);
				double clusterToChange = listOfAgents[j].getCluster();
				for (int k = 0; k < N; k++) 
				{
					if (listOfAgents[k].getCluster() == clusterToChange)
					{
						listOfAgents[k].setCluster(listOfAgents[i].getCluster());
					}
				}
			}
			listOfAgents[j].setCluster(listOfAgents[i].getCluster());
		}

		// Else if j agent is member of clustr (and i is not):
		// Set i agent to j cluster
		else if (listOfAgents[j].getCluster() != 0)
			listOfAgents[i].setCluster(listOfAgents[j].getCluster());

		// Else
		// Form new cluster and reserve slot in cluster-arr
		else 
		{
			int k = 0;
			while (clusters.getVal(k, 0) != 0)
				k++;

			clusters.setVal(k, 0, 1);
			listOfAgents[i].setCluster(k);
			listOfAgents[j].setCluster(k);
		}
	}
}


void clusterActivation(Agent* listOfAgents, int& N, double& globalBuyProb, 
						Matrix<int>& clusters, Matrix<int>& activatedClusterSize, int& t)
{
	// Random index draw of a nonzero cluster
	auto results = clusters.getRandomIndexOfNonZero();
	auto activeCluster = std::get<0>(results);
	auto activeClustersLength = std::get<1>(results);
	int randElemNum = std::get<1>(results);

	// Activate the cluster
	if (activeClustersLength > 0) 
	{
		int buyProb = 1;
		if (randomNumber() < 0.5)
			buyProb = 0;

		int tempSum = 0;

		for (int k = 0; k < N; k++) 
		{
			if (listOfAgents[k].getCluster() == activeCluster[randElemNum]) 
			{
				listOfAgents[k].SetBuyProb(buyProb);
				listOfAgents[k].setCluster(0); // Leave cluster
				tempSum++;

			}
		}

		activatedClusterSize.setValByIndex(t, tempSum);

		clusters.setValByIndex(activeCluster[randElemNum - 1], 0); // Free cluster

		delete[] activeCluster;
	}
}
