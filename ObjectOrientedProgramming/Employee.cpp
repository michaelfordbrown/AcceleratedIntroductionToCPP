#include "stdafx.h"
#include "Address.h"
#include "Person.h"
#include "Employee.h"

// OVERRIDE BASE CLASS greet() function
void Employee::greet()
{
	// Call original BASE CLASS greeting
	Person::greet();

	// Append department name to standard greeting
	cout << "By the way, I work in " << department << endl;
}
