#pragma once
#include <iostream>
#include <fstream>

#include "Matrix.h"

using namespace std;

class CheckFiles
{
private:
	ifstream inFile;
	char* inFileName;
	char* secInFileName;
	char* thirdInFileName;
	Matrix A;
	Matrix B;
	Matrix C;

public:
	CheckFiles(char*, char*);
	CheckFiles(char*, char*, char*);
	void openFile(char*);
	void readFile(Matrix&);
	void doTask(int);
};