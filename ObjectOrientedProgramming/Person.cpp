#include "stdafx.h"
#include "Address.h"
#include "Person.h"

// Initial constructor
Person::Person(int age, string name, int sex)
// Set base member variables
: age(age), name(name), sex(sex)
{
	// Assume that address (new additional member field) field not set
	address = nullptr;
}

// Second constructor that includes new address field by appending from initial constructor
Person::Person(int age, string name, int sex,
	int house_number, string street_name, string city)
	: Person(age, name, sex)
{
	// Check if address variable already defined
	if (address != nullptr)
		delete address;

	try
	{
		// NEW used to allocate heap memory by returned address
		address = new Address(house_number, street_name, city);
	}
	// std::bad_alloc is the type of the object thrown as exceptions by the allocation functions to report failure to allocate storage.
	catch (const bad_alloc& e)
	{
		cout << "Bad Memory Allocation for Address member variable (" << e.what()<< "\n";
	}

}

Person::~Person()
{
	// Check if address member variable present before return memory to the heap
	if (address != nullptr)
	{
		// DELETE - Deallocates a block of memory.
		delete address;

		// Clear address pointer to signify no address present
		address = nullptr;
	}
}

void Person::greet()
{
	//Reference to current instance (this)
	cout << "Greetings my name is " << this->name
		<< " and I am " << this->age << " years old."
		<< endl;

	// Check if address member variable present before streaming out details
	if (address)
	{
		cout << "I live at " << this->address->house_number << " "
			<< this->address->street_name << ", "
			<< this->address->city << endl;
	}
}

// PUBLIC function that gets member variable
int Person::getLifeExpectancy()
{
	return lifeExpectancy;
}

int Person::lifeExpectancy = 80;