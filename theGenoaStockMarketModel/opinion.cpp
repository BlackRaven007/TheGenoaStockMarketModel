#include "opinion.h"
#include "matrix.h"
#include <tuple>
#include "mathsFunc.h"

std::tuple<Matrix<double>*, int> opinion(Matrix<int>* cells)
{
	// Number of agents in the model
	int N = cells->getWidth();

	// Identifying the clusters in the CA
	// output and counting the number of clusters
	Matrix<int>* cluster;
	int numb;
	std::tie(cluster, numb) = cells->getMatrixOfClusters();

	Matrix<double>* buyProb = new Matrix<double>(N, 1);
	buyProb->setAll(0.5);
	int sum = 0;
	bool buy = false;

	// For extracting each cluster of agents and its sizes
	for (int i = 1; i < numb+1; i++) 
	{
		// Returning the vector of cluster members
		int numOfElements;
		int* listOfElements;
		
		std::tie(listOfElements, numOfElements) = cluster->getNumberOfElementsEqualTo(i);
		sum = sum + numOfElements;


		// Randomly allocating buyers/sellers
		if (randomNumber() < 0.5)
			buy = false;
		else
			buy = true;

		for (int k = 0; k < numOfElements; k++)
			buyProb->setValByIndex(listOfElements[k], buy);

		
		
		delete[] listOfElements;
	}

	delete cluster;

	return { buyProb, sum };
}