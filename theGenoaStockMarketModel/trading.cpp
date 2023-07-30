#include "trading.h"
#include "matrix.h"
#include "agent.h"
#include "supplyDemand.h"

double trading(Matrix<double>* stockPrice, int N, Agent* listOfAgents, int t)
{
	// Lower bound of stocks to trade
	double f, g;
	std::tie(f, g) = supplyDemand(stockPrice->getValByIndex(t+1), N, listOfAgents);
	double volume = std::min(f, g);
	double tradedSell = 0;
	double tradedBuy = 0;

	for (int n = 0; n < N; n++) 
	{
		if (listOfAgents[n].getIsSeller()) 
		{
			if (stockPrice->getValByIndex(t + 1) >= listOfAgents[n].getSellLowerLimit() 
				&& tradedSell < volume) 
			{
				// This seller sells
				double numAssetsToSell = std::min(listOfAgents[n].getSellQuant(), 
												volume - tradedSell);
				listOfAgents[n].setAssets(listOfAgents[n].getAssets() - numAssetsToSell);

				tradedSell = tradedSell + numAssetsToSell;
				listOfAgents[n].setCash(listOfAgents[n].getCash() + 
										(numAssetsToSell * stockPrice->getValByIndex(t + 1)));
			}
		}

		else 
		{
			if (stockPrice->getValByIndex(t + 1) <= listOfAgents[n].getBuyUpperLimit()
				&& tradedBuy < volume) 
			{
				// This buyer buys
				double numAssetsToBuy = std::min(listOfAgents[n].getBuyQuant(), 
												volume - tradedBuy);
				listOfAgents[n].setAssets(listOfAgents[n].getAssets() + numAssetsToBuy);
				tradedBuy = tradedBuy + numAssetsToBuy;

				double totalBuyPrice = numAssetsToBuy * stockPrice->getValByIndex(t + 1);
				listOfAgents[n].setCash(listOfAgents[n].getCash() - totalBuyPrice);
			}
		}
	}

	return volume;
}