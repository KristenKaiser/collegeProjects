/*
* Name: Kristen Kaiser, 1008179340 , Homework 8
* Description: deconstructs txt doc into ordered lists of single word and 2 word phrases and allows user to veiw and save related data
* Input: text file with equasions (+,-,%,/,*) of strings in text form 
* Output: result of each line where 
+ concatinates two strings, 
- removes the second string from the first, 
/ seperates the first sring into x equal length strings and discards remainder,
% out puts the remainder of division, 
*duplicates the righthand side x times
*/

#include<iostream>
#include<fstream>


using namespace std;

int size(int place);

class Opperands { // holds relevant info for either lefthand side or righthand side of the equasion
public:
	char *stringOfChars;
	char **stringofTwoChars;
	int stringOfCharsSize;
	int numDun; //for multiplication or division
	char symbol;
	Opperands(int size) {
		stringOfChars = new char[size];
		stringOfCharsSize = size;
	}

	char** createTwoD(int divisor);
	friend istream& operator >> (istream&, Opperands&);
	friend ostream& operator << (ostream&, Opperands&);
	char * operator +(Opperands);
	char * operator -(Opperands);
	char * operator %(Opperands);
	char * operator *(Opperands);
	char ** operator /(Opperands);
};

char** Opperands::createTwoD(int divisor) { //creates a two dimensional array
	stringofTwoChars = new char *[divisor];
	for (int i = 0; i < divisor; i++) {
		stringofTwoChars[i] = new char[(stringOfCharsSize/divisor)+1];//+1 allows for newline to be included
	}
	return stringofTwoChars;
}

char * Opperands::operator + (Opperands wordTwo) { //addition: concatinates 2 arrays of chars
	char *tempOne = new char[stringOfCharsSize + wordTwo.stringOfCharsSize];
	for (int j = 0; j < (stringOfCharsSize + wordTwo.stringOfCharsSize); j++)
	{
		for (int i = 0; i < stringOfCharsSize; i++) {
			tempOne[j] = stringOfChars[i];
			j++;
		}
		for (int i = 0; i < wordTwo.stringOfCharsSize; i++) {
			tempOne[j] = wordTwo.stringOfChars[i];
			j++;
		}
	}
	stringOfCharsSize = stringOfCharsSize + wordTwo.stringOfCharsSize;
	delete[]stringOfChars; //delete first stringOfArrays
	stringOfChars = NULL;
	stringOfChars = new char[stringOfCharsSize];
	for (int i = 0; i < stringOfCharsSize; i++)
		stringOfChars[i] = tempOne[i];
	delete[] tempOne;
	tempOne = NULL;
	return stringOfChars;
}
char * Opperands::operator - (Opperands wordTwo) { // subtraction: removes sequential set of strings from RHS 
	bool placeCheck;
	for (int i = 0; i < stringOfCharsSize - wordTwo.stringOfCharsSize; i++) {
		placeCheck = true;
		for (int j = 0; j < wordTwo.stringOfCharsSize; j++) {
			if (stringOfChars[i + j] != wordTwo.stringOfChars[j]) {
				placeCheck = false;
			}
		}
		if (placeCheck == true) {
			stringOfCharsSize = stringOfCharsSize - wordTwo.stringOfCharsSize;
			while (i < stringOfCharsSize) {
				stringOfChars[i] = stringOfChars[i + wordTwo.stringOfCharsSize];
				i++;
			}

			//shorten string of chars
			char *tempMinus = new char[stringOfCharsSize];
			for (int k = 0; k < stringOfCharsSize; k++) {
				tempMinus[k] = stringOfChars[k];
			}
			delete[]stringOfChars;
			stringOfChars = NULL;
			stringOfChars = new char[stringOfCharsSize];
			for (int k = 0; k < stringOfCharsSize; k++) {
				stringOfChars[k] = tempMinus[k];
			}
			delete[]tempMinus;
			tempMinus = NULL;
		}
	}

	return stringOfChars;
}
char * Opperands::operator % (Opperands wordTwo) { //modulus: outputs what would be the remainder if the equasions was divided 
	int mod = stringOfCharsSize%wordTwo.numDun;
	char *temp = new char[mod];
	for (int i = 0; i < mod; i++) {
		temp[i] = stringOfChars[i + (stringOfCharsSize - mod)];
	}
	delete []stringOfChars;
	stringOfChars = NULL;
	stringOfChars = new char[mod];
	for (int i = 0; i < mod; i++) {
		stringOfChars[i] = temp[i];
	}
	stringOfCharsSize = mod;
	delete[]temp;
	temp = NULL;

	return stringOfChars;
}
char * Opperands::operator * (Opperands wordTwo) { // multiplication: duplicates rhs by the lhs
	int mod = stringOfCharsSize * wordTwo.numDun;
	char *temp = new char[mod];
	for (int i = 0; i < wordTwo.numDun; i++) {
		for (int j = 0; j < stringOfCharsSize; j++) {
			temp[(i*(stringOfCharsSize))+j] = stringOfChars[j];
		}
	}
	delete[]stringOfChars;
	stringOfChars = NULL;
	stringOfChars = new char[mod];
	for (int i = 0; i < mod; i++) {
		stringOfChars[i] = temp[i];
	}
	stringOfCharsSize = mod;
	delete[]temp;
	temp = NULL;
	return stringOfChars;
}

char ** Opperands::operator /(Opperands divisor) { // division : seperates rhs into lhs number of pieces, arrays piece is an array inside of the larger array, discards modulus 
	int placeCount = 0;
	int outputCount = stringOfCharsSize / divisor.numDun;
	createTwoD(divisor.numDun);
	numDun = divisor.numDun;
	for (int i = 0; i < divisor.numDun; i++) {
		for (int j = 0; j < outputCount; j++) {
			stringofTwoChars[i][j] = stringOfChars[placeCount];
			placeCount++;
		}
		stringofTwoChars[i][outputCount] = '\n';
	}
	stringOfCharsSize = outputCount;
	return stringofTwoChars;
}

istream& operator >> (istream& wordsin,  Opperands& oppArray) {//inputs word into array of chars
	for (int i = 0; isalnum(cin.peek()); i++) {
		cin >> oppArray.stringOfChars[i];
	}
	
	return wordsin;
}

ostream& operator << (ostream& wordsout, Opperands& oppArray) { //outputs and deallocates arrays
	if (oppArray.symbol == '/') {
		for (int i = 0; i < oppArray.numDun; i++) {
			for (int j = 0; j < oppArray.stringOfCharsSize+1; j++) {
				cout << oppArray.stringofTwoChars[i][j];
				
			}
			delete[]oppArray.stringofTwoChars[i];
			oppArray.stringofTwoChars[i] = NULL;
		}
		delete[]oppArray.stringofTwoChars;
		oppArray.stringofTwoChars = NULL;

	}
	else {
		for (int i = 0; i < oppArray.stringOfCharsSize; i++)
			cout << oppArray.stringOfChars[i];
		cout << endl;
	}
	delete[] oppArray.stringOfChars;
	oppArray.stringOfChars = NULL;
	return wordsout;
}


int main()
{

	//while (!cin.eof()) {
	for ( int i = 0; i < 3; i++){
		Opperands first(size(cin.tellg())); //initialize class for right side of equasion
		cin >> first; //input word and size of word to first opperand class
		do {
			cin >> first.symbol; //collects +,-,*,%
			while (cin.peek() == ' ') //ignores whitespace after symbol
				cin.ignore();
			Opperands second(size(cin.tellg())); // initalizes class for left side of equasion
			if (first.symbol == '/' || first.symbol == '%' || first.symbol == '*')
				cin >> second.numDun; //records int for LHS
			else {
				cin >> second; //records word from LHS
			}

			//preforms algebra 
			if (first.symbol == '+')
			{
				first.stringOfChars = first + second;
			}
			else
				if (first.symbol == '-')
				{
					first.stringOfChars = first - second;
				}
				else
					if (first.symbol == '/')
					{
						first.stringofTwoChars = first / second;
					}
					else
						if (first.symbol == '%')
						{
							first.stringOfChars = first % second;
						}
						else
							if (first.symbol == '*')
							{
								first.stringOfChars = first * second;
							}
			while (cin.peek() == ' ') { // skips whitespaces before next symbol or newline
				cin.ignore();
			}
		} while (cin.peek() != '\n');
		cin.ignore();
		cout << first;
	}
    return 0;
}

int size(int place) {

	int i = 0;
	char junk;
	cin.seekg(place);
	while (isalnum(cin.peek())) {
		cin.ignore();
		i++;
	}
	cin.seekg(place);
	return i;
};

