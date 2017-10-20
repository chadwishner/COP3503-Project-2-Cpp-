//pa2
//Chad Wishner
//6631-5393

#include "pa2.h"
#include <iostream>

int main(int argc, char **argv) {
	int userChoice;
	string programName;
	int programSize;
	linkedList* list = new linkedList();
	list -> initPages();

	if (argc != 2){
		cout << "Error, ending program" << endl;
		return 1;
	}
	else {
		string bestOrWorst = argv[1];
		cout << "Using " << bestOrWorst << " fit algoritm" << endl;

		menu();

		while (userChoice != 5){
			cout << "Choice - ";

			cin >> userChoice;

			cout << endl;

			switch (userChoice) {
				case 1:
					cout << "Program name - ";
					cin >> programName;
					cout << endl;
					cout << "Program size (KB) - ";
					cin >> programSize;
					cout << endl;
					programSize = kbToPages(programSize);
					
					if (list -> checkExistence(programName)){
						cout << "Error, program already open" << endl;
						break;
					} else {
						list -> insert(programName, programSize, bestOrWorst);
					}
					break;
				case 2:
					cout << "Program name - ";
					cin >> programName;

					if (!list -> checkExistence(programName)){
						cout << "The program is not open" << endl;
						break;
					} else if (list -> checkExistence(programName)){
						list -> kill(programName);
						cout << "Program " << programName << " successfully killed, " << list -> countPages(programName) << " page(s) reclaimed." <<endl;
						break;
					}
				case 3:
					cout << "There are " << list -> countFrag() << " fragment(s)";
					break;
				case 4:
					list -> print();
					cout << "\n" << endl;
					break;
				case 5:
					return 0;
					break;
				default:
					cout << "Not a proper choice, ending program" << endl;
					break;
			}
		}
	}
	return 0;
}
