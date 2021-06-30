#include <iostream>
#include <fstream>
#include "CheckFiles.h"

using namespace std;


int main(int argc, char* argv[])
{
	if (argc > 4 || argc < 3)
	{
		cout << "Unesite naziv ulaznih fajlova kao argumente komandne linije!" << endl;
		return -1;
	}
	if (argc == 3)
		CheckFiles check(argv[1], argv[2]);
	else 
		CheckFiles check(argv[1], argv[2], argv[3]);

	return 0;

}