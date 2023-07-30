#include "market.h"
#include "automaton2.h"
#include "opinion_prop.h"
#include "opinion.h"
#include "mathsFunc.h"
#include "hist_volat.h"
#include "price_formation.h"
#include "trading.h"
#include "logging.h"

void market(Version version, bool trade, bool histVola, bool opinionProp,
			bool shortSelling, int timePeriod, int agents, bool plots)
{
	// Model features
	static bool TRADING = trade;
	static bool HISTORICAL_VELOCITY = histVola;
	static bool OPINION_PROPAGATION_CLUSTERS = opinionProp;
	static bool SHORTSELLING = shortSelling;
	static bool PLOTS = plots;
	static bool NEWMARKET = false;

	if (version == Version::NEW)
		NEWMARKET = true;

	int timeSteps = timePeriod;
	int N = agents;
	int percentageDone = 0;

	// Set global market parameters
	Matrix<double> stockPrice(timeSteps + 1, 1);
	stockPrice.setAll(1);

	Matrix<int> activatedClusterSize(timeSteps, 1);
	activatedClusterSize.setAll(0);

	Matrix<int> clusters(N,1);
	clusters.setAll(0);

	double clusterPairProbability = 0.0001;
	double clusterActivateProbability = 0.2;

	Matrix<int> tradeVolume(timeSteps, 1);
	tradeVolume.setAll(0);

	Matrix<double> vola1d(timeSteps, 1);
	vola1d.setAll(0);

	Matrix<int> shortSale(timeSteps, 1);
	shortSale.setAll(0);

	// Set glodal agent parameters
	double globalBuyProb = 0.5;
	double sellMu = 1.01;
	double sellSigmaK = 3.5;
	double buyMu = 1.01;
	double buySigmak = 3.5;
	double shortSigma = 0.2;

	Agent* listOfAgents = new Agent[N]();

	// Initializing the agents individual parameters
	for (int i = 0; i < N; i++) 
	{
		listOfAgents[i].SetBuyProb(globalBuyProb);
	}

	std::cout << "\nAll " << N << " Agents have been initialised" << std::endl;

	Matrix3D<int>* cells = nullptr;

	// Running the cellular automaton if opinion propagation is activated in the new model
	if (OPINION_PROPAGATION_CLUSTERS && NEWMARKET == true) 
	{
		cells = automaton2(N, timeSteps, PLOTS);

		//std::cout << "Initial State:" << std::endl;
		//cells->showAllInDimension(0);
		//std::cout << "Final State:" << std::endl;
		//cells->showAllInDimension(timeSteps - 1);
	}


	// Main loop
	for (int t = 0; t < timeSteps; t++) 
	{
		//std::cout << "\nStarting timestep " << t+1 << " of " << timeSteps << std::endl;
		//std::cout << "Stock price is at " << stockPrice.getValByIndex(t) << std::endl;

		opinionPropergation(OPINION_PROPAGATION_CLUSTERS, NEWMARKET, listOfAgents,
							N, globalBuyProb, clusters, clusterPairProbability, clusterActivateProbability,
							activatedClusterSize, t, cells);

		for (int n = 0; n < N; n++) 
		{
			// Agent is Buyer or Seller during this time-step?
			setBuyersOrSeller(listOfAgents, SHORTSELLING, shortSigma, shortSale, t, n);

			// Historical Volatility
			if (HISTORICAL_VELOCITY) {
				hist_volat(n, t, listOfAgents, stockPrice, buySigmak, sellSigmaK);
			}

			// Agent buy or sell parameters
			if (listOfAgents[n].getIsBuyer()) 
			{

				listOfAgents[n].setBuyUpperLimit(stockPrice.getValByIndex(t) 
								* (normrnd(buyMu, listOfAgents[n].getVolatSigma())));

				int buyQuant = (int)(round(listOfAgents[n].getBuyCash()
					/ listOfAgents[n].getBuyUpperLimit()));

				listOfAgents[n].setBuyQuant(buyQuant);
			}

			else 
			{
				listOfAgents[n].setSellLowerLimit(stockPrice.getValByIndex(t) 
								/ abs(normrnd(sellMu, listOfAgents[n].getVolatSigma())));
			}
		}

		// New Market Price
		stockPrice.setValByIndex(t + 1, priceFormation(stockPrice.getValByIndex(t), N, 
								listOfAgents));

		// Trading
		if (TRADING)
			tradeVolume.setValByIndex(t, trading(&stockPrice, N, listOfAgents, t));

		if (PLOTS) {
			if (percentageDone != (int)(round(100 * (t / timeSteps)))) {
				percentageDone = (int)(round(100 * (t / timeSteps)));
				std::cout << "Percent done: " << percentageDone << "%" << std::endl;
			}
				

		}
	}

	delete[] listOfAgents;
	delete cells;

	// Calculate 10d-averaged daily Volatility
	int voladays = 10; // Number of days to average the volatility


	// Price Dynamics
	Matrix<double> price(stockPrice.getWidth() - 1, 1);
	for (int i = 0; i < price.getWidth(); i++)
		price.setValByIndex(i, stockPrice.getValByIndex(i + 1));

	std::cout << "Price Dynamics:" << std::endl;
	price.showAll();
	

	// Calculating log price returns
	std::cout << "Price Log Return:" << std::endl;
	int stockPriceReturnLen = stockPrice.getWidth() - 1;
	double* stockPriceReturnLog = new double[stockPriceReturnLen];
	for (int i = 0; i < stockPriceReturnLen; i++) {
		stockPriceReturnLog[i] = log(stockPrice.getValByIndex(i + 1)) - log(stockPrice.getValByIndex(i));
		std::cout << stockPriceReturnLog[i] << " ";
	}
	std::cout<<std::endl<<std::endl;


	// Calculation of the daily volatility
	int tempDailyVolaLength = voladays - 1;
	double* tempDailyVola = new double[tempDailyVolaLength];
	for (int i = 0; i < timeSteps - tempDailyVolaLength; i++) 
	{
		for (int n = 0; n < tempDailyVolaLength;n++)
			tempDailyVola[n] = stockPriceReturnLog[i + n];

		vola1d.setValByIndex(i + voladays - 1, calculateSD(tempDailyVola, tempDailyVolaLength) / sqrt(voladays));
	}

	std::cout << "Daily volatility:" << std::endl;
	vola1d.showAll();

	logResults(price, stockPriceReturnLog, stockPriceReturnLen, vola1d);
		
	delete[] tempDailyVola;
	delete[] stockPriceReturnLog;
}


void opinionPropergation(bool OPINION_PROPAGATION_CLUSTERS, bool NEWMARKET, Agent *listOfAgents,
						int &N, double& globalBuyProb, Matrix<int>& clusters, double clusterPairProbability,
						double& clusterActivateProbability, Matrix<int>& activatedClusterSize,
						int& t, Matrix3D<int> *cells)
{
	// Opinion Propagation in the old model
	if (OPINION_PROPAGATION_CLUSTERS && !NEWMARKET) 
	{
		opinion_prop(listOfAgents, N, globalBuyProb, clusters, clusterActivateProbability, clusterPairProbability,
					activatedClusterSize, t);
	}

	// Opinions Propagation in the new model
	else if (OPINION_PROPAGATION_CLUSTERS && NEWMARKET) 
	{
		// Passing the CA output to the opinion function, which returns a vector of reset
		// buy probabilities for all agents
		Matrix<double>* buyProb;
		int clusterSize;

		Matrix<int>* tempCell = cells->getCopyOfDimension(t);
		std::tie(buyProb, clusterSize) = opinion(tempCell);
		delete tempCell;

		activatedClusterSize.setValByIndex(t, clusterSize);

		for (int n = 0; n < buyProb->getWidth(); n++) {
			listOfAgents[n].SetBuyProb(buyProb->getValByIndex(n));
		}

		delete buyProb;

	}
}


void setBuyersOrSeller(Agent *listOfAgents, bool SHORTSELLING, double shortSigma, 
						Matrix<int>& shortSale, int& t, int n)
{
	int numBuyers = 0;
	int numSellers = 0;
	// Randomly choosing buyers
	double agentBuyProb = listOfAgents[n].getBuyProb();
	if (randomNumber() < listOfAgents[n].getBuyProb()) 
	{
		listOfAgents[n].setIsSeller(false);
		listOfAgents[n].setIsBuyer(true);

		numBuyers++;

		/* BuyCash update : If short- selling is activated, then exceedance of current
			cash account is allowed (credit buying); else short-selling constraint*/
		if (SHORTSELLING)
			listOfAgents[n].setBuyCash(abs(normrnd(0.5, shortSigma)) * listOfAgents[n].getCash());
		
		else
			listOfAgents[n].setBuyCash(randomNumber() * listOfAgents[n].getCash());
	}
	
	// The rest are sellers
	else 
	{
		listOfAgents[n].setIsSeller(true);
		listOfAgents[n].setIsBuyer(false);

		numSellers++;

		/* SellQuant update : if short - selling is activated, then exceedance of
			current asset level is allowed; else short-selling constraint*/
		if (SHORTSELLING)
			listOfAgents[n].setSellQuant((int)(round(abs(normrnd(0.5, shortSigma)) 
													* listOfAgents[n].getAssets())));
		else
			listOfAgents[n].setSellQuant((int)(round(randomNumber() 
													* listOfAgents[n].getAssets())));

		// Counting incident of short-selling
		if (listOfAgents[n].getSellQuant() > listOfAgents[n].getAssets())
			shortSale.setValByIndex(t, shortSale.getValByIndex(t) + 1);
	}
}