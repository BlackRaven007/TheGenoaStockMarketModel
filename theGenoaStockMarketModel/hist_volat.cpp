#include "hist_volat.h"
#include "agent.h"
#include "matrix.h"
#include "mathsFunc.h"

void hist_volat(int n, int t, Agent* listOfAgents, Matrix<double> &stockPrice,
				double buySigmak, double sellSigmaK)
{
	// This function resets the nth agent's historic volatility
	// INPUT: agent number
	// Output: none

	// Calculate volatSigma

	int x = 0;

	if (t == 0)
		listOfAgents[n].setVolatSigma(0);

	else
	{
		double* logPriceReturn = new double[t];

		if (t < listOfAgents[n].getVolatTimeInt()) 
		{

			for (int i = 0; i < t ;i++)
			{
				logPriceReturn[i] = log(stockPrice.getValByIndex(i + 1) 
										/ stockPrice.getValByIndex(i));
			}	 
		}

		else
		{
			x = 0;
			for (int i = t - listOfAgents[n].getVolatTimeInt(); i < t; i++) 
			{
				logPriceReturn[x] = log(stockPrice.getValByIndex(i + 1) 
										/ stockPrice.getValByIndex(i));

				x++;
			}
			t = x;
		}

		if (listOfAgents[n].getIsBuyer()) {
			listOfAgents[n].setVolatSigma(buySigmak * calculateSD(logPriceReturn, t));
		}

		else
			listOfAgents[n].setVolatSigma(sellSigmaK * calculateSD(logPriceReturn, t));

		delete[] logPriceReturn;
	}
}