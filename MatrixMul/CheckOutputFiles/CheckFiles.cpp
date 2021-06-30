#include "CheckFiles.h"


CheckFiles::CheckFiles(char* inFN, char* secFN)
	: inFileName(inFN), secInFileName(secFN)
{
	cout << "Citanje iz fajlova..." << endl;
	openFile(inFileName);
	readFile(this->A);
	inFile.close();
	openFile(secInFileName);
	readFile(this->B);
	inFile.close();
	cout << "Provera..." << endl;
	doTask(2);
}

CheckFiles::CheckFiles(char* inFN, char* secFN, char* thirdFN)
	: inFileName(inFN), secInFileName(secFN), thirdInFileName(thirdFN)
{
	cout << "Citanje iz fajlova..." << endl;
	openFile(inFileName);
	readFile(this->A);
	inFile.close();
	openFile(secInFileName);
	readFile(this->B);
	inFile.close();
	openFile(thirdInFileName);
	readFile(this->C);
	inFile.close();
	cout << "Provera..." << endl;

	doTask(3);
}

void CheckFiles::openFile(char* fileName)
{
	inFile.open(fileName);
	if (!inFile.is_open())
	{
		cout << "Ulazni fajl " << fileName << " se ne moze otvoriti!" << endl;
		exit(1);
	}
}

void CheckFiles::readFile(Matrix& m)
{
	inFile >> m.rows >> m.cols;
	m.allocate();

	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; j++)
			inFile >> m.data[i * m.cols + j];
}

void CheckFiles::doTask(int numOfFiles)
{
	long long errNo = 0;
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			long long a = A.data[i * A.cols + j];
			long long b = B.data[i * A.cols + j];

			if (numOfFiles == 3)
			{
				long long c = C.data[i * A.cols + j];
				if (a != b || a != c || b != c) errNo++;
			}

			else if (numOfFiles == 2 && a != b)
			{
				cout << "A = " << a << " B = " << b << endl;
				system("pause");
				errNo++;
			}
		}
	}
	
	if (errNo)
		cout << "Postoji " << errNo << " gresaka" << endl;
	else
		cout << "Resenja se poklapaju!" << endl;
}