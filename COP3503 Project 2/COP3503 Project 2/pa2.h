//pa2
//Chad Wishner
//6631-5393

#include <iostream>
#include <string>
using namespace std;

void menu();
int kbToPages(int programSize);

void menu(){
	cout << "\n\t1. Add Program\n\t2. Kill Program\n\t3. Fragmentation\n\t4. Print Memory\n\t5. Exit\n" << endl;
}

int kbToPages(int programSize){
	int programPage = programSize / 4;
	if (programSize % 4 != 0){
		programPage++;
	}
	return programPage;
}

struct nodePage{
	string name;
	
	nodePage* nextNodePage;
	
	nodePage(string name){
		this->name = name;
	}
};

class linkedList{
	private:	nodePage* head;
	public:		linkedList();
				void initPages();
				void print();
				void insert(string name, int programSize, string bestOrWorst);
				void kill(string name);
				int countFrag();
				int countPages(string programName);
				bool checkExistence(string programName);
	
};

linkedList::linkedList(){
	head = NULL;
}

void linkedList::initPages(){
	nodePage* temp = NULL;
	
	for (int x = 0; x < 32; x++){
		if (head == NULL){
			head = new nodePage("free");
			temp = head;
		} else {
			temp -> nextNodePage = new nodePage("free");
			temp = temp -> nextNodePage;
		}
	}
}

void linkedList::print(){
	nodePage* temp = head;
	while (temp != NULL){
		for (int x = 0; x < 8; x++){
			if (temp -> name == "free"){
				cout << temp -> name << "\t";
			} else {
				cout << temp -> name << "\t\t";
			}
			temp = temp -> nextNodePage;
		}
		cout << "\n";
	}
}

void linkedList::insert(string name, int programSize, string bestOrWorst){
	int currentFrag = 0;
	int bestFrag = 0;
	nodePage* startNodeSmallest = NULL;
	nodePage* startNodeCurrent = NULL;
	if(head == NULL){
		head = new nodePage(name);
		return;
	}

	nodePage * temp = head;

	if(bestOrWorst == "best"){
		bestFrag = 33;
		while(temp!= NULL){
			if (temp -> name == "free"){
				startNodeCurrent = temp;
				currentFrag = 0;
				while (temp != NULL && temp -> name == "free"){
					currentFrag++;
					temp = temp -> nextNodePage;
				}
			}
			if (programSize <= currentFrag && bestFrag > currentFrag){
				startNodeSmallest = startNodeCurrent;
				bestFrag = currentFrag;
			}
			if (temp != NULL){
				temp = temp -> nextNodePage;
			}
		}
		if (bestFrag == 33 || programSize > bestFrag){
			cout << "Program " << name << " was not added successfully." << endl;
			return;
		}else {
			cout << "Program " << name << " added successfully: " << programSize << " page(s) used." << endl;
		}
		
		for (int x = 0; x < programSize; x++){
			startNodeSmallest -> name = name;
			
			if (startNodeSmallest != NULL){
				startNodeSmallest = startNodeSmallest -> nextNodePage;
			}
		}
		
	} else if (bestOrWorst == "worst"){
		bestFrag = 0;
		while(temp!= NULL){
			if (temp -> name == "free"){
				startNodeCurrent = temp;
				currentFrag = 0;
				while (temp != NULL && temp -> name == "free"){
					currentFrag++;
					temp = temp -> nextNodePage;
				}
			}
			if (programSize <= currentFrag && bestFrag < currentFrag){
				startNodeSmallest = startNodeCurrent;
				bestFrag = currentFrag;
			}
			if (temp != NULL){
				temp = temp -> nextNodePage;
			}
		}
		if (bestFrag == 0 || programSize > bestFrag){
			cout << "Program " << name << " was not added successfully." << endl;
			return;
		}else {
			cout << "Program " << name << " added successfully: " << programSize << " page(s) used." << endl;
		}
		
		for (int x = 0; x < programSize; x++){
			startNodeSmallest -> name = name;
			
			if (startNodeSmallest != NULL){
				startNodeSmallest = startNodeSmallest -> nextNodePage;
			}
		}
	}

}

void linkedList::kill(string name){
	nodePage* temp = head;
	while (temp != NULL){
		if (temp -> name == name){
			temp -> name = "free";
		}
		temp = temp -> nextNodePage;
	}
}

int linkedList::countFrag(){
	nodePage* temp = head;
	int count = 0;
	
	while (temp != NULL){
		if (temp -> name == "free"){
			
			if (temp -> nextNodePage != NULL){
				temp = temp -> nextNodePage;
			} else {
				return count;
			}
			if (temp -> name != "free" || temp -> nextNodePage == NULL){
				count ++;
			}
		} else {
			temp = temp -> nextNodePage;
		}
	}
	return count;
}

bool linkedList::checkExistence(string programName){
	bool exists = false;
	nodePage* temp = head;
	
	for (int x = 0; x < 32; x++){
		if (temp -> name == programName){
			exists = true;
			return exists;
		}
		if (temp -> nextNodePage != NULL){
			temp = temp -> nextNodePage;
		}
	}
	return exists;
}

int linkedList::countPages(string programName){
	int pages = 0;
	nodePage* temp = head;
	
	while (temp != NULL){
		if (temp -> name == programName){
			pages++;
		}
		if (temp -> nextNodePage != NULL){
			temp = temp -> nextNodePage;
		} else {
			return pages;
		}
	}
	return pages;
}
