/*
* Name: Kristen Kaiser, 1008179340, assignment 06
* Description:
* Input: user input for maipulating queues as requested by program
* Output: display of data in queues as they are altered
*/




#include<iostream>
#include<string>
#include<ctime>
using namespace std;




//#define DEBUG //Uncomment This to run checks, Comment it to run final version. 
//Program should work both ways. TAs will grade with both settings... they better!

template < class T>
class node {
public:
	//Your Code Here: Default Constructor
	node() {
		data = new T;
	}
	node(const T &var) : left(NULL), right(NULL) {
		//Your Code Here
		data = new T;
		*data = var;
	}
	//Your Code Here for Destructor
	~node() {
		delete data;
		data = NULL;
		delete left;
		left = NULL;
		delete right;
		right = NULL;
	
	}


	//Your Code Here to Overlaod Copy Constructor so you can make a node(node)

	node(const node& copy) {
		data = new T;
		*data = copy.getData();
	}




	//Your Code Here for Assignment Operator Overload to assign node to a node  (Part of Rule of 3)
	void operator= (const node &copy) {
		data = copy->data;
		right = copy->right;
		left = copy->left;

	
	}


	void operator=(const T &var) {  //Assignment Operator Overload to take literals
		*data = var;
	}
	void setData(T var) {
		*data = var;
	}
	T getData() const {
		//Your Code Here
		return *data;
	}
	friend std::ostream& operator<<(std::ostream& out, const node& n) {
		out << *n.data;
		return out;
	}
	//Your Code Here for >> operator overloading to read into n.data of a node& n. Make it inline
	friend std::istream& operator>>(std::istream& in, node& n) {
		in >> *n.data;
		return in;
	}

	//friend std::stringstream & operator>>(std::stringstream &out, const node& ) {}
	void setRight(T var) {
		right = var;

	
	}
	void setLeft(T var) {
		left = var;

	}
	

protected:
	T    *data;
	node *left;
	node *right;
	template <class U> friend class BinaryTree; //<--Don't you dare to @#$%$ touch this.
};




template <class T>
class BinaryTree {
public:
	static int counter;
	BinaryTree() : root(NULL), size(0) {
		root = new node<T>;
		
	}
	virtual ~BinaryTree() {                //Destructor                    (Part of Rule of 3)
#ifdef DEBUG
		cout << "De-allocating Tree here" << endl;
#endif
		//DeleteTree(&root);
		root = NULL;
	}
	BinaryTree(const BinaryTree &b2) {     //Copy Constructor Overload     (Part of Rule of 3)
#ifdef DEBUG
		cout << "Manually copying tree in copy constructor" << endl;
#endif
		//Your Code Here (Should call copyTree)
		root = new node<T>;
		copyTree(b2.root, &root);
	}
	int copyTree(node<T>* currOG, node<T>** currNEW) {

		if (!*currNEW) {
			cout << "hello";
			*currNEW = new node<T>;
			//T *(*currNEW)->data = new T;
		}
		//cout << currOG->data;
		(*currNEW)->data = currOG->data;
		if (currOG->left) {
			node<T> *nextNode = new node<T>;
			(*currNEW)->right = nextNode;
			copyTree(currOG->left, &nextNode);
		}
		if (currOG->right) {
			node<T> *nextNode = new node<T>;
			(*currNEW)->left = nextNode;
			copyTree(currOG->right, &nextNode);
		}
		return 0;
	}

	//overload | operator to act as mirror :D
	BinaryTree operator|(const BinaryTree& OG) {
#ifdef DEBUG
		cout << "Mirroring Tree!" << endl;
#endif
		if (OG.root == NULL) return OG;
		//DeleteTree(&root);
		this->root = NULL;
		this->size = mirrorTree(OG.root, &(this->root));
		return OG;
	}

	int mirrorTree(node<T>* currOG, node<T>** currNEW) {
		//Your Code Here
		if (*currNEW == NULL) {
			//currNEW = new node<T>*;
			*currNEW = new node<T>;
			root = *currNEW;

		}
		
	//	(*currNEW)->setData(currOG->data);
	//	(*currNEW)->data = currOG->data;
		(*currNEW)->setData(currOG->getData());
		node<T> *nextNode;
		if (currOG->right) {
			//cout << "right[" << currOG->right->getData() << "]" << endl;
			nextNode = new node<T>;
			(*currNEW)->right = nextNode;
			mirrorTree(currOG->right, &nextNode);
		}
		if (currOG->left) {
			//cout << "left[" << currOG->left->getData() << "]" << endl;
			nextNode = new node<T>;
			(*currNEW)->left = nextNode;
			mirrorTree(currOG->left, &nextNode) ;
		}

		return 0;
	}
	void operator=(const BinaryTree &b2) { //Assignment Operator Overload  (Part of Rule of 3)
#ifdef DEBUG
		cout << "Manually copy tree in assignment operator" << endl;
#endif
		DeleteTree(&root);
		this->root = NULL;
		this->size = copyTree(b2.root, &(this->root));
	}
	void readnGenerate(const T a[], int arr_size) {
		if (arr_size <= 0) return; //empty
#ifdef DEBUG
		cout << "Generating From: '" << a << "'\nOG Length: 00" << arr_size << endl;
#endif
		DeleteTree(&root);
		this->size = recInsert(a, arr_size, &root, 1);
#ifdef DEBUG
		cout << "Total Inserted: " << this->size << endl;
#endif

	}

	int calculateHeight(int size) {
		return (log2(size) + 1);
	}


	int recInsert(const T *a, int arrSize, node<T>**curr, int currIndex) {
		//Your Code Here'
	
		
		if (!(*curr)) {
			*curr = new node<T>;
			root = *curr;
			//(*curr)->data = new T;
		}
		if (!(*curr)->data) {
			//curr = new node<T>*;
			//root = *curr;
			(*curr)->data = new T;
		}

		if (currIndex > arrSize || !a[currIndex - 1]) {
			if(calculateHeight(currIndex) == calculateHeight(arrSize))
				(*curr)->setData('%');				
		return (arrSize);
		}
		else {
			counter++;
			(*curr)->setData(a[currIndex - 1]);
			node<T> *nextNode;
			
			if ((calculateHeight(currIndex) + 1) <= (calculateHeight(arrSize)) && a[(currIndex * 2) - 1] && a[(currIndex * 2) - 1] != '%') {
				nextNode = new node<T>;
				(*curr)->left = nextNode;
				recInsert(a, arrSize, &nextNode, currIndex * 2);//insert left
			}
			if ((calculateHeight(currIndex) + 1) <= (calculateHeight(arrSize)) && a[(currIndex * 2) ] && a[(currIndex * 2)] != '%') {
				nextNode = new node<T>;
				(*curr)->right = nextNode;
				recInsert(a, arrSize, &nextNode, (currIndex * 2) + 1) ;	//insert right
			}
		}
		return counter;
	}

	void inOrderTraversal(node<T>* curr) {
		//Your Code Here
		if (!curr)
			curr = root;
		if (curr->left && (*curr->left->data != '%' )) {
			inOrderTraversal(curr->left);
		}
		cout << *curr->data;
		if (curr->right && *curr->right->data != '%') {
			inOrderTraversal(curr->right);
		}

	}
	void preOrderTraversal(node<T>* curr) {
		//Your Code Here
		if (!curr)
			curr = root;
		cout << *curr->data;
		if (curr->left && (*curr->left->data != '%')) 
			preOrderTraversal(curr->left);
		if (curr->right && *curr->right->data != '%') 
			preOrderTraversal(curr->right);
	}
	void postOrderTraversal(node<T>* curr) {
		//Your Code Here
		if (!curr)
			curr = root;
		if (curr->left && (*curr->left->data != '%')) 
			postOrderTraversal(curr->left);
		if (curr->right && *curr->right->data != '%') 
			postOrderTraversal(curr->right);
		cout << *curr->data;
	}
	int getHeight(node<T> *curr) {
		//Compute Height of both subtrees and keep the larger one
		if (curr == NULL) return 0; //base case
		else {
			int lheight = getHeight(curr->left);
			int rheight = getHeight(curr->right);
			if (lheight > rheight) return lheight + 1;
			else return rheight + 1;
		}
	}
	void printSpecificLevel(node<T> *root, int level) {
		//node<T> blankCheck
		if (root == NULL) return;
		if (level == 1 && *root->data != '%' ) cout << *root;//  *root->data != '%' added to prevent printing undefined spaces
		else if (level > 1) {
				printSpecificLevel(root->left, level - 1);
				printSpecificLevel(root->right, level - 1);
		}
	}
	void printLevelOrderTraversal() {
		for (int i = 0; i <= getHeight(root); i++) {
			//Your Code Here. Should be one line of code, 
			printSpecificLevel(root, i); //a fucntion call to printSpecificLevel with root and i as parameters
		}
	}
protected:
	node<T> *root;
	int size;
private:
	void DeleteTree(node<T>** curr) {

		if ((*curr)->left)//if you can go left go left
			DeleteTree(&(*curr)->left);
		if ((*curr)->right)// after there are no more lefts if you cant go right delete current
			DeleteTree(&(*curr)->right);
		delete *curr;
		*curr = NULL;
	}
};
template <class T>
int BinaryTree<T>::counter = 0;


template<class T>
class OmegaSeamaster {
public:
	OmegaSeamaster() : BinaryTreeTemp(NULL) {}
	//Note:  Technically Needs Assignment Operator and Copy Constructor Overloading,
	// but I didn't add them. You probably should
	BinaryTree<T>  BinaryTreeFunction;
	BinaryTree<T>* BinaryTreeTemp;
	void Alarm() {
		cout << "Alarm: BOOM!" << endl;
	}
	void Time() {
        time_t t = std::time(0);
        cout << "                      Time: " << localtime(&t)->tm_hour 
             << ":" << localtime(&t)->tm_min 
             << ":" << localtime(&t)->tm_sec << endl;
	}
	void CleanTemp() {
		//Your Code Here
	}
	void Draw() {
		cout << "                           ||||                           \n";
		cout << "                   /\\      ||||      /\\                   \n";
		cout << "                   \\/             /| \\/                   \n";
		cout << "               /\\      |\\        / |     /\\               \n";
		cout << "               \\/       \\\\      / /      \\/               \n";
		cout << "                         \\\\    / /                        \n";
		cout << "           ____           \\\\__/ /         ____            \n";
		cout << "          |____|           |__|/         |____|           \n";
		cout << "                            /                             \n";
		cout << "                           /                              \n";
		cout << "               /\\         /              /\\               \n";
		cout << "               \\/        / Omega         \\/               \n";
		cout << "                   /\\   /            /\\                   \n";
		cout << "                   \\/  /    ||       \\/                   \n";
		cout << "                            ||                            " << endl; //Feel Free to make this pretier.
	} //Extra Credit Points if you make the watch actually work and draw the hands in the right spots representing current time.
	//Reedem your test grade and do the extra credit!!!
	~OmegaSeamaster() {
		//Your Code Here
	}
};


//You are not allowed to modify any code beneath this line. DO NOT TOUCH MAIN!
#ifdef DEBUG
#include<sstream>
#endif
//Client Code Given To Q Branch
int main(void) {
#ifdef DEBUG
	cout << "Q BRANCH DEBUG MODE ONLINE. SHOULD HAVE 0 MEMORY LEAKS" << endl;
	//Node Tests
	node<int>* testNode0 = new node<int>;
	testNode0->setData(007);
	node<int> testNode1(*testNode0);
	cout << testNode0->getData() << " = " << *testNode0 << " = " << testNode1 << " = 7" << endl;
	*testNode0 = 0;
	cout << *testNode0 << " = 0 and " << *testNode0 << " != " << testNode1 << endl;

	node<string>* testNode2 = new node<string>;
	string agentname = "James Bond";
	stringstream ss(agentname);
	ss >> *testNode2;
	cout << *testNode2 << " ";
	ss >> *testNode2;
	cout << *testNode2 << endl;
	node<float> testNode3 = 0.07f;
	cout << testNode3 << " = 0.07" << endl;
	cout << reinterpret_cast<void*>(testNode2) << " <--Some Memory Address that is not 0" << endl;
	node<int>* testNode4 = testNode0;
	delete testNode4; delete testNode2;
	//Binary Tree Tests
	char testmsg1[] = { 'R','O','L','E','X','%', '?','\0' };
	//All % symbols indicate empty spots in a tree and should not be inserted, but skipped instead
	BinaryTree<char> *testTree0 = new BinaryTree<char>;
	BinaryTree<char> *testTree1 = new BinaryTree<char>;
	cout << "Read and Traversal Tests: " << endl;
	testTree0->readnGenerate(testmsg1, string(testmsg1).length());
	cout << "Total Inserted Should be 6 since % was skipped" << endl;
	testTree0->inOrderTraversal(NULL);   cout << " = EOXRL?" << endl;
	testTree0->preOrderTraversal(NULL);  cout << " = ROEXL?" << endl;
	testTree0->postOrderTraversal(NULL); cout << " = EXO?LR" << endl;
	testTree0->printLevelOrderTraversal(); cout << " = ROLEX?" << endl;
	cout << "End Traversal Tests" << endl;
	cout << "Mirror Test and Traversals:" << endl;
	BinaryTree<char> testTree2;
	testTree2 | *testTree0; //Mirror
	testTree2.printLevelOrderTraversal(); cout << " = RLO?XE" << endl;
	testTree2.inOrderTraversal(NULL); cout << " = ?LRXOE" << endl;
	testTree2.preOrderTraversal(NULL); cout << " = RL?OXE" << endl;
	testTree2.postOrderTraversal(NULL); cout << " = ?LXEOR" << endl;
	cout << "End Mirror Traversal Tests" << endl;
	*testTree1 = *testTree0;
	cout << "Assignment Operator Test" << endl;
	testTree1->printLevelOrderTraversal(); cout << " = ROLEX?" << endl;
	BinaryTree<char> testTree3(*testTree0);
	cout << "Copy Constructor Test" << endl;
	testTree3.printLevelOrderTraversal(); cout << " = ROLEX?" << endl;
	delete testTree0; testTree0 = NULL;
	testTree1->printLevelOrderTraversal(); cout << " = ROLEX?" << endl;
	delete testTree1; testTree1 = NULL;
	BinaryTree<int> testTree4; cout << "Align Arrows -->" << flush;
	testTree4.postOrderTraversal(NULL); cout << "<--" << endl;
	cout << "Good Job, Agent. End of Debug Section" << endl;
	cout << "\n************************************************" << endl;
#endif

	//Captured Chatter:
	string msg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string msg1 = "Shaken, not Stirred";
	string msg2 = "You were the chosen one!";
	string msg3 = "Bond, James Bond";
	string cryptmsg[6];
	cryptmsg[0] = "C3PO Bot Never Forgets";
	cryptmsg[1] = "adl 3aa .nr..idn erioBe fmno oerRuraw eBnF .isy  acS";
	cryptmsg[2] = "Roaleuue g tfl%x?Oma,Bei";
	cryptmsg[3] = "..R.  ad . nnrin ewsdneiau racSoBforaeBya 3i mo lreF";
	cryptmsg[4] = "nS r   !ef'grAh%!cp osteaeasTeT%%!et";
	cryptmsg[5] = "Wehi er% ?700 s%%%%%%%%%%%%%%%%392aaahuusf%riiffooambnctnas";
	//End of Captured Chatter

	cout << "\nGood evening Mr. Bond, your latest Q Watch v2.01 Beta features a decoder that\n"
		<< "will take a level order binary tree list, generate the tree, and then return\n"
		<< "all of the available traversals. Using this technology you should be able to\n"
		<< "intercept and decipher any potential messages that Spectre's agents may be\n"
		<< "attempting to send within your vicinity.\n"
		<< "You should find it quite useful in the field. Oh, one word of warning.\n"
		<< "The alarm is rather loud. If you know what I mean.\n" << endl;
	OmegaSeamaster<char> myWatch;

	//Cypher Tester
	myWatch.BinaryTreeFunction.readnGenerate(msg0.c_str(), string(msg0).length());
#ifdef DEBUG
	cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal(); cout << endl;
	cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL); cout << endl;
	cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL); cout << endl;
	cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL); cout << endl;
#endif
	myWatch.BinaryTreeTemp = new BinaryTree<char>(myWatch.BinaryTreeFunction);
	myWatch.BinaryTreeFunction | *myWatch.BinaryTreeTemp;
#ifdef DEBUG
	cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal(); cout << endl;
	cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL); cout << endl;
	cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL); cout << endl;
	cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL); cout << endl;
#endif

	myWatch.Time();
	myWatch.Draw();

	//Cryptomsg
	int msgnum = 0;
	for (;;) {
		cout << "\nEnter a Frequency from 1-5 to Decrypt. Enter 0 to Exit: " << endl;
		cin >> msgnum; if (msgnum == 0) goto q; if (msgnum < 0 || msgnum > 5) goto BondJamesBond;
		myWatch.BinaryTreeFunction.readnGenerate(cryptmsg[msgnum].c_str(), string(cryptmsg[msgnum]).length());

		cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal(); cout << endl;
		cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL); cout << endl;
		cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL); cout << endl;
		cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL); cout << endl;

		myWatch.CleanTemp();
		myWatch.BinaryTreeTemp = new BinaryTree<char>(myWatch.BinaryTreeFunction);
		myWatch.BinaryTreeFunction | *myWatch.BinaryTreeTemp;

		cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal(); cout << endl;
		cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL); cout << endl;
		cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL); cout << endl;
		cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL); cout << endl;
	} BondJamesBond:

	myWatch.Alarm();
	cout << "OmegaLuL" << endl; q:;
	return 007;
}