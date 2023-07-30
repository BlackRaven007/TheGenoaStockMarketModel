#pragma once
#include "matrix.h"
#ifndef LOGGING_H
#define LOGGING_H

#pragma warning(disable : 4996);

void logResults(Matrix<double>& price, double* stockPriceReturnLog, int stockPriceReturnLen, Matrix<double>& vola1d);

void createDirectories();

void createPriceCSV(Matrix<double>& price);

void createStockPriceReturnLogCSV(double* stockPriceReturnLog, int stockPriceReturnLen);

void createVola1dCSV(Matrix<double>& vola1d);

#endif // !HIST_VOLAT_H