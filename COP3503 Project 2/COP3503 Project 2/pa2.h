//pa2
//Chad Wishner
//6631-5393

#include <iostream>
#include <string>
using namespace std;

//declare functions
void menu();
int kbToPages(int programSize);

/* print function
 @return void
 */
void menu(){
	cout << "\n\t1. Add Program\n\t2. Kill Program\n\t3. Fragmentation\n\t4. Print Memory\n\t5. Exit\n" << endl;
}

/* kb to pages function
 @parameter int programSize
 @return int programPage
 */
int kbToPages(int programSize){
	
	//divide int by 4 because 4kb per page
	int programPage = programSize / 4;
	
	//check if there is a remainder, if so, increment programPage
	if (programSize % 4 != 0){
		programPage++;
	}
	return programPage;
}

/* struct nodePage
 includes string name
 node* nextNodePage
 
 */
struct nodePage{
	string name;
	
	nodePage* nextNodePage;
	
	//allow access to node name
	nodePage(string name){
		this->name = name;
	}
};

/* linked list class
 */
class linkedList{
	private:	nodePage* head;
	
	//declare functions
	public:		linkedList();
				void initPages();
				void print();
				void insert(string name, int programSize, string bestOrWorst);
				void kill(string name);
				int countFrag();
				int countPages(string programName);
				bool checkExistence(string programName);
	
};

/* initialize linkedlist
 */
linkedList::linkedList(){
	head = NULL;
}

/* initialize 32 pages
 @return void
 */
void linkedList::initPages(){
	
	//create a temp node
	nodePage* temp = NULL;
	
	//create 32 nodes with "free" for name
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

/* print linked list with proper formating
 @return void
 */
void linkedList::print(){
	nodePage* temp = head;
	while (temp != NULL){
		
		//proper formatting
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

/* insert function
 @parameter string name, int programSize, string bestOrWorst
 @return void
 */
void linkedList::insert(string name, int programSize, string bestOrWorst){
	
	//initialize variables
	int currentFrag = 0;
	int bestFrag = 0;
	nodePage* startNodeSmallest = NULL;
	nodePage* startNodeCurrent = NULL;
	
	if(head == NULL){
		head = new nodePage(name);
		return;
	}

	nodePage * temp = head;

	//if user wanted best algorithm
	if(bestOrWorst == "best"){
		
		//set bestFrag to 33 to check if we find an open frag
		bestFrag = 33;
		
		//loop until we reach end of list
		while(temp!= NULL){
			
			//if the node is free, count and continure until the node is not free
			if (temp -> name == "free"){
				startNodeCurrent = temp;
				currentFrag = 0;
				while (temp != NULL && temp -> name == "free"){
					currentFrag++;
					temp = temp -> nextNodePage;
				}
			}
			
			//if this is the smallest found fragment, save it
			if (programSize <= currentFrag && bestFrag > currentFrag){
				startNodeSmallest = startNodeCurrent;
				bestFrag = currentFrag;
			}
			
			//if the temp node is not at NULL, progress to next node
			if (temp != NULL){
				temp = temp -> nextNodePage;
			}
		}
		
		//if a fragment has not been found or the program will not fit in it, do not add program
		if (bestFrag == 33 || programSize > bestFrag){
			cout << "Program " << name << " was not added successfully.\n" << endl;
			return;
		}else {
			cout << "Program " << name << " added successfully: " << programSize << " page(s) used.\n" << endl;
		}
		
		//add program to all necessary pages
		for (int x = 0; x < programSize; x++){
			startNodeSmallest -> name = name;
			
			if (startNodeSmallest != NULL){
				startNodeSmallest = startNodeSmallest -> nextNodePage;
			}
		}
	
	//if user wants worse fit algorithm
	} else if (bestOrWorst == "worst"){
		
		//set bestFrag to 0 to check if we find an open fragment
		bestFrag = 0;
		
		//loop until we reach end of list
		while(temp!= NULL){
			
			//if the node is free, count and continure until the node is not free
			if (temp -> name == "free"){
				startNodeCurrent = temp;
				currentFrag = 0;
				while (temp != NULL && temp -> name == "free"){
					currentFrag++;
					temp = temp -> nextNodePage;
				}
			}
			
			//if this is the largest found fragment, save it
			if (programSize <= currentFrag && bestFrag < currentFrag){
				startNodeSmallest = startNodeCurrent;
				bestFrag = currentFrag;
			}
			
			//if the temp node is not at NULL, progress to next node
			if (temp != NULL){
				temp = temp -> nextNodePage;
			}
		}
		
		//if a fragment has not been found or the program will not fit in it, do not add program
		if (bestFrag == 0 || programSize > bestFrag){
			cout << "Program " << name << " was not added successfully.\n" << endl;
			return;
		}else {
			cout << "Program " << name << " added successfully: " << programSize << " page(s) used.\n" << endl;
		}
		
		//add program to all necessary pages
		for (int x = 0; x < programSize; x++){
			startNodeSmallest -> name = name;
			
			if (startNodeSmallest != NULL){
				startNodeSmallest = startNodeSmallest -> nextNodePage;
			}
		}
	}

}
/* kill function
 @parameter string name
 @return void
 */
void linkedList::kill(string name){
	nodePage* temp = head;
	
	//loop to end of list
	while (temp != NULL){
		
		//if a node with the name is found, set its name to "free"
		if (temp -> name == name){
			temp -> name = "free";
		}
		
		//move to next node
		temp = temp -> nextNodePage;
	}
}
/* fragment counter function
 @return int fragment
 */
int linkedList::countFrag(){
	
	//initialize temp node pointer and count int
	nodePage* temp = head;
	int count = 0;
	
	//loop till end of list
	while (temp != NULL){
		
		//if we find a free node
		if (temp -> name == "free"){
			
			//if we can continue, continue, if not, then return count
			if (temp -> nextNodePage != NULL){
				temp = temp -> nextNodePage;
			} else {
				return count;
			}
			//if we reach a node that is not free or it is pointing to null, increment count to signify the end of a fragment
			if (temp -> name != "free" || temp -> nextNodePage == NULL){
				count ++;
			}
		} else {
			temp = temp -> nextNodePage;
		}
	}
	return count;
}

/* check if a program is open function
 @parameter string programName
 @return bool existence
 */
bool linkedList::checkExistence(string programName){
	
	//initialize variables and temp node pointer
	bool exists = false;
	nodePage* temp = head;
	
	//loop through all pages
	for (int x = 0; x < 32; x++){
		
		//if the program is found, set exists to true and return
		if (temp -> name == programName){
			exists = true;
			return exists;
		}
		
		//move to next node
		if (temp -> nextNodePage != NULL){
			temp = temp -> nextNodePage;
		}
	}
	return exists;
}

/* count pages helper function for the format of killing a program
 @parameter string programName
 @return int number of pages
 */
int linkedList::countPages(string programName){
	
	//initialize variable and temp node pointer
	int pages = 0;
	nodePage* temp = head;
	
	//loop until we reach the end of the list
	while (temp != NULL){
		
		//if a node is found with the program name, increment pages
		if (temp -> name == programName){
			pages++;
		}
		//move to next node
		temp = temp -> nextNodePage;
	}
	return pages;
}
