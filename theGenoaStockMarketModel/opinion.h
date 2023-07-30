#pragma once
#ifndef OPINION_H
#define OPINION_H

#include "matrix.h"
#include <tuple>

/* Identifying clusters in Cellular Automaton outputand randomly resetting
	buy Probability of agents in that cluster
	INPUT: a n-by-n matrix coming from the AS output with
			n*n=N, the total number of agents in the market model.
	OUTPUT: a vector of length N with buy probabilities for all agents
			/buyProb) as well as the number of agents in clusters (sum)*/
std::tuple<Matrix<double>*, int> opinion(Matrix<int>* cells);

#endif // !OPINION_H