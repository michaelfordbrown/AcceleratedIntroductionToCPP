// IntroToVariadicTemplates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>
#include <iostream>
#include <vector>


template<typename T>
std::string to_string_impl(const T& t)
{
	// stringstream used to convert between strings and other numerical types. 
	std::stringstream ss;
	ss << t;
	return ss.str();
}

/*
	Variadic functions are functions (e.g. std::printf) which take a variable number of arguments.	

	To declare a variadic function, an ellipsis(...) is used as the last parameter, e.g. int printf(const char* format, ...);. 
*/
template<typename ... Param>
// to_string - Convert value to string, for every parameter passed
std::vector<std::string> to_string(const Param& ... param)
{
	// Cycle through each parameter and place resultant string into returned vector of strings
	return{ to_string_impl(param)... };
}

int main()
{
	// Create a vector of strings from the RHS constants passed as parameters to variadic template function "to_string".
	const auto vec = to_string("hello", 1, 5.3, "World", 1.3f, 1, 2, 3, 4, 5, 1000, "bob");

	std::cout << "Intro To Variadic Templates (Jason Turner)\n\n";

	/*
		Range Based FOR Loop (C++ v11)

		for(varType var: range_r)

		assign every element in range_r to var
	*/

	for (const auto &o : vec)
	{
		std::cout << o << std::endl;
	}
    return 0;
}

