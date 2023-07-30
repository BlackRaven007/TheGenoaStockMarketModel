#include "logging.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>

void logResults(Matrix<double>& price, double* stockPriceReturnLog, int stockPriceReturnLen, Matrix<double>& vola1d)
{
    createDirectories();
    createPriceCSV(price);
    createStockPriceReturnLogCSV(stockPriceReturnLog, stockPriceReturnLen);
    createVola1dCSV(vola1d);

}

void createDirectories() {
    // Retrive path
    std::filesystem::current_path(std::filesystem::current_path().remove_filename());

    // Get current date and time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string dateTime = std::to_string(ltm->tm_mday) + "_" + std::to_string(1 + ltm->tm_mon) + "_" + std::to_string(1900 + ltm->tm_year) + "_"
        + std::to_string(5 + ltm->tm_hour) + std::to_string(30 + ltm->tm_min) + std::to_string(ltm->tm_sec);

    //Create Log directory and/or current datetime directory
    std::filesystem::create_directories("Logs/" + dateTime);

    // Set current path to new directory
    std::filesystem::current_path(std::filesystem::current_path().concat("//Logs//" + dateTime));
}

void createPriceCSV(Matrix<double>& price) {
    std::ofstream priceFile("price.csv");

    // Send data to the stream
    for (int i = 0; i < price.getWidth(); i++) {
        priceFile << price.getValByIndex(i) << "\n";
    }

    // Close the file
    priceFile.close();
}

void createStockPriceReturnLogCSV(double* stockPriceReturnLog, int stockPriceReturnLen) {
    std::ofstream stockPriceReturnLogFile("stockPriceReturnLog.csv");

    // Send data to the stream
    for (int i = 0; i < stockPriceReturnLen; i++) {
        stockPriceReturnLogFile << stockPriceReturnLog[i] << "\n";
    }

    // Close the file
    stockPriceReturnLogFile.close();
}

void createVola1dCSV(Matrix<double>& vola1d) {
    std::ofstream vola1dFile("vola1d.csv");

    // Send data to the stream
    for (int i = 0; i < vola1d.getWidth(); i++) {
        vola1dFile << vola1d.getValByIndex(i) << "\n";
    }

    // Close the file
    vola1dFile.close();
}