#include "automaton2.h"
#include "matrix3D.h"
#include "matrix.h"
#include "mathsFunc.h"

Matrix3D<int>* automaton2(int agents, int periods, int plot)
{
	// This function uses a stochastic cellular automaton to model cluster building amongst all
	// agents over the specified time horizon

	// Parameter set up
	double pini = 0.15;
	int p = 1;
	int pr = 1;
	double pd = 0.6;
	double pn = 0.0003;
	double pdest = 0.1;

	int N = (int)round(sqrt(agents));

	int T = periods;

	double densl = 0.85;
	double densg = 0.25;

	int PLOTS = plot;

	// Initialisations
	Matrix3D<int>* clusterDynamics = new Matrix3D<int>(N,N,T);
	clusterDynamics->setAll(0);

	Matrix<int> cells(N + 2, N + 2);
	cells.setAll(0);

	for (int x = 1; x < N; x++) 
	{
		for (int y = 1; y < N; y++) 
		{
			cells.setVal(x, y, (randomNumber() < pini));
		}
	}

	// Row/column indices set up

	int* up = new int[N];
	for (int i = 0; i < N; i++) 
	{
		up[i] = i;
	}

	int* down = new int[N];
	for (int i = 0; i < N; i++) 
	{
		down[i] = i + 2;
	}

	int* centreRows = new int[N];
	for (int i = 0; i < N; i++) 
	{
		centreRows[i] = i + 1;
	}

	int* left = new int[N];
	for (int i = 0; i < N; i++) 
	{
		left[i] = i;
	}

	int* right = new int[N];
	for (int i = 0; i < N; i++) 
	{
		right[i] = i + 2;
	}

	int* centreCols = new int[N];
	for (int i = 0; i < N; i++) 
	{
		centreCols[i] = i + 1;
	}

	for (int i = 0; i < T; i++) 
	{
		// Local Cluster Limitations
		
		// Three upper squares:
		int sum = 0;
		for (int x = 1; x < round(N / 3.0) + 1; x++) 
		{
			for (int y = 1; y < round(N / 3.0) + 1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = 1; x < round(N / 3.0) + 1; x++) 
			{
				for (int y = 1; y < round(N / 3.0) + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		sum = 0;
		for (int x = 1; x < round(N / 3.0) + 1; x++) 
		{
			for (int y = (int)round(N/3.0)+1; y < (round(N / 3.0))*2; y++) 
			{
				sum = sum + cells.getVal(x, y) + 1;
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = 1; x < round(N / 3.0) + 1; x++) 
			{
				for (int y = (int)round(N / 3.0) + 1; y < round(N / 3.0) * 2 + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		sum = 0;
		for (int x = 1; x < round(N / 3.0); x++) 
		{
			for (int y = (int)(round(N / 3.0) * 2) + 1; y < round(N / 3.0) * 3 + 1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = 1; x < round(N / 3.0) + 1; x++) 
			{
				for (int y = (int)(round(N / 3.0) * 2) + 1; y < round(N / 3.0) * 3 + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		// Three middle squares:
		sum = 0;
		for (int x = (int)round(N / 3.0) + 1; x < round(N/3.0)*2 + 1; x++) 
		{
			for (int y = 1; y < round(N / 3.0) +1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = (int)round(N / 3.0) + 1; x < round(N / 3.0) * 2 + 1; x++) 
			{
				for (int y = 1; y < round(N / 3.0) + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		sum = 0;
		for (int x = (int)round(N / 3.0) + 1; x < round(N / 3.0) * 2 + 1; x++) 
		{
			for (int y = (int)round(N/3.0) + 1; y < round(N / 3.0) * 2 + 1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = (int)round(N / 3.0) + 1; x < round(N / 3.0) * 2 + 1; x++) 
			{
				for (int y = (int)round(N / 3.0) + 1; y < round(N / 3.0) * 2 + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		sum = 0;
		for (int x = (int)round(N / 3.0) + 1; x < round(N / 3.0) * 2 + 1; x++) 
		{
			for (int y = (int)round(N / 3.0) * 2 + 1; y < round(N / 3.0) * 3 + 1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = (int)round(N / 3.0) + 1; x < round(N / 3.0) * 2 + 1; x++) 
			{
				for (int y = (int)round(N / 3.0) * 2 + 1; y < round(N / 3.0) * 3 + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		// Three lower squares:
		sum = 0;
		for (int x = (int)round(N / 3.0) * 2 + 1; x < round(N / 3.0) * 3 + 1; x++) 
		{
			for (int y = 1; y < round(N / 3.0) + 1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = (int)round(N / 3.0) * 2 + 1; x < round(N / 3.0) * 3 + 1; x++) 
			{
				for (int y = 1; y < round(N / 3.0) + 1; y++)
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		sum = 0;
		for (int x = (int)round(N / 3.0) * 2 + 1; x < round(N / 3.0) * 3 + 1; x++) 
		{
			for (int y = (int)round(N / 3.0) + 1; y < round(N / 3.0) * 2 + 1; y++) 
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = (int)round(N / 3.0) * 2 + 1; x < round(N / 3.0) * 3 + 1; x++) 
			{
				for (int y = (int)round(N / 3.0) + 1; y < round(N / 3.0) * 2 + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}

		sum = 0;
		for (int x = (int)round(N / 3.0) * 2 + 1; x < round(N / 3.0) * 3 + 1; x++) 
		{
			for (int y = (int)round(N / 3.0) * 2 + 1; y < round(N / 3.0) * 3 + 1; y++)
			{
				sum = sum + cells.getVal(x, y);
			}
		}

		if ((sum > (pow((N / 3), 2)) * densl) && (randomNumber() < pdest)) 
		{
			for (int x = (int)round(N / 3.0) * 2 + 1; x < round(N / 3.0) * 3 + 1; x++) 
			{
				for (int y = (int)round(N / 3.0) * 2 + 1; y < round(N / 3.0) * 3 + 1; y++) 
				{
					cells.setVal(x, y, (randomNumber() < pini));
				}
			}
		}


		// Neighbour information storage
		Matrix<int>* aga = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++)
		{
			for (int y = 0; y < N; y++) 
			{
				aga->setVal(x, y, cells.getVal(up[x], left[y]));
			}
		}

		Matrix<int>* agb = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				agb->setVal(x, y, cells.getVal(up[x], centreCols[y]));
			}
		}

		Matrix<int>* agc = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				agc->setVal(x, y, cells.getVal(up[x], right[y]));
			}
		}

		Matrix<int>* agd = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				agd->setVal(x, y, cells.getVal(centreRows[x], left[y]));
			}
		}

		Matrix<int>* age = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				age->setVal(x, y, cells.getVal(centreRows[x], right[y]));
			}
		}

		Matrix<int>* agf = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				agf->setVal(x, y, cells.getVal(down[x], left[y]));
			}
		}

		Matrix<int>* agg = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				agg->setVal(x, y, cells.getVal(down[x], centreCols[y]));
			}
		}

		Matrix<int>* agh = new Matrix<int>(N,N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				agh->setVal(x, y, cells.getVal(down[x], right[y]));
			}
		}

		Matrix<int>* ag = new Matrix<int>(N, N);
		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				ag->setVal(x, y, cells.getVal(centreRows[x], centreCols[y]));
			}
		}

		// Compare against 1
		Matrix<int> ag1(*ag, 1);
		Matrix<int> aga1(*aga, 1);
		Matrix<int> agb1(*agb, 1);
		Matrix<int> agc1(*agc, 1);
		Matrix<int> agd1(*agd, 1);
		Matrix<int> age1(*age, 1);
		Matrix<int> agf1(*agf, 1);
		Matrix<int> agg1(*agg, 1);
		Matrix<int> agh1(*agh, 1);

		// Compare against 0
		Matrix<int> aga0(*aga, 0);
		Matrix<int> agb0(*agb, 0);
		Matrix<int> agc0(*agc, 0);
		Matrix<int> agd0(*agd, 0);
		Matrix<int> age0(*age, 0);
		Matrix<int> agf0(*agf, 0);
		Matrix<int> agg0(*agg, 0);
		Matrix<int> agh0(*agh, 0);

		// Freeing up memory
		delete ag;
		delete aga;
		delete agb;
		delete agc;
		delete agd;
		delete age;
		delete agf;
		delete agg;
		delete agh;

		// Automaton clustering rules
		Matrix<int> tempCluster(N, N);
		for (int x = 0; x < (N*N); x++) 
		{

			int temp =  (ag1.getValByIndex(x) && (randomNumber() < p)) || ((agb1.getValByIndex(x) &&
						agd1.getValByIndex(x))&& (randomNumber() < pr))|| ((age1.getValByIndex(x) && 
						agg1.getValByIndex(x))&& (randomNumber() < pr))|| ((agd1.getValByIndex(x) && 
						agg1.getValByIndex(x))&& (randomNumber() < pr))|| ((agb1.getValByIndex(x) &&
						age1.getValByIndex(x))&& (randomNumber()) < pr)
						|| (randomNumber() < pn);

			int temp2 = ag1.getValByIndex(x)  && aga1.getValByIndex(x) && agb1.getValByIndex(x) &&
						agd1.getValByIndex(x) && agf1.getValByIndex(x) && agg1.getValByIndex(x) &&
						agc0.getValByIndex(x) && age0.getValByIndex(x) && agh0.getValByIndex(x) &&
						(randomNumber() < pd);
			
			int temp3 = ag1.getValByIndex(x)  && agb1.getValByIndex(x) && agc1.getValByIndex(x) &&
						age1.getValByIndex(x) && agh1.getValByIndex(x) && agg1.getValByIndex(x) &&
						aga0.getValByIndex(x) && agd0.getValByIndex(x) && agf0.getValByIndex(x) &&
						(randomNumber() < pd);

			int temp4 = ag1.getValByIndex(x)  && agd1.getValByIndex(x) && aga1.getValByIndex(x) &&
						agb1.getValByIndex(x) && agc1.getValByIndex(x) && age1.getValByIndex(x) &&
						agf0.getValByIndex(x) && agg0.getValByIndex(x) && agh0.getValByIndex(x) &&
						(randomNumber() < pd);

			int temp5 =	ag1.getValByIndex(x)  && agd1.getValByIndex(x) && agf1.getValByIndex(x) &&
						agg1.getValByIndex(x) && agh1.getValByIndex(x) && age1.getValByIndex(x) &&
						aga0.getValByIndex(x) && agb0.getValByIndex(x) && agc0.getValByIndex(x) &&
						(randomNumber() < pd);

			int temp6 = temp - temp2 - temp3 - temp4 - temp5;
			
			if (temp6 < 0) 
				temp6 = 0;

			tempCluster.setValByIndex(x, temp6);
		}


		for (int x = 0; x < N; x++) 
		{
			for (int y = 0; y < N; y++) 
			{
				cells.setVal(centreRows[x], centreCols[y], tempCluster.getVal(x,y));
			}
		}


		if (cells.getTotal() > (N * N * densg) && (randomNumber() < pdest)) 
		{
			for (int x = 0; x < N; x++)
			{
				for (int y = 0; y < N; y++) 
				{
					cells.setVal(centreRows[x], centreCols[y], (randomNumber() 
								< pini));
				}
			}
		}


		for (int x = 0; x < clusterDynamics->getNumOfRows(); x++) 
		{
			for (int y = 0; y < clusterDynamics->getNumOfColumns(); y++) 
			{
				clusterDynamics->setVal(x, y, i, cells.getVal(centreRows[x], centreCols[y]));
			}
		}
	}

	// Freeing Memory
	delete[] up;
	delete[] down;
	delete[] centreRows;
	delete[] left;
	delete[] right;
	delete[] centreCols;

	return clusterDynamics;

}
