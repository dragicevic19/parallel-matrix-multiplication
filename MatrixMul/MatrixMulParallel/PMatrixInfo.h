#pragma once
#include <vector>
#include <iostream>
using namespace std;

typedef vector<unsigned long long> Matrix;

class PMatrixInfo
{
private:
	//Matrix matrix;
	int rows;
	int cols;
	bool random;

public:
	long long* matrix;
	PMatrixInfo();
	~PMatrixInfo();
	int getRows();
	int getCols();
	void generateMatrix(int n, int m, bool rand);
	void generateRandomMatrix(int n, int m);
	void updateMatrixInfo(int n, int m, bool rand);
	void parallelForMultiplication(PMatrixInfo&, PMatrixInfo&);
	void printMatrix();
};