/*
* Name: Kristen Kaiser, 1008179340 , Homework 2
* Description: deconstructs txt doc into ordered lists of single word and 2 word phrases and allows user to veiw and save related data 
* Input: txt file of 6 ints via linux input redirection 
* Output: details of how the input .txt file alters the positions of the elevators.
*/


#include <iostream>
#include <cstdlib> //For Absolute value use abs() ie: abs(-5) will return 5

using namespace std;
//Skeleton Program by Jorge Fonseca
//Class Declaration (Design)

class myElevator 
{
private:
	static int count; //keeps track of how many elevators there are
	int id; //elevator id gets increased every time an elevator is added
	int currentFloor; //location of elevator
	int maxFloor; //Maximum Floor of Elevator
	bool inUse; //Whether elevator is in service
public:
	myElevator(int = 1, int = 50); //constructor
	int getElevatorID() const;
	int getElevatorCurrentFloor() const;
	int getCount() const;
	bool canReach(int) const;
	void ToggleElevator(); //Toggle elevator on or off
	void printElevator() const; //Print information on elevator
	void moveElevator(int); //Moves elevator to the requested floor
};
//Class Implementation
int myElevator::count = 0;
myElevator::myElevator(int floor, int max) 
{
	this->id = count++;
	this->currentFloor = floor;
	this->inUse = false;
	this->maxFloor = max;
}
int myElevator::getElevatorID() const 
{
	return id;
}
int myElevator::getElevatorCurrentFloor() const 
{
	return currentFloor;
}
int myElevator::getCount() const 
{
	return myElevator::count;
}
bool myElevator::canReach(int floor) const 
{
	if (maxFloor >= floor) return true;
	else return false;
}
void myElevator::ToggleElevator() 
{
	cout << "Toggled Elevator" << endl;
	if (inUse == true)
		inUse = false;
	else
		inUse = true;
}
void myElevator::printElevator() const 
{
	cout << "Elevator: " << id << " is";
	if (!inUse) cout << " not";
	cout << " in service." << endl;
	cout << "Floor Location: " << currentFloor << endl;
	cout << "Max Floor for Elevator: " << maxFloor << endl;
}
void myElevator::moveElevator(int floor) 
{
	if (floor > maxFloor)
		cout << "Error: Elevator Cannot Reach Floor " << floor << "!" << endl;
	else {
		if (inUse == false)
			cout << "Elevator " << id << " is out of service." << endl;
		else {
			cout << "Elevator Request Recieved for Elevator " << id << "." <<endl;
			cout << "Moving from Floor " << currentFloor << " to Floor " << floor << "." << endl;
			currentFloor = floor;
			cout << "Arrived at Floor " << currentFloor << endl;
		}
	}
}
//Non-Member Functions
int closestElevatorID(myElevator A, myElevator B, int floor) 
{
	if (abs(A.getElevatorCurrentFloor() - floor) <= abs(B.getElevatorCurrentFloor() - floor))
	{
		return A.getElevatorID();
	}
	
	else
	{
		return B.getElevatorID();
	}
} //Returns closest elevators. If equal it just picks the first one
int elevatorDistance(myElevator A, myElevator B) 
{
	//cout << "Distance betweeen Elevator " << A.getElevatorID << " and " << B.getElevatorID << " is " <<
		return abs(A.getElevatorCurrentFloor() - B.getElevatorCurrentFloor()); 
	//<< "floors." << endl;

} //Returns floor distance between both elevators
  // Client Code to test the functionality of the class myElevator
int main() 
{
	// Input: 1, 10, 11, 4, 2, 3
	int a, b, c, d, e, f; // testing code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	cin >> a; cin >> b; cin >> c; cin >> d; cin >> e; cin >> f;
	myElevator A; // declare 1 object of type Elevator
	myElevator B;
	myElevator C(a, b); //a=1,b=10
	C.printElevator();
	C.ToggleElevator();
	C.moveElevator(c);//c=11
	A.ToggleElevator();
	A.moveElevator(d);//d=4
	B.moveElevator(e);//e=2
	B.ToggleElevator();
	A.printElevator();
	B.printElevator();
	cout << "Closest Elevator to Floor " << f << " is Elevator ID: "
		<< closestElevatorID(A, B, f) << endl; //f=3
	cout << "Elevator Distance between Elevator " << A.getElevatorID()
		<< " and " << B.getElevatorID() << " is "
		<< elevatorDistance(A, B) << " Floors." << endl;
	cout << "Total Elevators in Existence: " << A.getCount() << endl;
	return 0;
}

