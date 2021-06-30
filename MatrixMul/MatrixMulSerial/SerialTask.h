#pragma once
#include "MatrixInfo.h"

#include <fstream>
#include "tbb/tick_count.h"

class SerialTask
{
private:
	ifstream inFile;
	ofstream outFile;
	char* inFileName;
	char* outFileName;
	MatrixInfo A;
	MatrixInfo B;
	MatrixInfo resultMatrix;
public:
	SerialTask(char*, char*);
	~SerialTask();
	void openFile();
	void readFile();
	void writeInFile();
	void doTask();
};

