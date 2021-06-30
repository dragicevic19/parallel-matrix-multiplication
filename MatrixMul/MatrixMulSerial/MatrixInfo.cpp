#include "MatrixInfo.h"

MatrixInfo::MatrixInfo(){}

MatrixInfo::~MatrixInfo() 
{
	delete matrix;
}

void MatrixInfo::updateMatrixInfo(int n, int m, bool rand)
{
	this->rows = n;
	this->cols = m;
	this->random = rand;
	this->matrix = new long long[rows*cols];
}

void MatrixInfo::generateMatrix(int n, int m, bool randNum)
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

void MatrixInfo::generateRandomMatrix(int n, int m)
{
	srand(NULL);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i*cols + j] = rand() % 10;
		}
	}
}

void MatrixInfo::printMatrix()
{
	cout << "---------------------------------------------------" << endl;
	cout << "\t\tMATRIX" << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i*cols + j] << "\t";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------" << endl;

}

int MatrixInfo::getCols()
{
	return cols;
}

int MatrixInfo::getRows()
{
	return rows;
}


void MatrixInfo::serialMultiplication(MatrixInfo& B, MatrixInfo& resMatrix)
{
	resMatrix.matrix = new long long[rows*B.cols];
	resMatrix.rows = this->rows;
	resMatrix.cols = B.cols;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < B.cols; j++) {
			long long sum = 0;
			for (int k = 0; k < cols; k++)
			{
				sum += this->matrix[i * cols + k] * B.matrix[k * B.cols + j];
			}
			resMatrix.matrix[i*B.cols + j] = sum;
		}
	}
}