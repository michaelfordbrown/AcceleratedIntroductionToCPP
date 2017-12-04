// Templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include <array>
#include <vector>
#include <complex>


/*
	template <class T1, class T2> struct pair;

	Pair of values
		This class couples together a pair of values, which may be of different types (T1 and T2). 
		The individual values can be accessed through its public members first and second.

		T1	Type of member first, aliased as first_type.
		T2	Type of member second, aliased as second_type.
*/

/*
	The typedef specifier, when used in a declaration's decl-specifier-seq, specifies that the declaration is a typedef declaration, and declares typedef-names rather than functions or objects. It may declare one or many identifiers on the same line, it may declare array and function types, pointers and references, class types, etc. Every identifier introduced in this declaration becomes a typedef-name, which is a synonym for the type of the object or function that it would become if the keyword typedef were removed. 
*/

typedef std::pair<int, int> int_pair;

int_pair sum_and_product_int(int a, int b)
{
	return int_pair(a + b, a *b);
}

/*
	Class template std::tuple is a fixed-size collection of heterogeneous values. It is a generalization of std::pair.
*/

typedef std::tuple<int, int, int> trie;
trie sum_product_avg_int(int a, int b, int c)
{
	trie t{ a + b + c, a * b * c, (a + b + c) / 3 };
	return t;
}

template<typename T1, typename T2, typename T3>
struct triple
{
	typedef T1 first_result_type;
	typedef T2 second_result_type;
	typedef T3 third_result_type;

	T1 first;
	T2 second;
	T3 third;

	triple(const T1& first, const T2& second, const T3& third)
		: first(first), second(second), third(third) 
	{

	}
};

void consuming_templates()
{
	int a = 2, b = 3, c = 4;

	std::cout << "\nConsuming Templates\n";

	std::cout << "Values are a = " << a << " b = " << b << " c = " << c << std::endl;

	auto sum_result = sum_and_product_int(a, b);
	std::cout << "Pair Template using first and second (int): sum = " << sum_result.first <<
		" product = " << sum_result.second << std::endl;

	std::cout << "Pair Template using get<i> (int): sum = " << std::get<0>(sum_result) <<
		" product = " << std::get<1>(sum_result) << std::endl;

	auto prod_result = sum_product_avg_int(a, b, c);
	std::cout << "Tuple Template  (int): sum = " << std::get<0>(prod_result) <<
		" product = " << std::get<1>(prod_result) <<
		" average = " << std::get<2>(prod_result) <<
		std::endl;
	
}

// TEMPLATE FUNCTIONS

/*
Function templates

Function templates are special functions that can operate with generic types. This allows us to create a function template whose functionality can be adapted to more than one type or class without repeating the entire code for each type.
*/
template<typename T1, typename T2, typename T3>
triple<T1, T2, T3> sum_product_avg_alltypes(const T1& a, const T2& b, const T3& c)
{
	// first_result_type, second_result_type and third_result_type used to align types of operand to meet result type
	return triple<T1, T2, T3>(a + triple<T1, T2, T3>::first_result_type(b) + triple<T1, T2, T3>::first_result_type(c),
		triple<T1, T2, T3>::second_result_type(a) * b * triple<T1, T2, T3>::second_result_type(c),
		(triple<T1, T2, T3>::third_result_type(a) + triple<T1, T2, T3>::third_result_type(b) + c) / triple<T1, T2, T3>::third_result_type(3));
}

void template_functions()
{
	int a = 2;
	double b = 3.0;
	float c = 4.0f;
	
	std::cout << "\nTemplate Functions\n";
	std::cout << "Values are a = " << a << " b = " << b << " c = " << c << std::endl;

	auto result = sum_product_avg_alltypes(a, b, c);
	std::cout << "Triple Template: sum = " << result.first <<
		" product = " << result.second <<
		" average = " << result.third <<
		std::endl;
}

// SPEICALIZATION

/*
Template specialization needed when necessary to define a different implementation for a template when a specific type is passed as template parameter, we can declare a specialization of that template.
*/

/*
A complex number is a number that can be expressed in the form a + bi, where a and b are real numbers, and i is a solution of the equation x2 = −1, which is called an imaginary number because there is no real number that satisfies this equation. 

For the complex number a + bi, a is called the real part, and b is called the imaginary part. Despite the historical nomenclature "imaginary", complex numbers are regarded in the mathematical sciences as just as "real" as the real numbers, and are fundamental in many aspects of our description of the natural world.
*/
typedef std::complex<double> cd;
typedef triple<cd, cd, cd> cdt;

// sum_product_avg_alltypes defined with complex number signature
template<> cdt sum_product_avg_alltypes(const cd& a, const cd& b, const cd& c)
{
	// filter down to the "real" side of the complex numbers
	auto result = sum_product_avg_alltypes(a.real(), b.real(), c.real());
	return cdt(result.first, result.second, result.third);
}

void template_specialization()
{
	// define three complex numbers
	cd a(2, 3), b(3, 4), c(4, 5);
	
	std::cout << "\nTemplate Specialization\n";

	std::cout << "sum_product_avg_alltypes function template has been updated to add real type of complex numbers . . \n";

	auto result = sum_product_avg_alltypes(a, b, c);
	std::cout << result.first << ", " << result.second
		<< ", " << result.third << std::endl;
}

// VARIADIC TEMPLATES

/*
	Accommodate single parameter sum
*/
template <typename T>
T sum(T t) { return t; }

/*
Variadic functions are functions (e.g. std::printf) which take a variable number of arguments.

To declare a variadic function, an ellipsis(...) is used as the last parameter, e.g. int printf(const char* format, ...);.
*/
template<typename T, typename ...U>
// sum - template "adds" one or multiple parameters
// decltype - Inspects the declared type of an entity or the type and value category of an expression. 
auto sum(T t, U ...u) -> decltype(t + sum(u...))
{
	return t + sum(u...);
}

void variadic_templates()
{
	std::cout << "\nVariadic Templates\n";
	std::cout << sum(1, 2.5, 3, 4) << std::endl;
	std::cout << sum(std::string("abra"), std::string("cadabra")) << std::endl;
}

// METAPROGRAMING
template <int n> struct Factorial
{
	enum {value = n * Factorial<n-1>::value};
};

template <> struct Factorial<0>
{
	enum { value = 1 };
};

/*
	Metaprograming

	Template metaprogramming (TMP) is a metaprogramming technique in which templates are used by a compiler to generate temporary source code, which is merged by the compiler with the rest of the source code and then compiled. The output of these templates include compile-time constants, data structures, and complete functions. The use of templates can be thought of as compile-time execution. 
*/
void metaprogramming()
{
	std::cout << "\nMetaprograming\n";

	int x = Factorial<4>::value;
	int y = Factorial<0>::value;

	std::cout << "See source code for results!\n";
}

int main()
{

	std::cout << "Templates\n";

	consuming_templates();
	template_functions();
	template_specialization();
	variadic_templates();
	metaprogramming();

	getchar();
    return 0;
}

