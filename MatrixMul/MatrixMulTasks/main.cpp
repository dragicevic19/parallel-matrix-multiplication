#include <iostream>
#include "TaskGroups.h"

using namespace std;

/**
 * ulazni fajl treba da bude u sledecem formatu:
 * 10 10 0 (oznacava da prva matrica ima 10 redova, 10 kolona i treci parametar je 0 - u matrici ce biti redom brojevi 1 2 3 4.., ili 1 - bice random brojevi od 0 - 10
 * 10 10 0 (oznake za drugu matricu, isto kao i za prvu)
**/

int main(int argc, char* argv[])	
{
	if (argc != 3)
	{
		cout << "Unesite naziv ulaznog i izlaznog fajla kao argumente komandne linije!" << endl;
		return -1;
	}
	
	char* inTxtFile = argv[1];
	char* outTxtFile = argv[2];
	TaskGroups tasks(inTxtFile, outTxtFile);


	return 0;

}

