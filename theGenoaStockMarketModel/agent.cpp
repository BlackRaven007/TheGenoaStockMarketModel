#include "agent.h"
#include <limits>

Agent::Agent()
{
	this->cash = 1000;
	this->assets = 1000;
	this->volatSigma = 0.02;
	this->volatTimeInt = 50;
	this->buyProb = 0;
	this->isBuyer = 0;
	this->isSeller = 0;
	this->buyCash = 0;
	this->buyQuant = 0;
	this->buyUpperLimit = 0;
	this->sellQuant = 0;
	this->sellLowerLimit = std::numeric_limits<double>::infinity();
	this->cluster = 0;
}

void Agent::SetBuyProb(double globalBuyProb)
{
	this->buyProb = globalBuyProb;
}

void Agent::setCluster(double tempCluster)
{
	this->cluster = tempCluster;
}

void Agent::setVolatSigma(double tempVolatSigma)
{
	this->volatSigma = tempVolatSigma;
}

void Agent::setIsSeller(bool tempIsSeller)
{
	isSeller = tempIsSeller;
}

void Agent::setIsBuyer(bool tempIsBuyer)
{
	this->isBuyer = tempIsBuyer;
}

void Agent::setBuyCash(double tempBuyCash)
{
	this->buyCash = tempBuyCash;
}

void Agent::setSellQuant(double tempSellQuant)
{
	this->sellQuant = tempSellQuant;
}

void Agent::setBuyUpperLimit(double tempBuyUpperLimit)
{
	this->buyUpperLimit = tempBuyUpperLimit;
}

void Agent::setBuyQuant(double tempBuyQuant)
{
	this->buyQuant = tempBuyQuant;
}

void Agent::setSellLowerLimit(double tempSellLowerLimit)
{
	this->sellLowerLimit = tempSellLowerLimit;
}

void Agent::setAssets(double tempAssets)
{
	this->assets = tempAssets;
}

void Agent::setCash(double tempCash)
{
	this->cash = tempCash;
}
