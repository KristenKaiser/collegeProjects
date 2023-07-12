// Homework4.cpp : Defines the entry point for the console application.
//




//Skeleton Code by: Jorge Fonseca
//Assignment Covers Creating an Engine Class, a Person Class, and an Airplane class that has engine and person as composition.
//Next the engine is upgraded in a derived class which is then added to a new Airplane class with added features.
//Will optionally log output of commands done on engines.

#include<iostream>
#include<fstream> //for  ifstream
#include<cstdlib> //For rand()
#include<string>
#include <time.h>  
using namespace std;

//Class Design
class engineType {

	//string model();
public:
	engineType(double t = 0, string m = "Propeller");
	double getThrust() const;
	void idle();
	void turnOff();
	void turnOn();
	void accelerate(const int&);
	void printModel() const;
protected:
	void printMsg(int) const;
	double thrust;
	string model;
	
};

//Class Implementation
engineType::engineType(double t, string m) {
	thrust = t; //uncomment once you created these memeber variables
	model = m;  //uncomment once you created these memeber variables
}

double engineType::getThrust() const {
	return thrust;
}

void engineType::idle()  {
	printMsg(4);
	thrust = 10000;
}

void engineType::turnOn() {
	if (thrust == 0) {
		printMsg(6);
		thrust = 10000;
	}
	else
		printMsg(1);
}

void engineType::accelerate(const int& accSpeed) {
	if (accSpeed >= 0) {
		thrust = thrust + accSpeed;
		printMsg(-thrust);
	}
}

void engineType::printModel() const {
	cout << model;
}



void engineType::turnOff() { //Use this function as an example of how to do these.
if(thrust == 0){ //It was off already
printMsg(3);
}
else{
printMsg(2);
thrust = 0;
}
}



void engineType::printMsg(int cmd) const { //You must use these messages as part of your class implementation
	switch (cmd) {
	case 1:  cout << "Warning: Engine is already On" << endl;
		break;
	case 2:  cout << "VRRR PFPT PTFP HKSSSS Turned Engine Off" << endl;
		break;
	case 3:  cout << "Warning: Engine is Off" << endl;
		break;
	case 4:  cout << "Engine RPM Changed to 10,000" << endl;
		break;
	case 5:  cout << "Warning: Cannot Decelerate This Engine" << endl;
		break;
	case 6:  cout << "P P P VROOM VROOM RRRRRRR! Engine is Turning On!" << endl;
		break;
	default: cout << "Engine RPM Changed to " << -cmd << endl;
		break;
	}
}

//Enum Declarations
enum FirstNames {
	Jorge,
	Jason,
	Jane,
	James,
	Wendy,
	Ben,
	Tim,
	Sophie,
	Andrew,
	Denzel,
	Vicky,
	Dolly,
	Jyn,
	maxFirstName
};

enum LastNames {
	Fonseca, 
	Doe, 
	Smith, 
	Jackson, 
	Pedersen, 
	Anderson, 
	Bond, 
	Washington,
	Skywalker, 
	Bourne, 
	Jones, 
	Solo, 
	Erso,
	maxLastName
};

//Non-Member Function Prototypes for Enums
string enum2FirstNameToString(unsigned int);
string enum2LastNameToString(unsigned int);

//Your Code Here for the enum2LastNameToString function prototype

//Class Design
struct personType {
	string firstName;
	string lastName;
public:
	personType();
	personType(string first, string last);
	string getFirstName() const;
	string getLastName() const;
	void changeName(const string& newFirst , const string& newLast);
};

//Class Implementation
personType::personType() {
	firstName = enum2FirstNameToString(rand() % maxFirstName); //Uncomment once you have created the firstName member variable
	lastName = enum2LastNameToString(rand() % maxLastName);
}

//Your Code Here for the rest of the member function definitions
personType::personType(string first, string last) {
	firstName = first;
	lastName = last;
}

string personType::getFirstName() const {
	return firstName;
}

string personType::getLastName() const{
	return lastName;
}

void personType::changeName(const string& newFirst, const string& newLast){
	firstName = newFirst;
	lastName = newLast;
}

//Composition
class airplaneType {
public:
	engineType propeller;
	personType pilot;
	personType passengers[5];
	airplaneType() : capacity(5), model("Propeller") {}; //initalizes capacity to 5 and model to "propeller"
	string getModel() const;
	void setModel(string str);
	int getPlaneCapacity();
	void rollIt() { cout << "omg we just did a barrel roll!" << endl; }
private:
	unsigned int capacity;
	string model;
};

string airplaneType::getModel() const {
	return model;
}
void airplaneType::setModel(string str) {
	model = str;
}
int airplaneType::getPlaneCapacity() {
	return capacity;
}

//Inheritance
//Class Design

class upgradedEngineType : public engineType{
private:
	const int maxThrust = 25000;
	ofstream fout;
public:
	upgradedEngineType(string filname = "engineLog.txt", double t = 0, string m = "Jet Engine");
	void accelerate(const int&);
	void decelerate(int);
	void printModel() const;
	~upgradedEngineType();
	string namo; 
};



//constructor
upgradedEngineType::upgradedEngineType(string filename, double t, string m)
{
	fout.open(filename.c_str());
	model = m;
	thrust = t;
	fout << "Engine Log File Started" << endl;
}

//deconstructor
upgradedEngineType::~upgradedEngineType(){
	fout << "Engine Log File Compleated" << endl;
	fout.close();
}


void upgradedEngineType::accelerate(const int& accSpeed) {
	if (accSpeed >= 0)
		if ((thrust + accSpeed) < maxThrust)
		{
			fout << "Engine Accelerated From " << thrust << " RPM to ";
			thrust = thrust + accSpeed;
			fout << thrust << "RPM." << endl;
			printMsg(-thrust);
		}
		else {
			cout << "Warning: Cannot Accererate to " << thrust + accSpeed << " RPM as it would go over the max limit of " << maxThrust << "!" << endl;
		}

}
void upgradedEngineType::decelerate(int accSpeed) {
	if (accSpeed >= 0)
		if ((thrust - accSpeed) > 0)
		{
			fout << "Engine Decelerated From " << thrust << " RPM to ";
			thrust = thrust - accSpeed;
			fout << thrust << "RPM." << endl;
			printMsg(-thrust);
		}
		else
			printMsg(5);
}
void upgradedEngineType::printModel() const {
	cout << "Engine Model: " << model;
}



//Class Implementation
//Your Code Here for upgradedEngineType that inherits from engineType (implementation)


class ModernAirplaneType {
private:
	unsigned int capacity;
	string model;
public:
	personType pilot;
	personType copilot;
	personType passengers[120];
	upgradedEngineType leftTurbine{ "leftEngineLog.txt" };
	upgradedEngineType rightTurbine{ "RightEngineLog.txt" };
	ModernAirplaneType();
	string getModel() const;
	void setModel(string str);
	int getPlaneCapacity() const;
};



ModernAirplaneType::ModernAirplaneType() {
	capacity = 120;
	model = "Jet Engine";
	class upgradedEngineType leftTurbine("leftEngineLog.txt", capacity, model);
	class upgradedEngineType RightTurbine("RightEngineLog.txt", capacity, model);
}
string ModernAirplaneType::getModel() const {
	return model;
}
void ModernAirplaneType::setModel(string str) {
	model = str;
}
int ModernAirplaneType::getPlaneCapacity() const {
	return capacity;
}

//Non Member Function;

//Enum Functions
string enum2FirstNameToString(unsigned int f) {
	switch (f) {
	case Jorge:  return "Jorge";
	case Jason:  return "Jason";
	case Jane:  return "Jane";
	case James:  return "James";
	case Wendy:  return "Wendy";
	case Ben:  return "Ben";
	case Tim:  return "Tim";
	case Sophie:  return "Sophie";
	case Andrew:  return "Andrew";
	case Denzel:  return "Denzel";
	case Vicky:  return "Vicky";
	case Dolly:  return "Dolly";
	case Jyn:  return "Jyn";
	default:  return "None";
	}
}

//Enum Functions
string enum2LastNameToString(unsigned int f) {
	switch (f) {
	case Fonseca: return "Fonseca";
	case Doe: return "Doe";
	case Smith: return "Smith";
	case Jackson: return "Jackson";
	case Pedersen: return "Pedersen";
	case Anderson: return "Anderson";
	case Bond: return "Bond";
	case Washington: return "Washington";
	case Skywalker: return "Skywalker";
	case Bourne: return "Bourne";
	case Jones: return "Jones";
	case Solo: return "Solo";
	case Erso: return "Eros";
	default:  return "None";
	}
}

//Other Non-member Functions
void printPassengers(personType person[], int capacty) {
	for (int i = 0; i < capacty; i++) {
		cout << i + 1 << " Passenger " << person[i].firstName << " " << person[i].lastName << endl;
	}
	
}

//Client Code
int main(int argc, char *argv[]) {
	cout << "Assignment 3: Welcome to CS202 Airways.\n"
		<< "Now Offering Non-stop flights to All-nighters coding C++\n"
		<< "Book your Flight Today! :D" << endl;
	srand(time(NULL)); //Seed Rand!

					   //Let's create an airplane!
	airplaneType Cessna;

	//Uncomment line by piece as you write the code, so you can test it

	//Next, let's print out the passengers in our plane!
	printPassengers(Cessna.passengers, Cessna.getPlaneCapacity());
	//Next, let's make ourselves the pilot CUZ I AM TEH CAPTEIN NAOW!/*
	personType LeCapitaine("Capt.", "Whip");
	Cessna.pilot = LeCapitaine;
	//Now let's print the Captain's greetings
	cout << "Greetings from your pilot. My name is " << Cessna.pilot.getFirstName() << " "
	<< Cessna.pilot.getLastName() << " and WE'RE GOING TO ROLL IT" << endl;
	//Captain Whip wants you to get this pupper in the air so turn the engines on.
	Cessna.propeller.turnOn();
	cout << "Current Thrust " << Cessna.propeller.getThrust() << endl;
	//When this baby hits 88...
	Cessna.propeller.accelerate(15000); //Accelerate the engine to take off.
	//wooho now we are flying. Let's push this baby to the limit!
	Cessna.propeller.accelerate(40000); //Accelerate the engine to take off.
	cout << "Warning: Engine Overheating. inb4 explosion!" << endl;
	cout <<"Quick lower the power on the engine before it blows!" << endl;
	Cessna.propeller.idle(); //Quick set the engine to idle before it blows!
	Cessna.propeller.turnOff();
	cout << "Omg the engine just cut off! Restart!" << endl;
	cout << "Engine: nah bruh im ded" << endl;
	cout << "Okay when I say go we gonna roll it!" << endl;
	Cessna.rollIt(); //roll it!
	cout << "Plane landed safely and everyone lived! Yay" << endl;

	cout << "Meanwhile at headquarters. In response to this incident they decide\n"
	<< "to create a new plane that has two engines and a larger capacity\n"
	<< "because safety, also can carry more people and can decelerate engines\n"
	<< "to a specified value instead of having to go all the way to idle.\n";

	//Create a new object of the ModernAirplaneType
	ModernAirplaneType B737MAX; //lol
	//Wow this guy is sweet! Let's fill 'er up with passengers!
	cout << "Our Passengers:" << endl;
	printPassengers(B737MAX.passengers, B737MAX.getPlaneCapacity());

	//Captain Whip is a Hero for saving that plane. Let's make him pilot.
	B737MAX.pilot = LeCapitaine;


	//We also need a co-pilot. The company assigned one. Print out both Pilot's names.
	cout << "Pilot  : " << B737MAX.pilot.getFirstName() << " " << B737MAX.pilot.getLastName()
	<< "\nCopilot: " << B737MAX.copilot.getFirstName() << " " << B737MAX.copilot.getLastName()
	<< endl;

	
	B737MAX.ModernAirplaneType::leftTurbine.turnOn();
	B737MAX.ModernAirplaneType::rightTurbine.turnOn();
	B737MAX.ModernAirplaneType::leftTurbine.idle();
	B737MAX.ModernAirplaneType::rightTurbine.idle();
	B737MAX.ModernAirplaneType::leftTurbine.accelerate(5000);
	B737MAX.ModernAirplaneType::rightTurbine.accelerate(10000);
	B737MAX.ModernAirplaneType::rightTurbine.decelerate(4000);
	B737MAX.ModernAirplaneType::leftTurbine.accelerate(15000);
	B737MAX.ModernAirplaneType::leftTurbine.idle();
	B737MAX.ModernAirplaneType::rightTurbine.idle();
	B737MAX.ModernAirplaneType::leftTurbine.turnOff();
	B737MAX.ModernAirplaneType::rightTurbine.turnOff();
	

	cout << "Thanks for Flying C202 Airways!" << endl;
	return 0;
}