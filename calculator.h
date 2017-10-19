/************************************* 
Fabrice Lacout
ID: 5652857
project2 calculator/ headers
***************************************/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <algorithm>

extern bool verbose;

// BigInt utilities
class BigInt{
		std::vector<int> number;

	public:
		BigInt(){};
		BigInt(const std::string& s);

		BigInt operator +(BigInt& second);
		BigInt operator *(BigInt& second);
		BigInt operator ^(BigInt& exponent);
		BigInt addVector (std::vector<int>& left, std::vector<int>& right);
		int to_int();
		std::vector<int> get_number() const { return number;}
};

std::ostream& operator<< (std::ostream& os, const BigInt& bigInt);

// Functions for parsing.
BigInt addition(const std::vector<std::string>& words);
BigInt multiplication(const std::vector<std::string>& words);
BigInt exponentiation(const std::vector<std::string>& words);
void tokenizeLine();
void showDocumentation();
void outputCalculation(const std::vector<std::string>& words, std::string line);

#endif
