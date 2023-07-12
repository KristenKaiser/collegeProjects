/*
* Name: Kristen Kaiser, 1008179340 , Homework 11
* Description: program to manipulate and output data from secondary text doc
* Input: seperate text doc with first line: num of ints, second line: list of ints, third line: int to search for, forth line int to reverse 
* Output: num of its, original list of ints, reversed list of ints, if the number in the third line is in the list of ints, the reverse of the 4th line, if the fist line is a palindrome, and if 23532 is a palendrome
*/

#include <iostream>
using namespace std;
//CS 202 AST 11
//Skeleton program by Jorge Fonseca
bool elementPresent(int[], int, int);
void reverseDisplay(int);
void reverse(int[], int, int);
bool isPalindrome(int[], int, int);
void printArray(int[], int);
int main(int argc, char* argv[]) {
	int n, x, y;
	cin >> n;
	int *a;
	a = new int[n];
	for (int i = 0; i<n; i++) cin >> a[i];
	cin >> x;
	cin >> y;
	cout << n << " Integer Array:\n";
	printArray(a, n);
	cout << "\nReverse of Given Array:" << endl;
	reverse(a, 0, n);
	printArray(a, n);
	cout << "\n\nis " << x << " present in given array?\n";
	if (elementPresent(a, n, x)) cout << "Aye, Aye Captain!\n";
	else cout << "That's a negative, Captain!\n";
	cout << "\nGiven Integer is: " << y;
	cout << "\nReverse: ";
	reverseDisplay(y);
	cout << "\n\nIs given array a palindrome?\n";
	if (isPalindrome(a, 0, n)) cout << "Afirmative, Captain!\n";
	else cout << "Does not look like it, Captain!\n";

	cout << "\nIs 2 3 5 3 2 a palindrome?\n";
	int b[5] = { 2, 3, 5, 3, 2 };
	if (isPalindrome(b, 0, 5)) cout << "Afirmative, Captain!";
	else cout << "Does not look like it, Captain!";
	cout << endl;
	return 0;
}
void printArray(int a[], int n) {
	if (n>0) {
		printArray(a, n-1); //tail
		cout << a[n-1] << " "; //head
	}
}
//Your Code Here (For all four functions)
/*input:array of ints, size of array, and what element to search for
output: true if element is in array else false*/
bool elementPresent(int a[], int size, int element) {
	if (a[size] == element)
		return true;
	else if (size == 0)
		return false;
	else  
		elementPresent(a, size - 1, element);
}
/*inut: number to reverse
output: reverse of number*/
void reverseDisplay(int num) {
	cout << (num -((num / 10)*10));
	if (num / 10 == 0) 
		return;
	reverseDisplay(num / 10);
}

/*input: array, starting point int, ending point int
output: array is now sorted in reverse*/
void reverse(int a[], int start, int end) {
	if (start >= end) 
		return;
	else {
		swap(a[start], a[end-1]);
		reverse(a, start + 1, end - 1);
	}
}

/*input: array, starting point, ending point
output: true if array is palendrome else false*/
bool isPalindrome(int a[], int start, int end) {
	if (a[start] != a[end-1])
		return false;
	else if (start >= end)
		return true;
	else
		isPalindrome(a, start + 1, end - 1);
}
