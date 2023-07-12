/*
* Name: Kristen Kaiser, 1008179340 , Homework 5
* Description: deconstructs txt doc into ordered lists of single word and 2 word phrases and allows user to veiw and save related data now with dynamically created arrays
* Input: user input and txt file via command line
* Output: 
	in termianl menu which allows user to requset data to view or save
	1gms.txt - list of unigrams ordered by times used in original text
	2gms.txt - list of bigrams ordered alphabetically
	ast1log.txt - record of all changes made to text in cleanup process	
*/


#include<iostream>
#include<string>
#include<cctype>
#include<fstream>
#include<stdlib.h>



using namespace std;

struct Unigram
{
	string word;
	int timesused;
};

struct Bigram
{
	string word;
	string word2;
	int timesused;
};
int numwords(string filename);
int readdata(string finename, string *&words, int arraysize);
int getlongword(struct Unigram *&list, int count);
void cleanup(string *&word, int wordcount);
int inList(string word, struct Unigram *&list, int count);
int inList(string word, string word2, struct Bigram *&list, int count);
void sortgms(struct Unigram *&unigram, int unigramCount, struct Bigram *&bigram, int bigramCount);
void generate_unigrams(struct Unigram *&unigram, int &unigramCount, string *&word, int wordcount);
void generate_bigrams(struct Bigram *&bigram, int &bigramCount, string *&word, int wordcount);
void write1gmslog(Unigram *&list, int unigramCount);
void write2gmslog(Bigram *&list, int bigramCount);
string lowercase(string word);



/*
* function_identifier: output menu and cal other funcions as requested by user
*/
int main(int argc, char *argv[])
{
	bool check;
	Unigram* ulist;
	int ulistcount = -1;
	Bigram* blist;
	int blistcount = 0;
	//string allwords[arraysize];
	string docname = argv[1];
	int wordcount;
	string command;
	string tempword;
	string tempword2;
	int tempnum;
	string gramtype;
	string* allwords;

	cout << "Homework 5" << endl;
	cout << "Kristen Kaiser" << endl;
	cout << "section 1001" << endl;
	cout << "*********************************************************" << endl;
	cout << "Opening file " << docname << endl << endl;
	wordcount = numwords(docname);
	
	allwords = new string[wordcount];
	ulist = new Unigram[wordcount];
	blist = new Bigram[wordcount];


	readdata(docname, allwords, wordcount);
	cleanup(allwords, wordcount);
	generate_unigrams(ulist, ulistcount, allwords, wordcount);

	cout << "Unigram array size: " << ulistcount << endl;
//resize unigram array	
	Unigram* temp;
	temp = new Unigram[ulistcount];
	for (int i = 0; i < ulistcount; i++)
		temp[i] = ulist[i];
	delete[] ulist;
	ulist = NULL;
	ulist = new Unigram[ulistcount];
	for (int i = 0; i < ulistcount; i++)
		ulist[i] = temp[i];
	delete [] temp;
	temp = NULL;
	


	
	generate_bigrams(blist, blistcount, allwords, wordcount);

	cout << "Bigram Array Size: " << blistcount << endl;

//resize bigram array
	Bigram* btemp;
	btemp = new Bigram[blistcount];
	for (int i = 0; i < blistcount; i++)
		btemp[i] = blist[i];
	delete [] blist;
	blist = NULL;
	blist = new Bigram[blistcount];
	for (int i = 0; i < blistcount; i++){
		blist[i] = btemp[i];
	}
	delete[] btemp;
	btemp = NULL;

	delete[] allwords;
	allwords = NULL;

	cout << "Longest Word: " << ulist[getlongword(ulist, ulistcount)].word << endl;
	sortgms(ulist, ulistcount, blist, blistcount);

	// menu
	while (1 != 2)
	{
		cout << "Commands" << endl;
		cout << "Unigram: search for unigram" << endl;
		cout << "Bigram: search for bigram" << endl;
		cout << "save: save 1gms.txt and 2gms.txt" << endl;
		cout << "index: print index of unigram or bigram" << endl;
		cout << "Quit/q: terminate program" << endl;

		cin >> command;
		command = lowercase(command);

		if (command == "q" || command == "quit") // quit
		{
			cout << "GoodBye!" << endl;
			exit(0);
		}
		else
			if (command == "unigram") //unigram
			{
				cout << "Enter your word to search: ";
				cin >> tempword;
				tempword = lowercase(tempword);
				cout << "Searching for " << tempword << "..." << endl;
				if (inList(tempword, ulist, ulistcount) == -1)
					cout << "Unigram not found." << endl;
				else
					cout << "Unigram Found at Index : " << inList(tempword, ulist, ulistcount) << " with frequency of " << ulist[inList(tempword, ulist, ulistcount)].timesused << endl;
			}
			else
				if (command == "bigram") //bigram
				{
					cout << "Enter Word 1 to search: ";
					cin >> tempword;
					tempword = lowercase(tempword);
					cout << "Enter Word 2 to search: ";
					cin >> tempword2;
					tempword2 = lowercase(tempword2);
					cout << "Searching for " << tempword << " " << tempword2 << "..." << endl;
					if (inList(tempword, tempword2, blist, blistcount) == -1)
						cout << "Bigram not found." << endl;
					else
						cout << "Bigram Found at Index : " << inList(tempword, tempword2, blist, blistcount) << " with frequency of " << blist[inList(tempword, tempword2, blist, blistcount)].timesused << endl;
				}
				else
					if (command == "save") // save
					{
						write1gmslog(ulist, ulistcount);
						write2gmslog(blist, blistcount);
					}
					else
						if (command == "index")//index
						{
						index:
							cout << "Enter Index: ";
							cin >> tempnum;
							check =  cin.fail();
							if (check) {
								cin.clear();
								cin.ignore(500, '\n');
								cout << "error: please enter an integer." << endl;
								goto index;


							}


							cout << "Unigram or Bigram? ";
							cin >> gramtype;
							gramtype = lowercase(gramtype);
							if (tempnum < 0)
								cout << "Invalid Entry: " << tempnum << endl;
							else
							{
								gramtype = lowercase(gramtype);
								if (gramtype == "unigram")
									if (tempnum > ulistcount)
										cout << "Unigram does not exist, index too large" << endl;
									else
										cout << "Index " << tempnum << ": \'" << ulist[tempnum].word << "\' with a frequency of " << ulist[tempnum].timesused << "." << endl;
								else
									if (gramtype == "bigram")
										if (tempnum > blistcount)
											cout << "Bigram does not exist, index too large" << endl;
										else
											cout << "Index " << tempnum << ": \'" << blist[tempnum].word << " " << blist[tempnum].word2 << "\' with a frequency of " << blist[tempnum].timesused << "." << endl;
									else
									{
										cout << "Invalid Entry. Try again" << endl;
										goto index;
									}
							}

						}
						else
						{
							cout << "-Invalid command-" << endl << "please try again" << endl;
						}
	}
	//endmenu

	return 0;
}

/*
* function_identifier: inputs each indivitual word from original text into array
* parameters: filname establised in command line, array to store read words, int value to store number of words read (by refrance)
* return value: what the function returns, if any
*/
int numwords(string filename) {
	int count = 0;
	string tempword;

	ifstream fin;
	fin.open(filename.c_str());

	if (!fin.is_open()) {
		cout << "error: " << filename << " did not open" << endl;
		return 0;
	}

	else {
	exitloop:
		while (!fin.eof()) {
			fin >> tempword;
			for (int i = 0; i < tempword.length(); i++)
				if (isalnum(tempword[i]))
				{
					count++;
					goto exitloop;
				}
		}
	}
	return count;
}

int readdata(string filename, string *&words, int arraysize)
{

	string tempword;
	int wordcount = 0;

	ifstream fin;
	fin.open(filename.c_str());

	if (!fin.is_open())
		cout << "error: " << filename << " did not open" << endl;

	fin >> tempword;
	while (!fin.eof()) // read word, writes to array if letter or number exhists as part of word
	{

		
		for (int i = 0; i < tempword.length(); i++)
			if (isalnum(tempword[i]))
			{
				words[wordcount] = tempword;
				wordcount++;
				break;
			}

	fin >> tempword;
	}
	fin.close();

	cout << "Finished Reading " << wordcount  << " Words. Closing File" << endl;
	return 0;
}

/*
* function_identifier: finds longest word in document
* parameters: array of structs (unigrams), number of elements in array
* return value: location of logest word in array
*/
int getlongword(struct Unigram *&list, int count)
{
	//cout << count << endl;
	int longestword = 0;
	int longestwordlocation;
	for (int i = 0; i < count-1; i++)
		if (longestword < list[i].word.length())
		{
			longestword = list[i].word.length();
			longestwordlocation = i;
		}

	return longestwordlocation;
}

/*
* function_identifier: removes all non alphanumaric characters from words, lowercases all words and replaces all words including a number with "NONALPAH"
* parameters: array of all words in original text, number of words in original text
* return value: void
*/
void cleanup(string *&word, int wordcount)
{
	char cleanchoice;
	string tempword;
	int numletters = 0;
	ofstream oin;


	cout << "Log cleanup? Y/n: ";
	cin >> cleanchoice;
	if (cleanchoice == 'y' || cleanchoice == 'Y')
	{
		oin.open("ast1log.txt");
		oin << "Nonalphanumeric Replacement Log file:" << endl << endl;
		cout << "Writing Log to \"ast1log.txt\"" << endl;
	}

	// lowercase all letters and replace words containing 0-9 with "NONALPHA"
	for (int i = 0; i < wordcount; i++)
	{
		word[i] = lowercase(word[i]);
	}

	for (int i = 0; i < wordcount; i++) //next word

	{
		tempword = word[i];
		numletters = 0;

		//remove punctuation, if punctuation is not at the end of word moves ' ' to end
		for (int j = 0; j < tempword.length(); j++) // next letter
		{
			//converst any words with 0-9 to nonalpha and skips to print 
			if (isdigit(word[i][j]))
			{
				tempword = word[i];
				word[i] = "NONALPHA";
				goto print;
			}

			word[i][j] = ' ';
			// removes all punctuation 
			if (isalnum(tempword[j]))
			{
				word[i][numletters] = tempword[j];
				numletters++;
			}
		}
		// remove ' ' at end of words
		word[i].resize(numletters);

	print:
		if (cleanchoice == 'y' || cleanchoice == 'Y')
			if (tempword != word[i])
			{

				oin << tempword << "        -->" << word[i] << endl;
			}
	}
	oin.close();
}

/*
* function_identifier: finds index of where unigram is in array
* parameters: unigram requested, array of structs (unigram), number of unigrams
* return value: value of where in array requested unigram is saved
*/
int inList(string word, struct Unigram *&list, int count)
{

	for (int i = 0; i <= count + 1; i++)
		if (list[i].word == word)
		{
			return i;
		}

	return -1;

}

/*
* function_identifier: finds index of where bigram is in array
* parameters: word 1 of bigram, word 2 of bigram, array of structs (bigram), number of bigrams
* return value: value of where in array requested bigram is saved
*/
int inList(string word1, string word2, struct Bigram *&list, int count)
{

	for (int i = 0; i <= count + 1; i++)
		if ((list[i].word == word1 && list[i].word2 == word2) || (list[i].word == word2 && list[i].word2 == word1))
		{
			return i;
		}

	return -1;
}

/*
* function_identifier: sorts unigrams by number of times used, sorts bigrams althabetically
* parameters: array of structs (Unigrams), number of unigrams, array of structs (Bigrams), number of bigrams
* return value: void
*/
void sortgms(struct Unigram *&unigram, int unigramCount, struct Bigram *&bigram, int bigramCount)
{
	Unigram utemp;
	Bigram btemp;
	
	for (int i = 0; i < unigramCount-1; i++) {
		//cout << "s1" << endl;
		for (int j = 0; j < (unigramCount-i-1); j++) {
			//cout << j <<"s2" << unigram[j].word<< unigram[j + 1].word<< endl;
			if (unigram[j].timesused < unigram[j + 1].timesused) {
				//cout << "s3" << endl;
				utemp = unigram[j];
				unigram[j] = unigram[j + 1];
				unigram[j + 1] = utemp;
			}
		}
	}

	for (int i = 0; i < bigramCount - 1; i++) {
		for (int j = 0; j < (bigramCount - i - 1); j++) {
			if (bigram[j].word == bigram[j + 1].word) {
				if (bigram[j].word2 > bigram[j + 1].word2) {
					btemp = bigram[j];
					bigram[j] = bigram[j + 1];
					bigram[j + 1] = btemp;
				}
			}
			else
			if (bigram[j].word > bigram[j + 1].word) {
				btemp = bigram[j];
				bigram[j] = bigram[j + 1];
				bigram[j + 1] = btemp;
			}
		}
	}
}

/*
* function_identifier: adds unigram to array if no other instance of unigram occures, otherwise increases other instances count
* parameters: array of structs (Unigrams),int to hold number of unigrams (by refrance), array of every word used in main text, number of words in main text
* return value: void
*/
void generate_unigrams(struct Unigram *&unigram, int &unigramCount, string *&word, int wordcount)
{
	for (int i = 0; i < wordcount; i++) //new word
	{
		for (int j = 0; j <= unigramCount; j++) //check if word already exhists
		{
			if (word[i] == unigram[j].word)
			{
				unigram[j].timesused = unigram[j].timesused + 1;
				//cout << unigram[j].word << " " << unigram[j].timesused++ << endl;
				goto newword;
			}

		}
		unigramCount++;
		unigram[unigramCount].word = word[i];
		unigram[unigramCount].timesused = 1;
	newword:
		cout << "";
	}


	
	



}

/*
* function_identifier: alphabetically orderes 2 words in bigram, adds bigram to array if bigram is not already in array otherwise increases the times_used on the previouly created element of the same name.
* parameters: array of structs (Bigrams), int to hold number of bigrams (by refrance), array of every word used in main text, number of words in main text
* return value: void
*/
void generate_bigrams(struct Bigram *&bigram, int &bigramCount, string *&word, int wordcount)
{
	Bigram temp;

	// alpha order bigram and place in temp struct 
	for (int i = 1; i < wordcount; i++) // next set of words
	{
		if (word[i - 1] > word[i])
		{
			temp.word = word[i];
			temp.word2 = word[i - 1];
		}
		else
		{
			temp.word = word[i - 1];
			temp.word2 = word[i];
		}
		//cout << temp.word << temp.word2 << endl;

		for (int j = 0; j <= bigramCount; j++) //check if bigram already exhists
		{
			if (temp.word == bigram[j].word && temp.word2 == bigram[j].word2)
			{
				bigram[j].timesused = bigram[j].timesused + 1;
				//cout << unigram[j].word << " " << unigram[j].timesused++ << endl;
				goto newword;
			}

		}
		bigramCount++;
		bigram[bigramCount].word = temp.word;
		bigram[bigramCount].word2 = temp.word2;
		bigram[bigramCount].timesused = 1;
		//cout << bigram[i].word << ": " << bigram[i].word2 << " " << bigram[i].timesused << endl;


	newword:
		cout << "";
	}

	//for (int i = 0; i < bigramCount; i++)
	//if(bigram[i].timesused !=-858993460)
	//cout << bigram[i].word << ": " << bigram[i].word2 << " " << bigram[i].timesused << endl;
}

/*
* function_identifier: writes list of unigrams orded by frequency of use in main text to 1gms.txt
* parameters: array of structs (unigrams), number of elements in passed array
* return value: void
*/
void write1gmslog(Unigram *&list, int unigramCount)
{
	ofstream oin;
	oin.open("1gms.txt");

	cout << "Writing logs for \"1gms.tct\"" << endl;

	for (int i = 0; i < unigramCount; i++)
		if (list[i].word != "")
			oin << list[i].word << ":" << list[i].timesused << endl;

	oin.close();
}

/*
* function_identifier: writes alphabetically ordered list of bigrams to 2gms.txt (a->z)
* parameters: array of structs (bigrams), number of elements in passed array
* return value: void
*/
void write2gmslog(Bigram *&list, int bigramCount)
{
	ofstream oin;
	oin.open("2gms.txt");

	cout << "Writing logs for \"2gms.tct\"" << endl;

	for (int i = 1; i < bigramCount; i++)
		if (list[i].word != "")
			oin << list[i].word << " " << list[i].word2 << ":" << list[i].timesused << endl;

	oin.close();
}

/*
* function_identifier: convert entire word to lowercase.
* parameters: string
* return value: string with all lowercase letters
*/
string lowercase(string word)
{
	for (int i = 0; i < word.length(); i++) // lowercase command
	{
		word[i] = tolower(word[i]);
	}


	return word;
}
