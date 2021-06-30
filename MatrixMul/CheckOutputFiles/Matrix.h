#pragma once

class Matrix
{
public:
	long long* data;
	int rows;
	int cols;

	~Matrix();
	void allocate();
};