
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <algorithm>


// BigInt utilities
class BigInt{
		std::vector<int> number;

	public:
		// constructors.
		BigInt(){};
		BigInt(const std::string& s);

		// methods
		BigInt operator +(BigInt& second);
		BigInt operator *(BigInt& second);
		BigInt operator ^(BigInt& exponent);
		BigInt addVector (std::vector<int>& left, std::vector<int>& right);
		int to_int();
		std::vector<int> get_number() const { return number;}
};


BigInt::BigInt(const std::string& s){	
	std::for_each(s.rbegin(), s.rend(), [this](char n) { 
					if (n<'0' || n>'9') std::cout<<"bad input";
	    			else this->number.push_back(n-'0');
					} );
}

BigInt BigInt::operator +(BigInt& second){
	std::vector<int> left = this->number;
	std::vector<int> right = second.number;
	if (left.size() > right.size()) right.resize(left.size());
	else left.resize(right.size());

	return addVector(left, right);
}

BigInt BigInt::addVector (std::vector<int>& left, std::vector<int>& right){
	BigInt result;
	result.number.resize(left.size());
	int carry=0, localResult=0;

	for (int i=0; i<(int)left.size(); i++){
		localResult = left[i] + right[i] + carry;
		if (localResult > 9) { 
			result.number[i] = localResult % 10;
			carry = 1;
		}
		else {
			result.number[i] = localResult;
			carry = 0;
		}
	}
	if (carry==1) result.number.push_back(1);
	return result;
}

BigInt BigInt::operator *(BigInt& second){
	BigInt result, temp;
	result.number = {0};

	for (int i=0; i < (int)second.number.size(); i++){
		int digit = second.number[i];
		temp.number = {0};
		// multiply left by right single digit
		for (; digit>0; digit--) temp = temp + *this;
		// adjust multiple of tens
		for (int inserts=i; inserts>0; inserts--) temp.number.insert(temp.number.begin(), 0);
		result = result + temp;
	}
	
	return result;
}

BigInt BigInt::operator ^(BigInt& lhs){
	int exponent = lhs.to_int();
	BigInt result;
	result.number = this->number;
	if (exponent == 0) result.number = {1};
	else {
		for(; exponent>1; exponent--) result = result * *this;
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

int main(){
	BigInt s1("1234");
	BigInt s2("44");
	BigInt r = s1 * s2;
	std::cout << r << std::endl;

	return 0;
}
