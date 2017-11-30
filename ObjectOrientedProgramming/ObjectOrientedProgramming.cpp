// ObjectOrientedProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Address.h"
#include "Person.h"
#include "Employee.h"
#include "EmpFactory.h"

#define FILENAME "ObjectOrientedProgramming "

string db(long line)
{
	return (FILENAME + to_string(line) + " ");
};

int main()
{
	cout << "Object  Oriented Programming\n";

	// Instance allocated on the stack
	Person p(30, "Jane Doe", Person::female);

	//Instance allocated on the heap
	Person *p2 = new Person(25, "John Doe", Person::male);

	p2->greet();
	
	// Constants and Static members
	p.sex = Person::male;
	int le = Person::getLifeExpectancy();
	cout << le << endl;

	// Constructors and Destructor
	Person *p3 = new Person(44, "Jack Jones", Person::male);
	auto* address = new Address(123, "Oxford Street", "London");
	p3->address = address;

	p3->greet();

	// Copying
	Person p4(*p3);
	p3->address->city = "Exeter";
	cout << p4.address->city << endl;

	Person p5 = *p3;

	// Inheritance
	Employee e(33, "Chris", Person::male, "Engineering");
	
	// Lambda function
	auto u = [](const Person& p)
	{
		cout << p.name << endl;
	};
	u(e);

	Person &pr = e;

	// Unchecked casting of person type to employee type
	Employee& er = static_cast<Employee&>(pr);
	cout << er.department << endl;

	pr.greet();

	// NOTE: Has no employee information
	Person& pr2 = p; 
	
	// Checked casting of person type to employee type
	try {
		Employee& er2 = dynamic_cast<Employee&>(pr2);
		cout << er2.department << endl;
	}
	catch (const bad_cast& e)
	{
		cout << db(__LINE__) << "Cannot cast this!" << endl;
	}

	// Casting pointers with checking
	Person* pp = &p;
	Employee *ep = dynamic_cast<Employee*>(pp);
	if (ep)
		cout << ep->department << endl;
	else
		cout << db(__LINE__) << "Failed To Cast Pointer" << endl;

	// Clean up heap allocated objects
	delete p2;
	delete p3;

	getchar();
    return 0;
}

