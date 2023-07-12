/*
* Name: Kristen Kaiser, 1008179340, Assignment# 13
* Description: creates nested linked lists of nodes at runtime and displays its architecture .
* Input: line 1: possible levels in order to highest -> lowest. Line 2: nodes visited in the order that they are visited 
* Output: status updates of architecture being built, all levels printed by level, all levels in Depth First Search manner, updates as dream worls and reality is deleated 
*/

#include<iostream>
#include<sstream>
#include<string>

using namespace std;
class LinkedList;

/*
* class_identifier: holds ordered array of possible dream levels
* constructors: level
* public functions: findlevel (string search)
* static members: none
*/
class Levels {
public:
	string* name;
	int size;
	Levels(int s = 0);
	~Levels();
	int findLevel(string search);
	friend ostream& operator << (ostream& os, const Levels& lvl);
	friend istream& operator >> (istream& is, Levels& lvl);
};

/*
* class_identifier: holds individual dream nodes
* constructors: node
* public functions: 
	int getid() const;
* static members: count
*/
class Node {
	int id;
	static int count;
public:
	string * data;
	LinkedList* DeeperDream = NULL;
	Node* next = NULL;
	Node* prev = NULL;
	Node() {
		data = new string;
		id = count++;
	}
	~Node();
	int getid() const;
	friend ostream& operator << (ostream& os, const Node& node);
	friend ostream& operator << (ostream& os, const Node* node);
	friend istream& operator >> (istream& is, Node& node);
	friend istream& operator >> (istream& is, Node* node);
	
};
/*
* class_identifier: class to hold entire level of dream
* constructors:  LinkedList()
* public functions: 
	int getid() const;
	void fwdPrintList();
	void bkwdPrintList();
	void insertEndNode(Node* n);
	void insertDreamNode(Node* n, Levels& lvl);
* static members:count
*/
int Node::count = 0;
class LinkedList {
	int id;
	static int count;
public:
	Node* head = NULL;
	Node* tail = NULL;
	LinkedList() {
		id = count++;
		head = NULL; }
	~LinkedList();
	int getid() const;
	friend ostream& operator << (ostream& os, const LinkedList& node);
	friend ostream& operator << (ostream& os, const LinkedList* node);
	void fwdPrintList();
	void bkwdPrintList();
	void insertEndNode(Node* n);
	void insertDreamNode(Node* n, Levels& lvl);
	LinkedList* gotoLevel(int lvl);
};

/*
* class_identifier: hold everything including linkedlist dream layers and dream nodes 
* constructors: World()
* public functions: 
	static int DFStraversal
	int givehimthekick()
	void printbylevel()
* static members: none
*/
int LinkedList::count = 0;
class World {
public:
	LinkedList * reality = NULL;
	Levels levels;
	World() {
		reality = new LinkedList;
		cout << "New Linked List" << endl;
	}
	~World();
	static int DFStraversal(ostream& os, Node* node); 
	int givehimthekick();// deallocate dream layers ( not reality)
	void printbylevel();// calls fwdPrintList
	friend istream& operator >> (istream& is, World& world);
	friend istream& operator >> (istream& is, World* world);
	friend ostream& operator << (ostream& os, const World& world);
};
// functions for Levels
/*
* function_identifier: deconstructor; deletes name dynamic var out of null 
* parameters: none
* return value: none
*/
Levels::~Levels() {
	delete[] name;
	name = NULL;
}
/*
* function_identifier:  constructor; does nothing but can be uncommented to set levels in array to be consecutive numbers
* parameters:  int (number of test levels) 
* return value: none
*/
Levels::Levels(int s) {
	/*if (s > 0)
		name = new string[s];
	for (int i = 0; i < s; i++)
		name[i] = i;*/
}
/*
* function_identifier: finds number of levels deep level appears
* parameters: string (name of level program is searching for) 
* return value:  int( number of layers deep found level is)
*/
int Levels::findLevel(string search) {
	for (int i = 0; i < size; i++)
		if (search == name[i]) {
			return i;
}
	cout << "level search unsucessful" << endl;
	return -1;
}
/*
* function_identifier: prints out "Level #: NAME? where # is the level number and NAME is the name of the level from the file
* parameters: ostream& , Levels& (dream level) 
* return value: ostream& 
*/
ostream& operator << (ostream& os, const Levels& lvl) {
	for (int i = 0; i < lvl.size ; i++)
	//cout << "Level " << i << ": "<< lvl.name[i] << endl;
	return os;  
}

/*
* function_identifier: reads first line. seperates words and puts into "name" array
* parameters: istream& Levels& (dream level)
* return value: istream&
*/
istream& operator >> (istream& is, Levels& lvl) {
	stringstream splitLocate;
	string firstLine;
	string temp;
	int NumWords = 0;
	getline(is, firstLine);
	splitLocate << firstLine;
	//counts words in first line
	while (splitLocate >> temp) 
		NumWords++;
	lvl.size = NumWords;
	lvl.name = new string[NumWords];
	splitLocate.clear();
	splitLocate << firstLine;
	//adds locations from first line to array 
	for (int i = 0; i < NumWords; i++)
		splitLocate >> lvl.name[i];
	cout << NumWords << " Levels Created." << endl;
return is; }

/*
* function_identifier: find requested level and return pointer to it 
* parameters: int of desired level
* return value: "head" of *linkedList* with id == passed int "lvl"
*/

LinkedList* LinkedList::gotoLevel(int lvl) {
	Node * goHere = head ;
	int currentLevel = getid();

	cout << "Searching  LVL: " << lvl + 1 << endl;
	while (currentLevel < lvl && (goHere->next != NULL || goHere->DeeperDream != NULL)) { // continue while current level < desired level AND there is either a "next" node or a "dreamDeeper" node
		if(goHere->DeeperDream != NULL){
			cout << "We are going deeper: " << currentLevel << ' ' << lvl << endl;
			currentLevel++;
			if (currentLevel == lvl) {
				cout << "FOUND?: " << *goHere->DeeperDream->head->data << endl;
				return goHere->DeeperDream;
			}
			goHere = goHere->DeeperDream->head;
		}
		goHere = goHere->next;
	}
	if (lvl > 1 + currentLevel){
		cout << "ERROR: Dream Level Was Not Found. Go to sleep so that we can go deeper!" << currentLevel << ' ' << lvl << endl;
		cout << "Error: We Tried to Enter A Deeper Dream Directly!" << endl;
		cout << "Paradox: Terminating Program." << endl;
		exit(1);
	}
	else {
		cout << "New Linked List" << endl;
		cout << "We need to go deeper: "<< currentLevel << ' ' << lvl << endl;
		goHere->DeeperDream = new LinkedList;
		return goHere->DeeperDream;
	}
}
/*
* function_identifier: give access to private id member
* parameters: none
* return value: id of linked list
*/
int LinkedList::getid() const {
	return id;
}
/*
* function_identifier: deconstructor, sets nodes members to NULL and deletes dynamic "data" 
* parameters: none
* return value: none
*/
Node::~Node() {
	delete data;
	data = NULL;
	DeeperDream = NULL;
	next = NULL;
	prev = NULL;
}
/*
* function_identifier: give access to private id member
* parameters: none
* return value: id of node
*/
int Node::getid() const {
	return id;
}
/*
* function_identifier: overload to nicely print nodes id and contents 
* parameters: ostream& ,  node (dream node) 
* return value: Node #: ? where # is the id and D is the contents of the data string.
*/
ostream& operator << (ostream& os, const Node& node) {
		cout << "Level " << node.id << ": " << node.data << endl;
	return os;
}
/*
* function_identifier: overload to nicely print nodes id and contents 
* parameters: ostream& ,  node (dream node) 
* return value: Node #: ? where # is the id and D is the contents of the data string.
*/
ostream& operator << (ostream& os, const Node* node) {
		cout << "Level " << node->id << ": " << *node->data << endl;
	return os;
}
/*
* function_identifier: reads into the data string of node
* parameters: none
* return value: none
*/
istream& operator >> (istream& is, Node& node) { 
	cin >> *node.data;
return is; 
}
/*
* function_identifier: reads into the data string of node
* parameters: none
* return value: none
*/
istream& operator >> (istream& is, Node* node) {
	cin >> *node->data;
	return is;
}
// functions for LinkedList
/*
* function_identifier: inserts new node into linked list and sets previous nodes "next" member
* parameters: new node to be inserted
* return value: none
*/
void LinkedList::insertEndNode(Node* n) {
	//cout <<  *n->data << endl;
	
	if (head == NULL)
		head = n;
	else {
		n->prev = tail;
		n->prev->next = n;
	}
	tail = n;
}
/*
* function_identifier: print a single dream layer's nodes
* parameters: none
* return value: none
*/
void LinkedList::fwdPrintList() {
	Node* youAreHere = head;

	cout <<endl << "Forward Print List, " << *head->data << " Level :" << endl;
	while (youAreHere != NULL) {
		cout << "Node " << youAreHere->getid() << ": " << *youAreHere->data << ", ";
		youAreHere = youAreHere->next;
	}

	cout <<". " <<  endl;
}

/*
* function_identifier: deconstructor, delets nodes forwards
* parameters: none
* return value: none
*/
LinkedList::~LinkedList() {
	
	while (tail != NULL){
			tail = tail->prev;
		if(tail != NULL){
			delete tail->next;
			tail->next = NULL;
		}
		if(tail->prev == NULL){
			delete tail->DeeperDream;
			delete tail;
			tail = NULL;
		}
	}	
	

	
} 
/*
* function_identifier: print a single dream layer's nodes backwards
* parameters: none
* return value: none
*/
void LinkedList::bkwdPrintList() {
	Node* youAreHere = tail;

	cout << endl << "Backwards Print List, " << *head->data << " Level :" << endl;
	while (youAreHere != NULL) {
		cout << "Node " << youAreHere->getid() << ": " << *youAreHere->data << ", ";
		youAreHere = youAreHere->prev;
	}

	cout << ". " << endl;
}
/*
* function_identifier: inserts a dream node to the appropriate dream level
* parameters: Node*(node to insert) Levels& (list of all levels) 
* return value: none
*/
void LinkedList::insertDreamNode(Node* n, Levels& lvl) {
	int currentLvl = 0;
	for (int i = 0; i < id; i++) {
		
		if (head == NULL) { // for head of list
			head = n;
		}
	}
	if (head != n ){
		n->prev = tail;
		n->prev->next = n;
	}
	tail = n;
	cout << "Inserting to LVL " << lvl.findLevel(*n->data) + 1 << ": " << *n->data <<endl;
}
/*
* function_identifier: overload to nicely print nodes id
* parameters: ostream& , const LinkedList& (dream node) 
* return value: ostream&
*/
ostream& operator << (ostream& os, const LinkedList& node) {
	cout << "LinkedList: " << node.id;

	return os;
}
/*
* function_identifier: overload to nicely print nodes id
* parameters: ostream& , const LinkedList& (dream node) 
* return value: ostream&
*/
ostream& operator << (ostream& os, const LinkedList* node) {
	cout << "LinkedList: " << node->id;
	return os;
}
//functions for World
/*
* function_identifier: print every node
* parameters: ostream& , Node* (starting point node)
* return value: output every node in Depth First Search manner, return count of all nodes
*/
int World::DFStraversal(ostream& os, Node* node) {
	static int levelCount = 0;
	cout << levelCount++ << *node->data << ", ";
	if (node->DeeperDream != NULL) {
		//cout << levelCount++ << *node->data << ", ";
		cout << "ENTERING DEEPER LAYER, ";
		(DFStraversal(os, node->DeeperDream->head));
	}
	if (node->next != NULL) {
		//cout << levelCount++ << *node->data << ", ";
		(DFStraversal(os, node->next));
	}
	 if (node->next == NULL && node->DeeperDream == NULL) {
		if (*node->data != "REALITY")
			cout << "EXITING A LAYER, ";
		else {
			cout << endl << "Node Visited " << levelCount;
			return levelCount;
		}
	}
}
/*
* function_identifier: deconstructor, delete reality
* parameters:  none
* return value: none
*/

World::~World() {
	reality->~LinkedList();
	delete reality;
	reality = NULL;
}
/*
* function_identifier: reads line 2 and inserts into linked lists outputs if it is in reality or dream list
* parameters: istream& , World& (holds everything)
* return value: istream&
*/
istream& operator >> (istream& is, World& world) { 
	stringstream splitLocate;
	string secondLine;
	LinkedList * dreamLevel = world.reality;
	Node* nowNode;
	
	for(int i = 0; i < 2; i ++) {
	getline(is, secondLine);
	splitLocate << secondLine;
	nowNode = new Node;
	cout << "New Node: "; 
	while (splitLocate >> *nowNode->data) {
		if (*nowNode->data == "REALITY") {
			cout << "REALITY" << endl;
			world.reality->insertEndNode(nowNode);
		}
		else {
			cout << "DREAM" << endl;
			//cout << "Searching  LVL: " << world->levels.findLevel(*nowNode->data) + 1 << endl;
			dreamLevel = world.reality->gotoLevel(world.levels.findLevel(*nowNode->data));
			dreamLevel->insertDreamNode(nowNode, world.levels);
		}
		nowNode = new Node;
		cout << "New Node: " ;  
	}

	splitLocate.clear();
	delete nowNode;
	nowNode = NULL;
	}
	return is;
}

/*
* function_identifier: reads line 2 and inserts into linked lists outputs if it is in reality or dream list
* parameters: istream& , World& (holds everything)
* return value: istream&
*/
istream& operator >> (istream& is, World* world) {
	stringstream splitLocate;
	string secondLine;
	LinkedList * dreamLevel = world->reality;
	Node* nowNode;

for(int i = 0; i < 2; i ++) {
	getline(is, secondLine);
	splitLocate << secondLine;
	nowNode = new Node;
	cout << "New Node: ";// << nowNode << " ";
	while (splitLocate >> *nowNode->data) {
		if (*nowNode->data == "REALITY") {
			cout << "REALITY" << endl;
			world->reality->insertEndNode(nowNode);
		}
		else {
			cout << "DREAM" << endl;
			//cout << "Searching  LVL: " << world->levels.findLevel(*nowNode->data) + 1 << endl;
			dreamLevel = world->reality->gotoLevel(world->levels.findLevel(*nowNode->data));
			dreamLevel->insertDreamNode(nowNode, world->levels);
		}
		nowNode = new Node;
		cout << "New Node: ";// << nowNode;  
	}
	splitLocate.clear();
	delete nowNode;
	nowNode = NULL;
}
return is;
}
/*
* function_identifier: prints all nodes of a single level 
* parameters: none
* return value: none
*/
void World::printbylevel() {
	LinkedList* currentLevel = reality;
	Node* searchingNode = reality->head;
	cout << endl << "Printing World by Level:" << endl;
	for (int i = 0; i < levels.size-1; i++) {
		currentLevel->fwdPrintList();
		while (searchingNode->DeeperDream == NULL) {
			searchingNode = searchingNode->next;
		}
		currentLevel = searchingNode->DeeperDream;
		searchingNode = searchingNode->DeeperDream->head;
	}
	currentLevel->fwdPrintList();
}
/*
* function_identifier: print all nodes in the world and list of all levels
* parameters: ostream& , const (holds everything)
* return value: ostream&
*/
ostream& operator << (ostream& os, const World& world) {
	cout << endl << "The World As We Know It : " << endl;
	for (int i = 0; i < world.levels.size; i++) {
		cout << "Level " << i + 1 << ": " << world.levels.name[i] << endl;
	}
	cout << endl << "Dream Architecture : ";
	world.DFStraversal(os, world.reality->head);
	return os;
};
/*
* function_identifier: deletes dream layers
* parameters: none
* return value: int
*/
int World::givehimthekick() { 
	LinkedList** listOfLists = new LinkedList*[levels.size - 1];
	Node* searchingNode = reality->head;

	for (int i = 0; i < levels.size - 1; i++) {
		while (searchingNode->DeeperDream == NULL) {
			searchingNode = searchingNode->next;
		}
		
		listOfLists[i] = searchingNode->DeeperDream;
		searchingNode = searchingNode->DeeperDream->head;
	}
	cout << endl << endl << "Non, rien de rien, Non, je ne regrette rien, Ni le bien qu'on m'a fait BRRRR BRRRRRRR BRRRRRR BRRRRRRRRR" << endl;
	
	for (int i = levels.size - 2; 0 <= i; i--) {
		listOfLists[i]->~LinkedList();
		delete listOfLists[i];
		listOfLists[i] = NULL;
		cout << "THE DREAM IS COLLAPSING!" << endl;
	}
	
	delete [] levels.name;
	levels.name = NULL;
	delete[] *listOfLists;
	*listOfLists = NULL;
	delete[] listOfLists;
	listOfLists = NULL;

	return 0; }

int main(int, char**) {/////////
	cout << "Inception" << endl << endl;//
	World *world = new World;/////////////
	cin >> world->levels;/////////////////
	//cout << world->levels;//////////////
	cin >> world;/////////////////////////
	//world->reality->fwdPrintList();/////
	//world->reality->bkwdPrintList();////
	world->printbylevel();////////////////
	cout << *world;///////////////////////
	world->givehimthekick();//////////////
	delete world; world = NULL;///////////
	cout << "\nTHE END\n\nCreated by ";///
	cout << "Jorge Fonseca" << endl;//////
	return 0;/////////////////////////////
} ////////////////////////////////////// 

