#pragma once
#ifndef MATHSFUNC_H
#define MATHSFUNC_H

#include <random>
#include <iostream>

static bool distSetup = false;
static bool setup = false;
static bool debug = false;

template<typename Type>
// Calculates the Standard Deviation of an array
double calculateSD(Type* data, double lengthOfArray) 
{
    double sum = 0.0, mean, standardDeviation = 0.0;
    int i;

    for (i = 0; i < lengthOfArray; ++i) 
    {
        sum += data[i];
    }

    mean = sum / lengthOfArray;

    for (i = 0; i < lengthOfArray; ++i) 
    {
        standardDeviation += pow(data[i] - mean, 2);
    }

    double ans = sqrt(standardDeviation / lengthOfArray);

    return ans;
}

template<typename Type>
// Random distribution
double normrnd(Type mean, Type sigma) 
{
    try 
    {

        if (sigma == 0)
            return mean;
        
        double dist = mean;

        if (!distSetup) {
            
            distSetup = true;
        }
        std::random_device rd{};
        std::mt19937 gen{ rd() };
        std::normal_distribution<double> distribution(mean, sigma);
        dist = distribution(gen);
        
        return dist;
    }

    catch (...) 
    {
        return mean;
    }

}

double randomNumber(); 


#endif // !MATHSFUNC_H