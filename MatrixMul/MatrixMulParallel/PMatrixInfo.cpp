#include "PMatrixInfo.h"
#include "tbb/blocked_range.h"
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"
#include "tbb/spin_mutex.h"
#include <iostream>

using namespace tbb;

class MatrixMul {
	PMatrixInfo* my_A;
	PMatrixInfo* my_B;
	PMatrixInfo* my_C;
public:
	void operator()(const blocked_range2d<size_t>& r) const
	{
		int colsC = my_C->getCols();
		int colsA = my_A->getCols();

		for (size_t i = r.rows().begin(); i != r.rows().end(); ++i) {
			for (size_t j = r.cols().begin(); j != r.cols().end(); ++j) {
				long long sum = 0;
				for (size_t k = 0; k < colsA; ++k)
					sum += my_A->matrix[i * colsA + k] * my_B->matrix[k * colsC + j];
				my_C->matrix[i* colsC + j] = sum;
			}
		}
	}

	MatrixMul(PMatrixInfo* a, PMatrixInfo* b, PMatrixInfo* c) :
		my_A(a), my_B(b), my_C(c) {}
};


PMatrixInfo::PMatrixInfo() {}

PMatrixInfo::~PMatrixInfo() 
{
	delete matrix;
}

int PMatrixInfo::getRows()
{
	return rows;
}

int PMatrixInfo::getCols()
{
	return cols;
}

void PMatrixInfo::updateMatrixInfo(int n, int m, bool rand)
{
	this->rows = n;
	this->cols = m;
	this->random = rand;
	this->matrix = new long long[rows*cols];
}

void PMatrixInfo::generateMatrix(int n, int m, bool randNum)
{
	updateMatrixInfo(n, m, randNum);

	if (randNum) generateRandomMatrix(n, m);
	else
	{
		int num = 1;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i*cols + j] = num++;
			}
		}
	}
}

void PMatrixInfo::generateRandomMatrix(int n, int m)
{
	srand(time(NULL));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i* cols + j] = rand() % 10;
		}
	}
}

void PMatrixInfo::printMatrix()
{
	cout << "---------------------------------------------------" << endl;
	cout << "\t\tMATRIX" << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i* cols + j] << "\t";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------" << endl;
}

void PMatrixInfo::parallelForMultiplication(PMatrixInfo& B, PMatrixInfo& resMatrix)
{
	resMatrix.matrix = new long long[rows * B.cols];
	resMatrix.rows = this->rows;
	resMatrix.cols = B.cols;
	parallel_for(blocked_range2d<size_t>(0, this->rows, 16, 0, B.cols, 32),
		MatrixMul(this, &B, &resMatrix));
}
