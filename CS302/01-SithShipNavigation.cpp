
/*
* Name: Kristen kaiser, 1008179340, Assignment 1
* Description: simulates creating 10000 sith ships, setting their 
navigation source to a navigation tower then changes the navigation 
source to a resurgent ship
* Input: text doc of of all possible ship names with three lines of 
header to be givein in commandline
* Output: notation of every ship being set to the first navigation 
tower followed by notation of every ship (by name) changing to new
navigation source
*/


//CS 302 Assignment 1 By Jorge Fonseca
//Build as: g++ ast01.cpp -g -std=c++17
//Execute as: ./a.out shipnames.txt
//Debug as: 'gdb a.out' and then type 'r shipnames.txt'
//Check for memory leaks with valgrind ./a.out shipnames.txt
#include <iostream> //cout
#include <fstream>  //ifstream
#include <cstdlib>  //rand()
#include <string>   //stringz
#include <time.h>

using namespace std;

/*
* class_identifier: inports holds and distributes array of potential names for ships 
* constructors: 
	RNGnamer(string)
* public members: 
	printAllPossibleNames()
	string generateName()	
* static members: none
*/
class RNGnamer {
public:
	RNGnamer(string);// : size(0);
	~RNGnamer() {
		delete[] names;//use delete to de-allocate your name array.
		names = NULL;
	}
	void printAllPossibleNames() {
		cout << "All Possible Ship Names:" << endl;
		for (int i = 0; i < size; i++) {
			cout << i << ": " << names[i] << endl;
		}
		cout << endl;
	}
	string generateName() {
		return names[rand() % size];
	}
private:
	int size;
	string *names;
};

/*
* class_identifier: for creation of genaric objects
* constructors:
	entity_t()
* public members:
	virtual string whatamI()
	string getName()
* static members:
	 ent_cnt
*/
class entity_t {
public:
	entity_t() : id(ent_cnt++) {}
	virtual string whatamI() = 0; //Virtual Function whatamI() that returns a string
	string getName() { return name; }// function getName that returns a string with the name
protected:
	static int ent_cnt;//static integer variable called ent_cnt that keeps track of how many entities there are
	int id; //individual entity id
	string name;
};
int entity_t::ent_cnt = 0;// Initalize ent_cnt static variable with 0.

/*
* class_identifier: navigation tower 
* constructors:
	navigation_tower()
* public members:
	string whatamI()
* static members: none
*/
class navigation_tower : public entity_t {
public:
	navigation_tower() { name = "Exegol Navigation Tower #" + to_string(id); }
	string whatamI() { return "Navigation_Tower"; }
};

/*
* class_identifier: Xyston StarDestroyer
* constructors: 
	Xyston_class_StarDestroyer(RNGnamer)
* public members:
	 setNavSource(entity_t *)
	 void printNavSource()
	 void printNavSource()
	 string whatamI()
* static members:none
* public variables:
	string navSourceName
	string navSourceType
*/
class Xyston_class_StarDestroyer : public entity_t {//for the Xyston_class_StarDestroyer class that inherits from entity_t
public:
	string navSourceName;
	string navSourceType;
	Xyston_class_StarDestroyer(RNGnamer &arrayOfNames) {//sets name randomly and sets navigation source and name to blank  
		navSourceName = "";
		navSourceType = "";
		name = arrayOfNames.generateName() + " #" + to_string(id);
	}
	void setNavSource(entity_t *x) {
		navSourceName = x->getName();
		navSourceType = x->whatamI();
	}
	void printNavSource() {
		if (navSourceType == "")//check if navigation is set
			cout << "No Navigator Source is set. Cannot escape Exogol without one!" << endl;
		else
			cout << "Current Navigation Source is a " << navSourceType << " : " << navSourceName << endl;
	}
	string whatamI() { return "Xyston class StarDestroyer"; }

};

/*
* function_identifier: constructor to inport and create array of all possible ship names 
* parameters: string filename 
* return value: none
*/
RNGnamer::RNGnamer(string filename = "shipnames.txt") : size(0) {
	//Your Code Here:
	//string temp;
	ifstream fin;//	//Using filestream open the file with shipnames.
	fin.open(filename.c_str());
	while (!fin.eof() && isalnum(fin.peek())) {//!isblank(fin.peek())) {	//Read the file once the end of it to count the number of ships.
		size++;		//Keep that value in size class variable.
		fin.ignore(256, '\n'); //getline(fin, temp);
	}
	size = size - 3; //accounts for 3 lines of header 
	fin.close(); //Close file.
	names = new string[size];	//Use new to dynamically allocate an array of strings called names.  For the size use the number you just read into the size class variable.
	fin.open(filename.c_str());	//Open file again.
	for (int i = 0; i < 3; i++) //Note that the first 3 lines will always be a header so you want to skip them when reading into the array.
		fin.ignore(256, '\n');
	for (int i = 0; i < size; i++)
		getline(fin, names[i]);	//Read in all ship names into the names array you just made.
	fin.close();	//close file.
	cout << "Total Number of Possible Ship Names Read: " << size << endl;
}

/*
* class_identifier: Resurgent Star Destroyer
* constructors: 
	Resurgent_class_StarDestroyer(string
* public members: 
	string whatamI()
* static members:none
*/
class Resurgent_class_StarDestroyer : public entity_t {
public:
	Resurgent_class_StarDestroyer(string name = "Capital Ship Steadfast") {
		this->name = name;
	}
	string whatamI() {
		return "Resurgent_StarDestroyer";
	}
};

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Error: Missing shipnames.txt!" << endl;
		return 1;
	}
	srand(time(NULL)); //Seed Rand!
	RNGnamer nameList(argv[1]);
	const int fleet_size = 10000;
	//#define DEBUG
#ifdef DEBUG
	fleet_size = 10; //for small tests (sample output given is with this size)
#endif
	Resurgent_class_StarDestroyer Steadfast_flagship;
	//Xyston_class_StarDestroyer Sith_Eternal_Fleet[fleet_size](nameList); //old
	Xyston_class_StarDestroyer *Sith_Eternal_Fleet[fleet_size];
	for (int i = 0; i < fleet_size; i++) {
		Sith_Eternal_Fleet[i] = new Xyston_class_StarDestroyer(nameList);
	}
	navigation_tower Exogol_Tower;

	cout << "\nAt last the work of generations is complete. "
		<< "The great error is corrected. The day of victory is at hand. "
		<< "The day of revenge. The day of the Sith.\n" << endl;

	for (int i = 0; i < fleet_size; ++i) {
		Sith_Eternal_Fleet[i]->setNavSource(&Exogol_Tower);
	}

	cout << "Nav Source for fleet:" << endl;
	for (auto ship : Sith_Eternal_Fleet)
		ship->printNavSource();

	cout << "\nThe Resistance is targetting the Navigation Tower. "
		<< "Transfer the signal to the Steadfast. "
		<< "We'll guide the fleet ourselves." << endl;

	cout << "\nSwitching Nav Source to Steadfast." << endl;
	for (int i = 0; i < fleet_size; ++i) {
		Sith_Eternal_Fleet[i]->setNavSource(&Steadfast_flagship);
		cout << Sith_Eternal_Fleet[i]->getName() << ": ";
		Sith_Eternal_Fleet[i]->printNavSource();
	}

	for (int i = 0; i < fleet_size; i++) {
		delete Sith_Eternal_Fleet[i];
	} //Did you ever hear the tragedy of Darth Plagueis the wise?

#ifdef DEBUG
	nameList.printAllPossibleNames(); //Test if read successfully.
	cout << "RNG Test: " << nameList.generateName() << endl; //Test RNG of names (should be different each run)
	cout << "RNG Test: " << nameList.generateName() << endl; //Test RRG of names (should be different each run)

	Xyston_class_StarDestroyer ship1(nameList);
	Xyston_class_StarDestroyer ship2(nameList);

	navigation_tower test_tower;
	Resurgent_class_StarDestroyer flagship;

	ship1.printNavSource(); //No Nav Set

	//ship1.setNavSource(dynamic_cast<entity_t*>(&test_tower));
	ship1.setNavSource(&test_tower);
	ship2.setNavSource(dynamic_cast<entity_t*>(&flagship));
	//ship2.setNavSource(&flagship);

	ship1.printNavSource();
	ship2.printNavSource();

#endif
	cout << "\n\nSimulation Terminated." << endl;
	return 0;
}