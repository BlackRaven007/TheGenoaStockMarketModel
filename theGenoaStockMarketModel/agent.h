#pragma once
#ifndef AGENT_H
#define AGENT_H

class Agent
{
public:
	// Constructor
	Agent();

	// Getters
	double getCash() 
	{
		return cash;
	}

	double getAssets() 
	{
		return assets;
	}

	double getVolatSigma() 
	{
		return volatSigma;
	}

	int getVolatTimeInt() 
	{
		return volatTimeInt;
	}

	double getBuyProb() 
	{
		return buyProb;
	}

	bool getIsBuyer() 
	{
		return isBuyer;
	}
	
	bool getIsSeller() 
	{
		return isSeller;
	}

	double getBuyCash() 
	{
		return buyCash;
	}

	double getBuyQuant() 
	{
		return buyQuant;
	}

	double getBuyUpperLimit() 
	{
		return buyUpperLimit;
	}

	double getSellQuant() 
	{
		return sellQuant;
	}

	double getSellLowerLimit() 
	{
		return sellLowerLimit;
	}

	double getCluster() 
	{
		return cluster;
	}


	// Setters
	void SetBuyProb(double globalBuyProb);

	void setCluster(double tempCluster);

	void setVolatSigma(double tempVolatSigma);

	void setIsSeller(bool tempIsSeller);

	void setIsBuyer(bool tempIsBuyer);

	void setBuyCash(double tempBuyCash);

	void setSellQuant(double tempSellQuant);

	void setBuyUpperLimit(double tempBuyUpperLimit);

	void setBuyQuant(double tempBuyQuant);

	void setSellLowerLimit(double tempSellLowerLimit);

	void setAssets(double tempAssets);

	void setCash(double tempCash);

private:
	int volatTimeInt;
	double cash, volatSigma, buyProb, buyCash, buyQuant, buyUpperLimit, sellQuant,
			sellLowerLimit, cluster, assets;
	bool isBuyer, isSeller;
};

#endif // !AGENT_H