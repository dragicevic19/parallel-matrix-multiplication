#pragma once
#include "PMatrixInfo.h"

#include <fstream>
#include "tbb/tick_count.h"

class ParallelForTask
{
private:
	ifstream inFile;
	ofstream outFile;
	char* inFileName;
	char* outFileName;
	PMatrixInfo A;
	PMatrixInfo B;
	PMatrixInfo resultMatrix;
public:
	ParallelForTask(char*, char*);
	~ParallelForTask();
	void openFile();
	void readFile();
	void writeInFile();
	void doTask();
};

