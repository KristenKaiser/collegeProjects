/** 
Name: Kristen Kaiser, 1008179340, assignment 02
Description: run 4 algorithms which are written either iterative or recursive depending on user input
Input: "iterative" or "recursive" in command line; Number of timeseach algorithm should run
Output: count of how many times each algorithm looped
*/

#include<iostream>
#include<stdio.h>
#include<string>
#include<exception>
#include<chrono>

using namespace std;

const int nCap = 100; // maximum n that can be tested, do not raise ove 164 as code 4's count will overflow


/*
*function_identifier: print what code was run and the count of loops. 
*parameters:  (int) code id, (int) count of loops, (time_point) time the algorithim started, (time point) time algorithm ended, (bool) if you are displaying time analysis
*return value: none
*/
void print(int code, int count, chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point end, bool displayTime) {
	//chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	cout << "Code " << code << ": count = " << count;
	if (displayTime == true) {
		cout << " time: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds";
	}
	cout << endl;
}

/* Function for Code 3*/
void fcn(int n, int *count) {
	int i;
	for (i = 0; i < n; i++) {
		++*count;
	}
}

/*
*function_identifier: loop n times keeping count
*parameters: (int) num of times to run, (int)times already run
*value: count of loop 
*/
int code1(int n, int count) { //recursive mmimicking a single for loop 
	if (n > 0) 
		code1(n - 1, count + 1);
	else if (n == 0) 
		return count;
}

/*
*function_identifier: loop n times keeping count, passing back to fcn function for each loop
*parameters: (int) num of times to run, (int)times already run, (int) num of times to run[stays constant]
*value: count of loop
*/
int code2(int n, int count, int c) { //recursive functon that calls fcn
	if (n > 0) {
		code2(n - 1, code1(c, count), c);
	}
	else if (n == 0) 
		return count;
}
/*
*function_identifier: loop n times keeping count, passing back to code2 [which passes to code3 function which passes to code 1 with n tripled] function for each loop
*parameters: (int) num of times to run, (int)times already run, (int) num of times to run[stays constant]
*value: count of loop
*/
int code3(int n, int count, int c) {//recursive mimicking a double for loop
	if (n > 0) {
		fcn(c, &count);
		code3(n - 1, count, c);
	}
	else if (n == 0)
		return count;
}

/*
*function_identifier: loop n times keeping count, passing back to code2 [which passes to code1 function] function for each loop
*parameters: (int) num of times to run, (int)times already run, (int) num of times to run[stays constant]
*value: count of loop
*/
int code4(int n, int count, int c) {//recursive mimicking a triple for loop
	if (n > 0) {
		code4(n - 1, code2(c, count, c*3), c);
	}
	else if (n == 0) 
		return count;
}




		int main(int argc, char *argv[]) {
		//Code
		int count; /*keep track of counts */
		int i;
		int j;
		int k;
		int n;
		bool recursive;
		string codeChoice;
		bool timeOn = false;
		string timeTest;
		chrono::duration<double> elapsed_seconds;
		chrono::high_resolution_clock::time_point start;
		chrono::high_resolution_clock::time_point end;
		
		//set commandline dependent variables only if they exist 
		if (argc > 1) {
			codeChoice = argv[1]; 
			if (argc > 2){
				timeTest = argv[2];
				//enable time analysis 
				if (timeTest == "time") //check if command line argument 2 == time
					timeOn = true;
				else {
					cout << "Invalid command line argument " << timeTest << endl;
				timeTestChoice: //jump here if used does not choose y,Y,n,N
					cout << "Would you like to see how long each piece of code takes to run? (y/n)" << endl;
					cin >> timeTest;
					if (timeTest == "y" || timeTest == "Y")
						timeOn = true;
					else if (timeTest != "n" || timeTest != "N") {
						cout << "Invalid command" << endl;
						goto timeTestChoice;
					}
				}
			}
		}
		
		//set recursive or itertive 
		if (codeChoice != "recursive" && codeChoice != "iterative") { //if recursive or iterative is not declared via command line argument 
			cout << "No valid code codeChoice declared in command line argument" << endl;
		chooseCode:// jump here input other than I, i, R, r for code 
			cout << "Which code would you like to run" << endl;
			cout << "(R/r) Recursive" << endl;
			cout << "(I/i) Iterative " << endl;
			cin >> codeChoice;
			if (codeChoice == "r" || codeChoice == "R")
				codeChoice = "recursive";
			else if (codeChoice == "i" || codeChoice == "I")
				codeChoice = "iterative";
			else {
				cout << "unexpected input please try again" << endl;
				goto chooseCode;
				}
			}
		
		if (codeChoice == "recursive") 
			recursive = true;
		else if (codeChoice == "iterative") 
			recursive = false;

		cout << endl << "Displaying " << codeChoice << " results";
		if (timeOn == true)
			cout << ", time analysis on";
		cout << endl << endl;

		do{
		cout << "Enter a value for n (0 to stop): ";
		cin >> n;
			if (n > 100)
			cout<< "n capped at 100, please pick a diffrent number" << endl << endl;
		}while(n > 100);// cap n at 100 to prevent overflow in code 4
		while (n != 0) {
			if (recursive == false) {
				
				/*Code 1 */
				start = chrono::high_resolution_clock::now();
				count = 0;
				for (i = 0; i < n; i++)
					++count;
				end = chrono::high_resolution_clock::now();


				print(1, count, start, end, timeOn);

				
				/*Code 2 */
				start = chrono::high_resolution_clock::now();
				count = 0;
				for (i = 0; i < 2 * n; i++)
					for (j = 0; j < n; j++)
						++count;
				end = chrono::high_resolution_clock::now();
				print(2, count, start, end, timeOn);
				
				/*Code 3 */
				start = chrono::high_resolution_clock::now();
				count = 0;
				for (i = 0; i < n; i++)
					fcn(n, &count);
				end = chrono::high_resolution_clock::now();
				print(3, count, start, end, timeOn);

				/*Code 4 */
				start = chrono::high_resolution_clock::now();
				count = 0;
				for (i = 0; i < n * n; i++)
					for (j = 0; j < n; j++)
						for (k = 0; k < 3 * n; k++)
							++count;
				end = chrono::high_resolution_clock::now();
				print(4, count, start, end, timeOn);
			}
			else {
				/*Code 1 */
				start = chrono::high_resolution_clock::now();
				count = code1(n, 0);
				print(1,count, start, chrono::high_resolution_clock::now(), timeOn);
				

				/*Code 2 */
				start = chrono::high_resolution_clock::now();
				count = code2(n * 2, 0, n);
				print(2, count, start, chrono::high_resolution_clock::now(), timeOn);
				
				

				/*Code 3 */
				start = chrono::high_resolution_clock::now();
				count = code3(n, 0, n);
				print(3, count, start, chrono::high_resolution_clock::now(), timeOn);
				
				

				/*Code 4 */
				start = chrono::high_resolution_clock::now();
				count = code4(n*n, 0, n);
				print(4, count, start, chrono::high_resolution_clock::now(), timeOn);
				
				
			}
		do{
		cout << "Enter a value for n (0 to stop): ";
		cin >> n;
		if (n > nCap)
			cout<< "n capped at " << nCap <<  ", please pick a diffrent number" << endl << endl;
		}while(n > nCap);
		}
		return (0);
	}
