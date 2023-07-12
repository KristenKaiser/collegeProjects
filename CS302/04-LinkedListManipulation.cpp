/*
* Name: Kristen Kaiser, 1008179340, assignment 04
* Description: 
* Input: user input for maipulating queues as requested by program
* Output: display of data in queues as they are altered
*/

#include <iostream>
#include<string>
#include <windows.h> // for null testing in visual studio

using namespace std;
/*
* class_identifier: classs for nlinked list nodes
* constructors:
	node()
* public members:
	next
	character
* static members:
	count
* (variables and function prototypes)
*/
class Node {
public:
	Node *next;
	char character;
	static int count; // for testing
	int nodeNum;
	Node();
};
int Node::count = 0;
/*
* class_identifier: class forlinked list
* constructors: 
	LinkedQueue();
* public members: 
* static members: 
* 
*/

class LinkedQueue {
public:
	Node *head;
	Node *tail;
	LinkedQueue();
};


/*
* class_identifier: class for interacting with main circular queue
* constructors:
	MainQueue(int)
	~MainQueue()
* public members:
	size
	front
	back
* static members:
	none
*/
class MainQueue {
public: 
	int size;
	int front;
	int back;
	LinkedQueue *bigCircle;
	Node *nextInput;
	MainQueue(int);
	~MainQueue();
	void resizeQueue();
	void print();
	void print(int);
	void enqueue(LinkedQueue);
	void enqueue(int, char);
	void enqueueNext(char);
	void dequeue();
	void createCircularQueue(int);
	void createQueue();
};
/*
*function_identifier: node constructor
* parameters : none
* return value :none
*/
Node::Node() {
	next = NULL;
}

/*
*function_identifier: constructor for main queue, creates queue
* parameters : size of queue
* return value :none
*/
MainQueue::MainQueue(int size) {
	front = 0;
	back = 0;
	createCircularQueue(size);
}
/*
*function_identifier: constructor for linked queue, nulls head and tail
* parameters : none
* return value :none
*/
LinkedQueue::LinkedQueue(){
	head = NULL;
	tail = NULL;

}
/*
* function_identifier: create queue to be added to main queue
* parameters: Queue new queue to be added
* return value:none
*/
void MainQueue::createQueue() {
	if (back < size-1)
		++back;
	else
		back = 0;
	if (back == front) {
		cout << "The circular queue is full, doubling size of queue" << endl;
		resizeQueue();
	}
}
/*
* function_identifier: add linked list to next available spot in main queue
* parameters: Queue new queue to be added 
* return value: address of head of new linked list
*/
Node* NewLinkedList();
void MainQueue::enqueue(LinkedQueue NewQueue){
	Node *NewHead = NewLinkedList();
	cout << "adding independent queue to end of queue at index " << back;
	createQueue();
	bigCircle[back].head = NewHead;
	while (NewHead->next != NULL) {
		bigCircle[back].tail = NewHead;
		NewHead = NewHead->next;
	}

}
/*
* function_identifier: add to sub queue at index of main queue
* parameters: int index num of main queue to be added to, char character to be input 
* return value:none
*/
void MainQueue::enqueue(int index, char input){
	nextInput = new Node;
	if (bigCircle[index].head == NULL) 
		bigCircle[index].head = nextInput;
	else 
		bigCircle[index].tail->next = nextInput;
	bigCircle[index].tail = nextInput;
	bigCircle[index].tail->character = input;
	bigCircle[index].tail->next = NULL;
	//cout << nextInput->nodeNum << ", ";
}
/*
* function_identifier: print content of next queue in main array and then delete its content 
* parameters: none
* return value:
*/
void MainQueue::dequeue() {
	cout << "dequeueing index " << front << " :";
	print(front);
	Node* tempNode = bigCircle[front].tail;
	while (tempNode->next != NULL) {
		Node* tempNodeNext = bigCircle[front].tail->next;
		delete tempNode;
		tempNode = NULL;
		tempNode = tempNodeNext;
	}
	bigCircle[front].tail = NULL;
	bigCircle[front].head = NULL;
	cout << endl;
	delete tempNode;
	tempNode = NULL;
	
	++front;

}
/*
* function_identifier: add to the last position of the queue in the last index of main queue
* parameters: char character to be added to queue
* return value:
*/
void MainQueue::enqueueNext(char input) {
	nextInput = new Node;
	//cout << back << endl;
	if (bigCircle[back].head == NULL)
		bigCircle[back].head = nextInput;
	else {
		cout << bigCircle[back].tail->character << " ";
		bigCircle[back].tail->next = nextInput;
	}
	bigCircle[back].tail = nextInput;
	bigCircle[back].tail->character = input;
	bigCircle[back].tail->next = NULL;
	//cout << nextInput->nodeNum << ", ";

}
/*
* function_identifier: double the size of the queue
* parameters:none
* return value:
*/
void MainQueue::resizeQueue() {
	int oldsize = size;
	LinkedQueue *tempArray = new LinkedQueue[oldsize];
	for (int i = 0; i < oldsize; i++) {
		tempArray[i] = bigCircle[i];
	}
	delete[] bigCircle;
	bigCircle = NULL;
	createCircularQueue(oldsize * 2);
	for (int i = 0; i < oldsize; i++) {
		bigCircle[i] = tempArray[i];
	}
	back = oldsize;
	cout << "New Queue size: " << size << endl;
}
/*
* function_identifier: creates intitial circular queue
* parameters: size of queue,
* return value:
*/
void MainQueue::createCircularQueue(int newSize) {
	size = newSize;
	bigCircle = new LinkedQueue[newSize];
}
/*
* function_identifier: print queue index followed by content of queue in index
* parameters:none
* return value:
*/
void MainQueue::print() {
	for (int i = 0; i < size; i++) {
		cout << endl << "Index " << i << ":";
		if (!bigCircle[i].head)
			cout << "EMPTY";
		else
			print(i);
	}
	//cout << endl << "Index " << back << ":";
	//print(back);
	cout << endl;
}
/*
* function_identifier: print only single linked list
* parameters:array location of linked list
* return value:none
*/
void MainQueue::print(int arrayNum) {
	Node *placeHolder;
	placeHolder = bigCircle[arrayNum].head;
	if (placeHolder == NULL)
		return;
	else
		while (placeHolder->next != NULL) {
		cout << placeHolder->character << ", ";
		placeHolder = placeHolder->next;
	}
	cout << placeHolder->character << ", ";
}

/*
* function_identifier: deconstructor for MainQueue, deletes bigCircle
* parameters:none
* return value: None
*/
MainQueue::~MainQueue() {
	delete[] bigCircle;
	bigCircle = NULL;

}

/*
* function_identifier: ask user yes or no question
* parameters:string yes or no question
* return value: bool true==yes, false ==no
*/
bool ynCheck(string question) {
	char choice;
rechoice:
	cout << question << " (y/n): ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
		return true;
	else
		if (choice == 'n' || choice == 'N')
			return false;
	else
	cout << "not a valid input, try again" << endl;
	goto rechoice;
}

/*
* function_identifier: create a linked list
* parameters:none
* return value:none
*/
Node* NewLinkedList() {
	int num;
	bool moreNums = true;
	Node *indyNode = new Node;
	Node *indyHead = indyNode;

	while (moreNums == true) {
		cout << "What number do you want to add to your linked list? ";
		cin >> indyNode->character;
		moreNums = ynCheck("Would you like to add another number?");
		if (moreNums == true) {
			indyNode->next = new Node;
			indyNode = indyNode->next;
		}
	}
	return indyHead;
}

int main()
{
	int inNum;
	char inChar;
	bool repeat;
	cout << "Size of circular Queue: ";
	cin >> inNum;
	MainQueue bigQueue(inNum);
	while (1 > 0) {
		cout << endl << "**commands**" << endl << "Print (P/p)" << endl << "Add char to end(E/e)" << endl << "add char at index(I/i)" << endl << "Dequeue (D/d)" << endl << "quit(Q/q)" << endl;
		cin >> inChar;
		if (inChar == 'q' || inChar == 'Q')
			return 0;
		if (inChar == 'P' || inChar == 'p')
			bigQueue.print();
		else
			if (inChar == 'E' || inChar == 'e') {
				repeat = true;
				while (repeat == true) {
					if (ynCheck("start a new Linked List?") == true)
						bigQueue.createQueue();
					cout << "Character: ";
					cin >> inChar;
					bigQueue.enqueueNext(inChar);
					repeat = ynCheck("Add another char to the end? ");
				}
			}
			else
				if (inChar == 'I' || inChar == 'i') {
					cout << "which array would you like to add to?";
					cin >> inNum;
					repeat = true;
					while (repeat == true) {
						cout << "character: ";
						cin >> inChar;
						bigQueue.enqueue(inNum, inChar);
						repeat = ynCheck("Add another char this index? ");
					}
				}
				else
					if (inChar == 'D' || inChar == 'd')
						bigQueue.dequeue();
	}








}

