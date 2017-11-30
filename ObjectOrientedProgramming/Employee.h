#pragma once
#include "Person.h"
class Employee : public Person
{
	//  FRIEND declaration appears in a class body and grants a function or another class access to private and protected members of the class where the friend declaration appears. 
	friend class EmpFactory;

	// By default CLASS access specifier is PRIVATE (no need to state but does not hurt)
	private:
		int taxId;

	// PUBLIC access provides unlimited access
	public:
		// Replacement of default constructor that set default values
		Employee() : Person(0, "", 0) {}

		// Replacement of default constructor that uses Person BASE CLASS constructor
		// Also set member variable department
		Employee(int age,  string const& name, int sex,
			string department = string())
			: Person(age, name, sex),
			 department(department)
		{
			// Set PROTECTED BASE PERSON social security number variable 
			ssn = 0;
		}

		// OVERRIDE, change function from derived CLASS (defined in .cpp file)
		void greet() override;

		// PUBLIC member variable
		string department;
};

