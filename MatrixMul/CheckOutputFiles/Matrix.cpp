#include "Matrix.h"

Matrix::~Matrix()
{
	delete data;
}

void Matrix::allocate()
{
	data = new long long[rows * cols];
}

