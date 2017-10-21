//pa2
//Chad Wishner
//6631-5393

#include "pa2.h"
#include <iostream>

/* main
 @parameters int argc, char** argv
 */
int main(int argc, char** argv) {
	//create variables
	int userChoice;
	string programName;
	int programSize;
	
	//create new linked list and initialize 32 pages
	linkedList* list = new linkedList();
	list -> initPages();

	//check to make sure that the user started program with proper
	if (argc != 2){
		cout << "Error, ending program" << endl;
		return 1;
	}
	else {
		//save the argument as a string
		string bestOrWorst = argv[1];
		
		//proper formating
		cout << "Using " << bestOrWorst << " fit algoritm" << endl;

		//print menu
		menu();

		//loop so that way the user can keep picking options
		while (userChoice != 5){
			cout << "Choice - ";
			cin >> userChoice;

			//check to see if the user entered an int, if not end program
			if (cin.fail()){
				cout << "Must enter an int, ending program\n" << endl;
				return -1;
			}
			cout << endl;

			//switch statement for user input
			switch (userChoice) {
				case 1:
					//open program
					
					cout << "Program name - ";
					cin >> programName;
					cout << endl;
					
					cout << "Program size (KB) - ";
					cin >> programSize;
					
					//check to see if the user entered an int, if not end program
					if (cin.fail()){
						cout << "Must enter an int, ending program\n" << endl;
						return -1;
					}
					cout << endl;
					
					//convert kb to pages
					programSize = kbToPages(programSize);
					
					//check to see if program is already open, if so break and allow user to make a new choice
					if (list -> checkExistence(programName)){
						cout << "Error, program already open\n" << endl;
						break;
					} else {
						//insert program
						list -> insert(programName, programSize, bestOrWorst);
					}
					break;
				case 2:
					//kill program
					
					cout << "Program name - ";
					cin >> programName;

					//check if program is open, if not allow user to pick new option
					if (!list -> checkExistence(programName)){
						cout << "The program is not open\n" << endl;
						break;
						
					//kill program
					} else if (list -> checkExistence(programName)){
						int numberPages = list -> countPages(programName);
						list -> kill(programName);
						cout << "Program " << programName << " successfully killed, " << numberPages << " page(s) reclaimed.\n" <<endl;
						break;
					}
				case 3:
					//count fragments and print with proper formating
					
					cout << "There are " << list -> countFrag() << " fragment(s)" << endl;
					break;
				case 4:
					//print memory
					
					list -> print();
					cout << "\n" << endl;
					break;
				case 5:
					//exit program
					
					return 0;
					break;
				default:
					//allow user to enter a new option if they do not enter an int 1-5
					
					cout << "Not a proper choice, please enter an option 1-5\n" << endl;
					break;
			}
		}
	}
	return 0;
}
