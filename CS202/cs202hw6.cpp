/*
* Name: Kristen Kaiser, 1008179340 , Homework 6
* Description: retrieves 7 key codes hidden in classes in vault.h and usued the data to unlock sections. for the last section the lock is changed to accept the value of zero instead of requiring the original key.
* Input: vault.h
* Output: list of all keys discovered and a message saying access granted
	
*/
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>


#ifndef VAULT_H
#include "vault.h"
#endif

/*
These #ifdef DEBUG you see are activated in vault.h you can
uncomment #define DEBUG there to help you work on the assignment,
but when you submit it your program must work for BOTH cases when
#define DEBUG is commented out and when it's not. Please add extra
comments with memory addresses and what you are doing in that
version. otherwise DO NOT TOUCH vault.h Good luck, Agent! -JF
*/

using namespace std;

int main() {
#ifndef DEBUG
	srand(time(NULL)); // For Rand to seed correctly
#endif
					   //Create Key
	key_gen k;

	//Create Variables to store hax0red numbers.
	num h0 = 0, h1 = 0, h2 = 0, h3 = 0, h4 = 0, h5 = 0, h6 = 0;

	//Check if Haxed:
	k.iskey(h0, h1, h2, h3, h4, h5, h6);

	cout << "\n**Beginning Hack**\n" << endl;

	//Test if lockout works
	for (int i = 0; i<15; i++)
		;//	k.iskey(h0, h1, h2, h3, h4, h5, h6);

		 //Debug
	cout << "Initial Hacked:" << endl;
	cout << h0 << " " << h1 << " " << h2 << " ";
	cout << h3 << " " << h4 << " " << h5 << " " << h6 << endl;

	//Your Code Here:

	//VAULT 0: Easy one they didn't even try...
	
	int* temp;
	temp = new int;

	cout << endl << "V0 Key PreHax : " << h0 << endl;
	cout << "V0 Key PreHax Address : " << &h0 << endl;
	
	
	*temp = *(int*)k.v0;
	h0 = *temp;

	cout << "V0 Key PostHax Address :" << h0 << endl;
	cout << "V0 Key PostHax : " << &h0 << endl << endl;

	//VAULT 1: Should be easy too
	
	k.v1.maintenanceMode();
	
	cout << endl <<  "V1 Key PreHax : " << h1 << endl;
	cout << "V1 Key PreHax Address : " << &h1 << endl;
	
	h1 = *k.v1.maintenance;

	cout << "V1 Key PostHax Address :" << h1 << endl;
	cout << "V1 Key PostHax : " << &h1 << endl << endl;

	//VAULT 2: You'll need some pointer casting
	
	
	k.v2.maintenanceMode();

	cout << endl << "V2 Key PreHax : " << h2 << endl;
	cout << "V2 Key PreHax Address : " << &h2 << endl;

	temp = (int*)k.v2.maintenance;
	h2 = *temp;

	cout << "V2 Key PostHax Address :" << h2 << endl;
	cout << "V2 Key PostHax : " << &h2 << endl << endl;
	//VAULT 3: Kind of a mix of the previous two with static_cast
	
	
	temp = (int*)k.v3.maintenanceMode();

	cout << endl << "V3 Key PreHax : " << h3 << endl;
	cout << "V3 Key PreHax Address : " << &h3 << endl;

	
	h3 = *temp;

	cout << "V3 Key PostHax Address :" << h3 << endl;
	cout << "V3 Key PostHax : " << &h3 << endl << endl;

	//VAULT 4: (In array) Hint: use a loop and pointer arithmetics to traverse array (like key[0] to key[1]
	k.v4.diversionMode();
	
	cout << endl << "V4 Key PreHax : " << h4 << endl;
	cout << "V4 Key PreHax Address : " << &h4 << endl;

	
	temp = (int*)&(k.v4.falsekey);
	temp = temp +12;
	h4 =*temp;

	cout << "V4 Key PostHax Address :" << h4 << endl;
	cout << "V4 Key PostHax : " << &h4 << endl << endl;
	//VAULT 5: (pointer magic/arithmentic to move around struct)

	cout << "V5 Key PreHax : " << h5 << endl;
	cout << "V5 Key PreHax Address : " << &h5 << endl;
	
	temp = (int*)&k.v5->madeby;
	temp = temp + 12;
	h5 = *temp;
	
	cout << "V5 Key PostHax Address :" << h5 << endl;
	cout << "V5 Key PostHax : " << &h5 << endl << endl;
	//VAULT 6: (Using a struct equivalent of our vault6 class and reinterpret_cast) //Use the method I showed in class)
	temp = (int*)&k.v6;
	temp = temp + 6;
	
	cout << "V6 Key PreHax : " << *temp << endl;
	cout << "V6 Key PreHax Address : " << &h6 << endl;
	int zero = 0;
	*temp = static_cast<int>(zero);
	
	cout << "V6 Key PostHax Address :" << h6 << endl;
	cout << "V6 Key PostHax : " << &h6 << endl << endl;
	
	temp = 0;
	delete temp;
	temp = NULL;
	{
		//IN this case I want you to print out the original value of k.v6's key but then change it to zero.

#ifdef DEBUG
		cout << "V6 Key New Value: " << k.v6.getKey() << endl;
#endif
		h6 = 0;
	}
	h6 = 0;


	//End of Your Code
	cout << "\nStatus of Hacked:" << endl;
	cout << h0 << " " << h1 << " " << h2 << " ";
	cout << h3 << " " << h4 << " " << h5 << " " << h6 << endl;


	//Debug Solution
#ifdef DEBUG
	cout << k.v0->key << " " << k.v1.getKey() << " ";
	cout << k.v2.getKey() << " " << k.v3.getKey();
	cout << " " << k.v4.getKey() << " " << k.v5->getKey();
	cout << " " << k.v6.getKey() << endl;
#endif
	cout << endl;

	//Check if Haxed:
	if (k.iskey(h0, h1, h2, h3, h4, h5, h6)) {
		cout << "\n!!!!1337 Success!!!!\n" << endl; //if this prints you finished your homework :D
	}

	return 0;
}










	