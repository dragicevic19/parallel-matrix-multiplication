#pragma once
#include <vector>
#include <iostream>

using namespace std;

class TGMatrixInfo
{
private:
	int rows;
	int cols;
	bool random;

public:
	long long* matrix;
	TGMatrixInfo();
	~TGMatrixInfo();
	int getRows();
	int getCols();
	void generateMatrix(int n, int m, bool rand);
	void generateRandomMatrix(int n, int m);
	void updateMatrixInfo(int n, int m, bool rand);
	void tasksMultiplication(TGMatrixInfo&, TGMatrixInfo&);
	void oneRowOfResMatrix(TGMatrixInfo& B, TGMatrixInfo& resMatrix);
	void oneElementOfResMatrix(TGMatrixInfo& B, TGMatrixInfo& resMatrix);
	void partOfResMatrix(TGMatrixInfo& B, TGMatrixInfo& resMatrix);
	void calcOneElementOfResMatrix(long long*, long long*, long long*, int, int, int, int);
	void calcPartOfResMatrix(long long*, long long*, long long*, int, int, int, int, int, int);
	void calcOneRowOfResMatrix(long long*, long long*, long long*, int, int, int);
	void printMatrix();
};