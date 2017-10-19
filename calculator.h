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
		BigInt(): number{0} {}
		BigInt(const std::string& s);

		int to_int();
		std::vector<int> get_number() const { return number;}
        void set_number(std::vector<int> v) { number = v;}
};

std::ostream& operator<< (std::ostream& os, const BigInt& bigInt);
BigInt operator +(BigInt& first, BigInt& second);
BigInt operator *(BigInt& first, BigInt& second);
BigInt operator ^(BigInt& first, BigInt& exponent);
BigInt addVector (std::vector<int>& left, std::vector<int>& right);


// Functions for parsing and the calculator.
BigInt addition(const std::vector<std::string>& words);
BigInt multiplication(const std::vector<std::string>& words);
BigInt exponentiation(const std::vector<std::string>& words);
void tokenizeLine();
void showDocumentation();
void outputCalculation(const std::vector<std::string>& words, std::string line);

#endif
