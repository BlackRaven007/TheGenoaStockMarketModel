#include "mathsFunc.h"

// Generates a random number between 0 and 1
double randomNumber() {
    if (!setup) {
        srand((int)time(0));
        setup = true;
    }
    double temp;
    if (debug)
        temp = 0.5;
    else
        temp = ((double)rand() / (double)(RAND_MAX));

    return temp;
}
