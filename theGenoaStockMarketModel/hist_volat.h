#pragma once
#ifndef HIST_VOLAT_H
#define HIST_VOLAT_H

#include "agent.h"
#include "matrix.h"

// Market function initialisation
void hist_volat(int n, int t, Agent* listOfAgents, Matrix<double> &stockPrice,
				double buySigmak, double sellSigmaK);


#endif // !HIST_VOLAT_H
