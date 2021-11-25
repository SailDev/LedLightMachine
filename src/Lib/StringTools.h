#pragma once
#include <sstream>
#include <string>

using namespace std;

/*
 * std::to:string does not compile,
 * so we use this woraround.
 */
class StringTools
{
public:
	string ToString(double number)
	{
		ostringstream tmp;
		tmp << number;
		return tmp.str();
	}
	
	string ToString(long double number)
	{
		ostringstream tmp;
		tmp << number;
		return tmp.str();
	}

	string ToString(unsigned long number)
	{
		ostringstream tmp;
		tmp << number;
		return tmp.str();
	};

	string ToString(int number)
	{
		ostringstream tmp;
		tmp << number;
		return tmp.str();
	};
};
