/*************************************************************************
Fabrice Lacout
ID: 5652857
project2 calculator/ functions definition

**************************************************************************/


#include "calculator.h"

// All BigInt utilities.
BigInt::BigInt(const std::string& s){	
	std::for_each(s.rbegin(), s.rend(), [this](char n) { 
					if (n<'0' || n>'9') std::cout<<"bad input: number should only contain digits";
	    			else this->number.push_back(n-'0');
					} );
}

BigInt operator +(BigInt& first, BigInt& second){
	std::vector<int> left = first.get_number();
	std::vector<int> right = second.get_number();
	if (left.size() > right.size()) right.resize(left.size());
	else left.resize(right.size());

	return addVector(left, right);
}

BigInt addVector (std::vector<int>& left, std::vector<int>& right){
	BigInt res;
    std::vector<int> result;
	result.resize(left.size());
	int carry=0, localResult=0;

	for (int i=0; i<(int)left.size(); i++){
		localResult = left[i] + right[i] + carry;
		if (localResult > 9) { 
			result[i] = localResult % 10;
			carry = 1;
		}
		else {
			result[i] = localResult;
			carry = 0;
		}
	}
	if (carry==1) result.push_back(1);
    res.set_number(result);
	return res;
}

BigInt operator *(BigInt& first, BigInt& second){
	BigInt result("0");

	for (int i=0; i < (int)second.get_number().size(); i++){
		int digit = second.get_number()[i];
		BigInt temp("0");
		// multiply left by a single digit of right
		for (; digit>0; digit--) temp = temp + first;
		// adjust multiple of tens relative to the position of digit.
        std::vector<int>  tenths = temp.get_number();
		for (int inserts=i; inserts>0; inserts--) {
            tenths.insert(tenths.begin(),0); 
        }
        temp.set_number(tenths);
		result = result + temp;
	}
	
	return result;
}

BigInt operator ^(BigInt& first, BigInt& expo){
	int exponent = expo.to_int();
	BigInt result;
	result.set_number(first.get_number());
	if (exponent == 0) result.set_number({1});
	else {
		for(; exponent>1; exponent--) result = result * first;
	}
	return result;
}

int BigInt::to_int(){
	int result=0, temp=0;
	for (int i=0; i<(int)this->number.size(); i++){
		temp = this->number[i] * pow(10, i);
		result += temp;
	}
	return result;
}
	

std::ostream& operator<< (std::ostream& os, const BigInt& bigInt) {
	std::vector<int> v = bigInt.get_number();
	for (int i=((int)v.size()-1); i>=0; i--) os << v[i];
	return os;
}

/**********************************************************************************************/
// functions of parsing.
void tokenizeLine(){
    std::string line;
    std::string word;

    while ( !std::cin.eof() ){
        std::vector<std::string> words;
		std::getline(std::cin, line);
		if (line[0]=='\0' || line[0]=='#' ) continue; // continue if comment or no input.
    	std::istringstream iss(line);
    	while (iss >> word) words.push_back(word);
		if (words.size()>0) outputCalculation(words, line);
    }
}

void outputCalculation(const std::vector<std::string>& words, std::string line){
    if (verbose){
        if (words[0] == "+") std::cout <<line <<" = "<< addition(words) << std::endl;
		else if (words[0] =="*") std::cout <<line<<" = "<< multiplication(words) << std::endl;
		else if (words[0] =="^") std::cout <<line<<" = "<< exponentiation(words) << std::endl;
		else if (words[0] == "quit") exit(0);
		else std::cout << "unrecognized input try again\n" << std::endl;
    }
    else{
        if (words[0] == "+") std::cout << addition(words) << std::endl;
		else if (words[0] =="*") std::cout << multiplication(words) << std::endl;
		else if (words[0] =="^") std::cout << exponentiation(words) << std::endl;
		else if (words[0] == "quit") exit(0);
		else std::cout << "unrecognized input try again\n" << std::endl;
    }
}

BigInt addition (const std::vector<std::string>& words) {
    BigInt result("0");
    for (int i=1; i< (int)words.size(); i++){
		BigInt operand(words[i]);
		result = result + operand;
	}
	return result;
}

BigInt multiplication(const std::vector<std::string>& words){
    BigInt result("1");
    for (int i=1; i< (int)words.size(); i++){
		BigInt operand(words[i]);
		result = result * operand;
	}
	return result;
}

BigInt exponentiation(const std::vector<std::string>& words){
	// i has to be define outside the for loop, in case the first
	// result = std::stoi() raise an exception.
	int i =1;
	BigInt result(words[i]);
    for (i=2; i< (int)words.size(); i++){
		BigInt operand(words[i]);
		result = result ^ operand;
	}
    return result;
}


void showDocumentation(){
// use a string literal to std::cout a long string.
std::cout << R"(
	Usage: ˜/bin/calc [-h] [-v]
	to run the program interactively. To run using standard input:
	echo ’equation’ | ./calc
	where ’equation’ is a single prefix notation equation, i.e. ’+ 2 2’
	or:
	˜/bin/calc < input_file.txt
	where ’input_file.txt’ contains prefix notation equations,
	one per line
	Options:
	-h Show this text
	-v Set a verbose output flag. Default = false.
	Running with no input from standard in enters ’interactive mode’.
	Equations can be entered one per line.
	The program runs until ’quit’ is the first word on a line or
	EOF is reached.
	)";
}
