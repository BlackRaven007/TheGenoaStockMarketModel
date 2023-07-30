#pragma once
#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "matrix.h"

template<typename Type3D>
class Matrix3D
{
public:
	/*
	Constuctor:
	- Creates a numOfRows by numOfColoumns Matrix
	*/
	Matrix3D(int numOfRows, int numOfColumns, int depth)
	{
		this->m_numOfRows = numOfRows;
		this->m_numOfColumns = numOfColumns;
		this->m_depth = depth;
		this->m_width = this->m_numOfRows * this->m_numOfColumns * this->m_depth;
		this->arrayMatrix = new Type3D[this->m_width];
	}

	/*
	Constuctor:
	- Creates a resulting comparison Matrix when
	  the parent Matrix is compared to the passed
	  in value
	*/
	Matrix3D(Matrix3D parentMatrix, Type3D val) 
	{
		this->m_numOfRows = parentMatrix.getNumOfRows();
		this->m_numOfColumns = parentMatrix.getNumOfColumns();
		this->m_depth = parentMatrix.getDepth();
		this->m_width = parentMatrix.getWidth();
		this->arrayMatrix = new Type3D[this->m_width];

		for (int i = 0; i < this->m_width; i++) 
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
	~Matrix3D() { delete[] arrayMatrix; }

	// Get methods
	Type3D getVal(int x, int y, int z) 
	{
		checkMatrix3DParameters(x, y, z);
		return this->arrayMatrix[getIndex(x, y, z)];
	}

	Type3D getValByIndex(int pos) 
	{
		checkMatrix3DParameters(pos);
		return this->arrayMatrix[pos];
	}

	int getWidth() const { return this->m_width; }
	int getNumOfRows() const { return this->m_numOfRows; }
	int getNumOfColumns() const { return this->m_numOfColumns; }
	int getDepth() const { return this->m_depth; }

	Type3D getTotal() const 
	{
		Type3D total{};
		for (int i = 0; i < getWidth(); i++) 
		{
			total += this->arrayMatrix[i];
		}

		return total;
	}

	// Gets a dimension from this multi dimensional matrix
	Matrix<Type3D>* getCopyOfDimension(int z) 
	{
		Matrix<Type3D>* dimMatrix = new Matrix<Type3D>(getNumOfRows(), getNumOfColumns());
		for (int x = 0; x < getNumOfRows(); x++) 
		{
			for (int y = 0; y < getNumOfColumns(); y++) 
			{
				dimMatrix->setVal(x, y, getVal(x, y, z));
			}
		}

		return dimMatrix;
	}


	// Set methods
	void setVal(int x, int y, int z, Type3D val) 
	{
		checkMatrix3DParameters(x, y, z);
		this->arrayMatrix[getIndex(x, y, z)] = val;
	}

	void setValByIndex(int pos, Type3D val) 
	{
		checkMatrix3DParameters(pos);
		this->arrayMatrix[pos] = val;
	}

	void setAll(Type3D val) { std::fill_n(arrayMatrix, getWidth(), val); }

	// Display methods
	void showAllInDimension(int z) 
	{
		for (int x = 0; x < getNumOfRows(); x++) 
		{
			for (int y = 0; y < getNumOfColumns(); y++) 
			{
				std::cout << getVal(x, y, z) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

private:
	// Get methods
	int getIndex(int x, int y, int z) const 
	{
		int index = x + ((getNumOfRows()) * y) + ((getNumOfRows()) * (getNumOfColumns()) * z);
		if (index > getWidth() - 1)
			throw "Index out of bounds.";
		return index;
	}

	void checkMatrix3DParameters(int x, int y, int z) 
	{
		if (x > getNumOfRows() - 1 || x < 0)
			throw "X index is out of bounds.";
		if (y > getNumOfColumns() - 1 || y < 0)
			throw "Y index is out of bounds.";
		if (z > getDepth() - 1 || z < 0)
			throw "Z index is out of bounds.";
	}

	void checkMatrix3DParameters(int pos) 
	{
		if (pos > getWidth() - 1 || pos < 0)
			throw "Index out of bounds";
	}

	// Variable initializers
	int m_width, m_numOfRows, m_numOfColumns, m_depth;
	Type3D* arrayMatrix;
};

#endif // !MATRIX3D_H