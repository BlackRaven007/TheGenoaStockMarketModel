#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <tuple>
#include <iostream>

template<typename Type>
class Matrix
{
public:
	/*
	Constuctor:
	- Creates a numOfRows by numOfColoumns Matrix
	*/
	Matrix(int numOfRows, int numOfColumns) 
	{
		this->m_numOfRows = numOfRows;
		this->m_numOfColumns = numOfColumns;
		this->m_width = numOfRows * numOfColumns;
		this->arrayMatrix = new Type[m_width];
	}

	/*
	Constuctor:
	- Creates a resulting comparison Matrix when
	  the parent Matrix is compared to the passed
	  in value
	*/
	Matrix(Matrix& parentMatrix, Type val) 
	{
		this->m_numOfRows = parentMatrix.getNumOfRows();
		this->m_numOfColumns = parentMatrix.getNumOfColumns();
		this->m_width = parentMatrix.getWidth();
		this->arrayMatrix = new Type[m_width];

		for (int i = 0; i < m_width; i++) 
		{
			if (parentMatrix.getValByIndex(i) == val) 
			{
				this->arrayMatrix[i] = 1;
			}

			else 
			{
				this->arrayMatrix[i] = 0;
			}
		}
	}

	// Destructor
	~Matrix() 
	{
		delete[] this->arrayMatrix;
	}

	// Get methods
	Type getVal(int x, int y) 
	{
		checkMatrixParameters(x, y);
		return this->arrayMatrix[getIndex(x, y)];
	}

	Type getValByIndex(int x) 
	{
		checkMatrixParameters(x);
		return this->arrayMatrix[x];
	}

	int getWidth() const { return this->m_width; }
	int getNumOfRows() const { return this->m_numOfRows; }
	int getNumOfColumns() const { return this->m_numOfColumns; }

	Type getTotal() const 
	{
		Type total{};
		for (int i = 0; i < this->m_width; i++)
		{
			total += this->arrayMatrix[i];
		}

		return total;
	}

	// Returns a dynamic list of index positions of non zero elements
	std::tuple<int*, int> findNonZeros() 
	{
		int count = 0;
		for (int i = 0; i < getWidth(); i++)
			if (getValByIndex(i) != 0)
				count++;

		if (!(count > 0))
			return { nullptr, 0 };

		int* nonZeroList;
		nonZeroList = new int[count];
		count = 0;

		for (int i = 0; i < getWidth(); i++)
			if (getValByIndex(i) != 0) 
			{
				nonZeroList[count] = i;
				count++;
			}

		return { nonZeroList, count };
	}

	// Returns a random index of an element that does not contain zero
	std::tuple<int*, int, int> getRandomIndexOfNonZero() 
	{
		auto results = findNonZeros();

		int randIndex = 0;

		if (std::get<1>(results) > 0)
			randIndex = rand() % std::get<1>(results) + 0;

		return { std::get<0>(results), std::get<1>(results), randIndex };
	}

	// WARNING: This function will set all elements to 0 within this Matrix
	std::tuple<Matrix<Type>*, int> getMatrixOfClusters() 
	{
		// Set up cluster matrix
		Matrix<Type>* cluster = new Matrix<Type>(getNumOfRows(), getNumOfColumns());
		cluster->setAll(0);

		int tally = 0;

		for (int y = 0; y < getNumOfColumns(); y++) 
		{
			for (int x = 0; x < getNumOfRows(); x++) 
			{
				if (getVal(x, y) > 0) 
				{
					tally++;
					startClustering(x, y, *cluster, tally);
				}
			}
		}

		return { cluster, tally };
	}

	// Returns the number of val found in the matrix
	std::tuple<int*, int> getNumberOfElementsEqualTo(Type val) 
	{
		int count = 0;

		for (int i = 0; i < getWidth(); i++)
			if (getValByIndex(i) == val)
				count++;

		int* elementList;
		elementList = new int[count];
		int x = 0;
		for (int i = 0; i < getWidth(); i++)
			if (getValByIndex(i) == val) 
			{
				elementList[x] = i;
				x++;
			}


		return { elementList, count };
	}



	// Set methods
	void setVal(int x, int y, Type val) {
		checkMatrixParameters(x, y);
		this->arrayMatrix[getIndex(x, y)] = val;
	}

	void setValByIndex(int pos, Type val) {
		checkMatrixParameters(pos);
		this->arrayMatrix[pos] = val;
	}

	void setAll(Type val) { std::fill_n(arrayMatrix, getWidth(), val); }

	// Display methods
	void showAll() {
		if (getNumOfColumns() > 1) {
			for (int x = 0; x < getNumOfRows(); x++) {
				for (int y = 0; y < getNumOfColumns(); y++) {
					std::cout << getVal(x, y) << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		else {
			for (int x = 0; x < getWidth(); x++) {
				std::cout << getValByIndex(x) << " ";
			}
			std::cout << std::endl << std::endl;
		}
		
	}

private:
	// Get methods
	int getIndex(int x, int y) const {
		int index = x + getNumOfRows() * y;
		if (index > getWidth() - 1)
			throw "Index out of bounds.";
		return index;
	};

	void checkMatrixParameters(int x, int y) {
		if (x > getNumOfRows() - 1 || x < 0)
			throw "X index is out of bounds.";
		if (y > getNumOfColumns() - 1 || y < 0)
			throw "Y index is out of bounds.";
	}

	void checkMatrixParameters(int pos) {
		if (pos > getWidth() - 1 || pos < 0)
			throw "Index out of bounds";
	}

	bool checkClusterParameters(int x, int y) {
		if (x > getNumOfRows() - 1 || x < 0)
			return false;
		if (y > getNumOfColumns() - 1 || y < 0)
			return false;
		return true;
	}

	void startClustering(int x, int y, Matrix<Type>& cluster, int tally) {
		cluster.setVal(x, y, tally);
		setVal(x, y, 0);
		if (checkClusterParameters(x + 1, y))
			if (getVal(x + 1, y) > 0)
				startClustering(x + 1, y, cluster, tally);
		if (checkClusterParameters(x - 1, y))
			if (getVal(x - 1, y) > 0)
				startClustering(x - 1, y, cluster, tally);
		if (checkClusterParameters(x, y + 1))
			if (getVal(x, y + 1) > 0)
				startClustering(x, y + 1, cluster, tally);
		if (checkClusterParameters(x, y - 1))
			if (getVal(x, y - 1) > 0)
				startClustering(x, y - 1, cluster, tally);
	}

	// Variable initializers
	int m_width, m_numOfRows, m_numOfColumns;
	Type* arrayMatrix;
};

#endif // !MATRIX_H