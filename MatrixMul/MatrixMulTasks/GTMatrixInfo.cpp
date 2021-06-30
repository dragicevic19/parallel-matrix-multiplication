#include "GTMatrixInfo.h"
#include "tbb/blocked_range.h"
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"
#include "tbb/spin_mutex.h"
#include <iostream>

using namespace tbb;

TGMatrixInfo::TGMatrixInfo() {}

TGMatrixInfo::~TGMatrixInfo()
{
	delete matrix;
}

int TGMatrixInfo::getRows()
{
	return rows;
}
int TGMatrixInfo::getCols()
{
	return cols;
}

void TGMatrixInfo::updateMatrixInfo(int n, int m, bool rand)
{
	this->rows = n;
	this->cols = m;
	this->random = rand;
	this->matrix = new long long[rows * cols]{0};
	if (!matrix)
	{
		cout << "Memory allocation failed\n";
	}
}

void TGMatrixInfo::generateMatrix(int n, int m, bool randNum)
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
				matrix[i * cols + j] = num++;
			}
		}
	}
}

void TGMatrixInfo::generateRandomMatrix(int n, int m)
{
	srand(time(NULL));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i * cols + j] = rand() % 10;
		}
	}
}

void TGMatrixInfo::printMatrix()
{
	cout << "---------------------------------------------------" << endl;
	cout << "\t\tMATRIX" << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i * cols + j] << "\t";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------" << endl;
}


void TGMatrixInfo::tasksMultiplication(TGMatrixInfo& B, TGMatrixInfo& resMatrix)
{
	resMatrix.matrix = new long long[rows * B.cols];
	resMatrix.rows = this->rows;
	resMatrix.cols = B.cols;
	

	oneRowOfResMatrix(B, resMatrix);		// svaki zadatak racuna jedan red rezultujuce matrice

	//oneElementOfResMatrix(B, resMatrix);	// svaki zadatak racuna jedan element rezultujuce matrice

	//partOfResMatrix(B, resMatrix);			// delim rezultujucu matricu na 4 dela i svaki zadatk racuna jedan deo
}

void TGMatrixInfo::oneRowOfResMatrix(TGMatrixInfo& B, TGMatrixInfo& resMatrix)
{
	task_group g;
	for (int i = 0; i < rows; ++i)
	{																	
		g.run([&, i] {calcOneRowOfResMatrix(this->matrix, B.matrix, resMatrix.matrix, i, cols, B.cols); });
	}
	g.wait();
}

void TGMatrixInfo::oneElementOfResMatrix(TGMatrixInfo& B, TGMatrixInfo& resMatrix)
{
	task_group g;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < B.cols; j++)
			g.run([&, i, j] {calcOneElementOfResMatrix(this->matrix, B.matrix, resMatrix.matrix, i, j, cols, B.cols); });
	}
	g.wait();
}

void TGMatrixInfo::partOfResMatrix(TGMatrixInfo& B, TGMatrixInfo& resMatrix)
{
	task_group g;
	g.run([&] {calcPartOfResMatrix(this->matrix, B.matrix, resMatrix.matrix, 0, 0, rows / 2, B.getCols() / 2, cols, B.cols); });
	g.run([&] {calcPartOfResMatrix(this->matrix, B.matrix, resMatrix.matrix, rows / 2, 0, rows, B.getCols() / 2, cols, B.cols); });
	g.run([&] {calcPartOfResMatrix(this->matrix, B.matrix, resMatrix.matrix, 0, B.getCols() / 2, rows / 2, B.getCols(), cols, B.cols); });
	g.run([&] {calcPartOfResMatrix(this->matrix, B.matrix, resMatrix.matrix, rows / 2, B.getCols() / 2, rows, B.getCols(), cols, B.cols); });

	g.wait();
}

void TGMatrixInfo::calcOneRowOfResMatrix(long long* A, long long* B, long long* C, int row, int colsA, int colsB)
{
	for (int j = 0; j < colsB; j++)
	{
		long long sum = 0;
		for (int k = 0; k < colsA; k++)
		{
			sum += A[row * colsA + k] * B[k * colsB + j];
		}
		C[row * colsB + j] = sum;
	}
}

void TGMatrixInfo::calcPartOfResMatrix(long long* A, long long* B, long long* C, int rStart, int cStart, int rEnd, int cEnd, int colsA, int colsB)
{
	for (int i = rStart; i < rEnd; i++)
	{
		for (int j = cStart; j < cEnd; j++)
		{
			long long sum = 0;
			for (int k = 0; k < colsA; k++)
				sum += A[i * colsA + k] * B[k * colsB + j];
			C[i * colsB + j] = sum;
		}
	}
}

void TGMatrixInfo::calcOneElementOfResMatrix(long long* A, long long* B, long long* C, int i, int j, int colsA, int colsB)
{
	unsigned long long sum = 0;
	for (int k = 0; k < colsA; k++)
	{
		sum += A[i * colsA + k] * B[k * colsB + j];
	}
	C[i * colsB + j] = sum;
}
