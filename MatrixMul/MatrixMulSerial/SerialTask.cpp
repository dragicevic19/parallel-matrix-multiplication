#include "SerialTask.h"

using namespace tbb;


SerialTask::SerialTask(char* inFN, char* outFN) : inFileName(inFN), outFileName(outFN)
{
	openFile();
	readFile();
	inFile.close();
	doTask();
	writeInFile();

}

SerialTask::~SerialTask() {}

void SerialTask::openFile()
{
	inFile.open(inFileName);
	if (!inFile.is_open())
	{
		cout << "Ulazni fajl " << inFileName << " se ne moze otvoriti!" << endl;
		exit(1);
	}
}

void SerialTask::readFile()
{
	cout << "Ucitavanje iz fajla..." << endl;

	// r - rows, c - columns, b - isRandom (bool (1,0)) 
	int r1, c1, b1, r2, c2, b2;

	inFile >> r1 >> c1 >> b1;

	if (r1 < 2 || c1 < 2 || (b1 != 1 && b1 != 0))
	{
		cout << "Nepodrzan format ulaznog fajla!" << endl;
		exit(2);
	}
	A.generateMatrix(r1, c1, b1);

	inFile >> r2 >> c2 >> b2;

	if (r2 < 2 || c2 < 2 || (b2 != 1 && b2 != 0))
	{
		cout << "Nepodrzan format ulaznog fajla!" << endl;
		exit(2);
	}

	if (c1 != r2)
	{
		cout << "Broj kolona prve matrice i broj redova druge nije jednak!" << endl;
		exit(1);
	}
	B.generateMatrix(r2, c2, b2);
}

void SerialTask::writeInFile()
{
	cout << "Upisivanje rezultata u fajl <" << outFileName << "> ..." << endl;

	outFile.open(outFileName);
	int rows = resultMatrix.getRows();
	int cols = resultMatrix.getCols();

	outFile << rows << " " << cols << endl;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			outFile << resultMatrix.matrix[i * cols + j] << " ";
		outFile << endl;
	}

	outFile.close();
}

void SerialTask::doTask()
{
	//A.printMatrix();
	//B.printMatrix();
	//cout << "---------------------------------------------------" << endl;
	//cout << "\t\tMATRIX A*B Calculating..." << endl;
	//cout << "---------------------------------------------------" << endl;

	cout << "Racunanje AxB..." << endl;

	tick_count startTime = tick_count::now();
	A.serialMultiplication(B, resultMatrix);
	tick_count endTime = tick_count::now();

	//resultMatrix.printMatrix();

	cout << endl << "Vreme izvrsavanja serijskog programa : " << (endTime - startTime).seconds() * 1000 << "ms." << endl << endl;

}