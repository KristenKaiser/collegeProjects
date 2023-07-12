/*
* Name: Kristen Kaiser, 1008179340 , Homework 9
* Description: uses templates to create arrays of diffrent types of random input
* Input: nothing
* Output: outputs random list of ints, chars, and doubles, then outputs the same lists but organised form smallest to largest
*/


#include <iostream> //cin/cout
#include <stdlib.h> //srand
#include <time.h>   //time
using namespace std;

//Create a global (not part of any class) Template Function getMin that takes two pointers of myType and
//returns a pointer to the smaller of the two. 
 //Use a ternary statement and make this be a single line of code inside the function. 
//The parameters are myType *a and myType *b but return should be a and b since they are pointers.
//Call the function getMin
template <class myType>
myType* getMin(myType *a, myType *b) {
	return (*a <= *b) ? a : b;
}


//Create a global Void Template function to swap two values. Parameters are passed by reference. 
//This should be three lines of code. the template name can be anything, I called it 'something' in my solution.
//Just to understand it can be any name call it something other than myType. Heck, call it JorgeType.
//Call the function Tswap
template <class T>
void tswap(T x, T y) {
	swap(*x, *y);
}


//Create a template class called myList that uses myType as the template variable
//The only function that you are allowed to define inside the class definition is
// 'void setSize(int s)' the rest must be defined OUTSIDE the class definiton!!!
//Here is the class
template <class myType>
class myList {
private:
	myType * arr;
	int size;
public:
	myList(int);
	~myList();
	void print();
	int getSize();
	void setSize(int s) {} //DEFINE THIS FUNCTION INSIDE THE CLASS
		void insertAt(int, myType);
		bool mySort();
	
};

//Define myList Constructor. It takes in one argument int s. This argument is copied to size. size = s;
//Next we dynamically allocate an array of size s of type myType and set it so arr points to it
template <class myType>
myList<myType>::myList (int s) {
	size = s;
	arr = new myType[s];
	
}

//Define Destructor for myList. This should delete arr array and set pointer to null;
template <class myType>
myList<myType>::~myList() {
	delete arr;
	arr = NULL;
}

//Define print member function of myList. This should iterate through the array of size 'size'
//and print out the array. Each element should be separated by a single space. See sample output in PDF
//FYI: This will work for double, int, and anything cout can handle. NOT custom object you'd need operator overloading for that
template <class myType>
void myList<myType>::print() {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

//Define a getSize member function that returns an integer with the size of the array
template <class myType>
int myList<myType>::getSize() {
	return size;
}

//Define a myList memeber method insertAt that will take two parameters: 
//an index of type integer and a value of type myType
//Then use that information to insert the value into the array arr at index given by int index.
template <class myType>
void myList<myType>::insertAt(int index, myType value) {	
	cout << index;// << ' ' << value;
	arr[index] = value;
}

//Define the member method mySort of class myList that will have a double for loop:
//    for(int i=0; i<size;i++)
//        for(int j=0; j<size; j++){
//                  YOUR CODE HERE - LINE 1
//                  YOUR CODE HERE - LINE 2
//    }
//    return true;
// and then TWO lines of code where it says YOUR CODE HERE. 
// These two lines (not 3 or 1,  but 2) must be first:
// a call to getMin
// and then a call to Tswap
// This will take care of sorting your array as long as you pick the right indices
// Hint: the call to getMin should be stored into a pointer ptr declared in the same line
// and then pass that ptr along with an arr index into Tswap. and that's it! NO IF STATEMENTS!
template <class myType>
bool myList<myType>::mySort() {
	for(int i=0; i<size;i++)
        for(int j=0; j<size; j++){
			myType *ptr = getMin(&arr[i], &arr[j]);
			tswap(&arr[j], ptr);
    }
	return true;
}

//Client Code:
int main(int argc, char *argv[]) {
	srand(time(NULL));
	//Each of these represent a single line of code
	cout << "Template Program" << endl;
	//Create an Object of type myList of integers called L1 with size 15
	myList<int> L1(15);

	//Create a pointer to a type myList of integers called ptr
	myList<int> *ptr;

	//make ptr point to L1
	ptr = &L1;

	//create another pointer of type myList of chars
	myList<char> *ptr2;

	//Dynamically Allocate an object of myList size 8 of chars and have ptr2 point to it 
	ptr2 = new myList<char>(8);

	//Note, try the above but instead try to make it point to doubles or int or anything else. 
	//It will error. It's good to see the error so you know it incase you ever run into it.
	//-Comment it out after you test it.
	//ptr2 = new myList<int>(8);

	//In a single line create ptr3 and dynamically allocate a myList size 4 of type double
	myList<double> *ptr3 = new myList<double>(4);

	//Uncomment the following segnment of code to insert a couple of values to each list
	//It should work. If it doesn't then you messed up variable names. Fix it. Don't change my code.
	
	for(int i=0; i<L1.getSize();i++){
	ptr->insertAt(i, rand()%200 + 1);
	if(i<4)
	ptr3->insertAt(i, static_cast<double>(rand()%200)/17 + 1.01 );
	if(i<8)
	ptr2->insertAt(i, 'A'+rand()%24);
	}
	
	cout << "Pre Sorted Lists:" << endl;

	//Print out L1 by calling the print function
	L1.print();

	//Print out ptr by calling the print function
	ptr->print();


	//Print out ptr2 by calling the print function
	ptr2->print();


	//Print out ptr3 by calling the print function
	ptr3->print();//printing blanks?


	//Now call mysort for L1
	L1.mySort();


	//Call mySort in ptr  (should do nothing since it's sorted, but whatever)
	ptr->mySort();

	//Call mySort in ptr2
	ptr2->mySort();

	//Call mySort in ptr3
	ptr3->mySort();

	cout << "\nSorted Lists:" << endl;

	//Next, Print out L1 again by calling the print function
	L1.print();

	//Print out ptr again by calling the print function
	ptr->print();

	//Print out ptr2 again by calling the print function
	ptr2->print();

	//Print out ptr3 again by calling the print function
	ptr3->print();

	//Did it work? Did it sort each list? If so good job, gg ez, if not then I guess it's time to debug!
	//Go ahead and be a good citizen and de-allocate your memory and set pointers to null. 
	//Run valgrint ./a.out to test for memory leaks :)
	//Start by de-allocating ptr2


	//Next do ptr3


	//Just for fun let's call the destructor explicitly.
	//This happens automatically at the end (when we leave the scope), but you cal also call it 
	//explicity by doing L1.~myList() It's good to know this so you can break your code by 
	//accidentally calling it before you are done using the object :D  Try it!
	L1.~myList();

	//If you tried to call print you would seg fault since you've lost access to the memory. 
	//It may not seg fault but you definitely shouldn't be accessing it! Uncomment to try it
	//L1.print(); //Morale of the story is don't explicitly call the destructor unless you're a pro :)

	//Set ptr, ptr2, and ptr3 to null. Notice that if you tried to do ptr=ptr2=ptr3=NULL you get an error!
	//Yeah it's dumb, but that's C++ for ya, so I guess you have to write it in 3 lines of code :(
	ptr = NULL;
	ptr2 = NULL;
	ptr3 = NULL;



	return 0;
}
