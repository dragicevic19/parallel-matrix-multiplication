#pragma once
#include <vector>
#include <iostream>

using namespace std;

class MatrixInfo
{
private:
	int rows;
	int cols;
	bool random;
public:
	long long* matrix;
	MatrixInfo();
	~MatrixInfo();
	void generateMatrix(int n, int m, bool rand);
	void generateRandomMatrix(int n, int m);
	void updateMatrixInfo(int n, int m, bool rand);
	void serialMultiplication(MatrixInfo&, MatrixInfo&);
	void printMatrix();
	int getRows();
	int getCols();
};