/*
* Name: Kristen Kaiser, 1008179340 , Homework 10
* Description: read text file and output info about contents
* Input: txt file with words and numbers
* Output: count of numbers, list of numbers input, sum of numbers, smallest number, number of letters, copy of list of letters, count of vowels and if the list of numbers matched an array pre initalized.
*/

#include <iostream>
using namespace std;
//CS 202 AST 10
//Skeleton program by Jorge Fonseca
int min2(int, int);
int intSum(int[], int);
int minEntry(int[], int);
int vowelCount(char[], int);
void printArray(int[], int);
void printArray(char[], int);
bool areEqual(int[], int[], int, int);
int main(int argc, char* argv[]) {
	int n, m;
	cin >> n >> m;
	int *a;
	char *c;
	a = new int[n];
	c = new char[m];
	for (int i = 0; i<n; i++) cin >> a[i];
	for (int i = 0; i<m; i++) cin >> c[i];
	cout << n << " Integers:\n";
	printArray(a, n);
	cout << "\nSum: " << intSum(a, n);
	cout << "\nMin: " << minEntry(a, n);
	cout << "\n\n" << m << " Characters:\n";
	printArray(c, m);
	cout << "\nVowel Count: " << vowelCount(c, m);
	int a2[6] = { 2, 3, 6, -2, 4, -6};
	cout << "\n\nTesting Equality with a2... ";
	if (areEqual(a, a2, n, 6)) cout << "They are Equal.\n";
	else cout << "They are not equal.\n";
	return 0;
}
int min2(int a, int b) {
	return ((a<b) ? a : b);
}
int intSum(int a[], int n) {
	if (n == 1) return a[0];
	else return (intSum(a, n-1) + a[n-1]);
}
//Your Code Here(minEntry and vowelCount)

/*intput pointer array, size of pointer array
output: smallest member of array
checks if value at pointer array is smallest value, if not checks if the value at the next address is the smallest */
int minEntry(int a[], int n){
	//n--;
	if (n == 0) 
		return *a;
return (*a < a[n] ? minEntry(a, n-1): minEntry(a+1, n-1));
	}

/*input: array of chars, size of array
output: count of vowels in array
adds 1 to return value for every vowel element in char array*/
int vowelCount(char a[], int n){
	if (n == 0)return 0;
	else
		if (tolower(a[n]) == 'a' || tolower(a[n]) == 'e' || tolower(a[n]) == 'i' || tolower(a[n]) == 'o' || tolower(a[n]) == 'u' || tolower(a[n]) == 'y') //lowercases a[n] and checks if vowel
			return 1 + (vowelCount(a, n - 1)); //return vowel count +1 if true
		else
			return (vowelCount(a, n - 1)); //else return vowel count +0 if false
}
void printArray(int a[], int n) {
	if (n>0) {
		printArray(a, n-1); //tail
		cout << a[n-1] << " "; //head
	}
}
//Your Code Here (printArray and equality)
/*input: array of chars, number of chars in array
output: prints array of chars*/
void printArray(char a[], int n){
	cout << a[0] << ' ';
	a++;
	if (n == 1)
		return;
	else
		printArray(a, n - 1);



}

/*input: 2 arrays to compare and 2 ints of the size of the 2 arrays
output: true if the 2 arrays hold the same ints, else false

*/
bool areEqual(int arrayOne[], int arrayTwo[], int sizeArrayOne, int sizeArrayTwo) {
	sizeArrayOne--;
	sizeArrayTwo--;

	if (arrayOne[sizeArrayOne] != arrayTwo[sizeArrayTwo])
		return false;
	if (sizeArrayOne == 0){
		return true;
}
	areEqual(arrayOne, arrayTwo, sizeArrayOne, sizeArrayTwo);
}