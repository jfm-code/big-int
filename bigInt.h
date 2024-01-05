//BigInt.h
#pragma once
#include <iostream>
#include <string> //used for to_string function
#include <cctype> //used for isdigit function 
#include <vector> //used for implement the sum_total as a vector

using namespace std;

class BigInt
{
public:
	BigInt(); 
	// Initializes the BigInt to zero.
	BigInt(int x); 
	//Initializes the BigInt to have the same value as x
	explicit BigInt(string x);
	//Initalizes the BigInt to have the value of the given string BUT
	//must check that the string is valid or exit(1) otherwise.
	friend ostream& operator<<(ostream& out, const BigInt& right);
	friend BigInt operator+(BigInt left, BigInt right);
	friend BigInt operator-(BigInt left, BigInt right);
	friend BigInt operator*(BigInt left, BigInt right);
	friend BigInt operator/(BigInt left, BigInt right);
	friend BigInt operator%(BigInt left, BigInt right);
	friend bool operator<(BigInt left, BigInt right);
	friend bool operator>(BigInt left, BigInt right);
	friend bool operator==(BigInt left, BigInt right);
	bool isValidString(string s, bool& checkNegative);

private:
	string data;
	bool isNegative;
};

string reverse(string s);
string addition(string left, string right);
string substraction(string left, string right);
