/*
* Name: Kristen Kaiser, 1008179340 , Homework 12
* Description: takes in 2 lists, sorts, and splits at set point
* Input: txt file line1: length of 2 lists // line2: first list of ints // line3: second list of ints // line 4: break point for list 1 // line 5: break point for list 2
* Output: both sorted lists then after the list is split, 4 sorted lists.
*/


#include<iostream>
#include<cstddef>

using namespace std;
typedef int ItemType;
struct NodeType;
typedef NodeType *NodePtr;

struct NodeType {
	ItemType component;
	NodePtr link;
};
class List {
public:
	List();
	void Insert(ItemType item);
	void Delete(ItemType item);
	void ResetList();
	ItemType GetNextItem();
	int GetLength() const;
	bool IsEmpty() const;
	bool IsFull() const;
	bool IsThere(ItemType item) const;
	bool HasNext() const;
	
	/** function_identifier: split linked list by creating a new list for linked lists after the break and deleting the lists used in the new linked list
	parameters: itemtype int to act as breakpoint
	return value: list address to new list holding second half of original list*/
	List split_ver1(ItemType item){
		List newList;
		NodePtr temp;
		NodePtr currPtr = dataPtr;
		while (currPtr->component != item)//move to break point
			currPtr = currPtr->link;
		while(currPtr != NULL){//fill new list remove remaing list from current list
			newList.Insert(currPtr->component);
			temp = currPtr->link;
			Delete(currPtr->component);
			currPtr = temp;
		}
		return newList;
	}
	
	/** function_identifier: split linked list by moving start and endpoints 
	parameters: itemtype int to act as breakpoint
	return value: list address to new list holding second half of original list*/
	List split_ver2(ItemType item){
		List newList;
		NodePtr temp;
		int count = 0;
		NodePtr currPtr = dataPtr;
		while((currPtr->link)->component != item){//Find end of new list 
			count++;
			currPtr = currPtr->link;
		}
	//update end point of original list and the start of the new list
		count++;
		newList.length = length - count;
		length = count;
		lastPtr = currPtr;
		newList.dataPtr =currPtr->link;
		(currPtr->link) = NULL; //set new end of original list
		return  newList;
	}


	void PrintForward() const {
		NodePtr currPtr = dataPtr;
		while (currPtr != NULL) {
			cout << currPtr->component << ",";
			currPtr = currPtr->link;
		}
		cout << endl;
	}
private:
	NodeType * dataPtr;
	int length;
	NodeType *currentPos;
	NodeType *lastPtr;
};
List::List() {
	dataPtr = NULL;
	currentPos = dataPtr;
	length = 0;
	lastPtr = NULL;
}
void List::Insert(ItemType item) {

	NodePtr currPtr, prevPtr, newNodePtr;
	newNodePtr = new NodeType;
	newNodePtr->component = item;
	if (dataPtr == NULL) { // Empty list?
		dataPtr = newNodePtr;
		lastPtr = newNodePtr;
	}
	else { //Find previous insertion point
		currPtr = dataPtr;
		prevPtr = NULL;
		while (currPtr != NULL && currPtr->component < item) {
			prevPtr = currPtr;
			currPtr = currPtr->link;
		}
		// Insert new node
		newNodePtr->link = currPtr;
		if (prevPtr == NULL) // Insert as first?
			dataPtr = newNodePtr;
		else prevPtr->link = newNodePtr;
		if (currPtr == NULL) // Insert as last?
			lastPtr = newNodePtr;
	}
	length++;
}
void List::Delete(ItemType item) {
	NodePtr prevPtr = NULL;
	NodePtr currPtr = dataPtr;
	while (currPtr != NULL && currPtr->component != item) {
		prevPtr = currPtr;
		currPtr = currPtr->link;
	}
	if (currPtr != NULL) {
		if (currPtr == dataPtr) dataPtr = currPtr->link;
		else prevPtr->link = currPtr->link;
		if (currPtr == lastPtr) lastPtr = prevPtr;
		delete currPtr;
		length;
	}
}
void List::ResetList() {
	currentPos = dataPtr;
}
ItemType List::GetNextItem() {
	ItemType item;
	item = currentPos->component;
	currentPos = currentPos->link;
	return item;
}
int List::GetLength() const {
	return length;
}
bool List::IsEmpty() const {
	return (dataPtr == NULL);
}
bool List::HasNext() const {
	return (currentPos != NULL);
}
bool List::IsFull() const {
	return false;
}
bool List::IsThere(ItemType item) const {
	NodePtr currPtr = dataPtr;
	while (currPtr != NULL && currPtr->component != item)
		currPtr = currPtr->link;
	if (currPtr != NULL) return true;
	else return false;
}
int main() {
	List L1, L2, L3, L4;
	int n, x;
	cin >> n;
	//read first list
	for (int i = 0; i<n; i++) {
		cin >> x;
		L1.Insert(x);
	}
	cout <<endl; // testing code
	//read second list
	for (int i = 0; i<n; i++) {
		cin >> x;
		L2.Insert(x);
	}
	cout << "Given List L1: " << endl;
	L1.PrintForward();
	cout << endl;
	cout << "Given List L2: " << endl;
	L2.PrintForward();
	cout << endl;
	
	cin >> x; // Read item to split the first list
	cout << "Split Data: " << x << endl;

	L3 = L1.split_ver1(x);
	cout << "After splitting L1, first part is: " << endl;
	L1.PrintForward();
	cout << "After splitting L1, second part is: " << endl;
	L3.PrintForward();
	cin >> x; // Read item to split the second list
	cout << "Split Data: " << x << endl;
	L4 = L2.split_ver2(x);
	cout << "After splitting L2, first part is: " << endl;
	L2.PrintForward();
	cout << "After splitting L2, second part is: " << endl;
	L4.PrintForward();
	
	return 0;
}