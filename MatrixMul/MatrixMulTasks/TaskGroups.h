#pragma once
#include "GTMatrixInfo.h"

#include <fstream>
#include "tbb/tick_count.h"

class TaskGroups
{
private:
	ifstream inFile;
	ofstream outFile;
	char* inFileName;
	char* outFileName;
	TGMatrixInfo A;
	TGMatrixInfo B;
	TGMatrixInfo resultMatrix;
public:
	TaskGroups(char*, char*);
	void openFile(char*);
	void readFile();
	void writeInFile();
	void doTask();
};

