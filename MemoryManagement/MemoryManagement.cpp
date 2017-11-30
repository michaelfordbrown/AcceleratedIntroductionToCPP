// MemoryManagement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Address
{
public:
	string city;

	// Create Address instance on the STACK
	Address(string const& city) : city(city)
	{
		cout << "Address (" << city << ") created" << endl;
	}

	~Address()
	{
		cout << "Address (" << city << ") destroyed" << endl;
	}
};

class Person
{
public:
	Address *address;

	Person(string const& city)
	{
		// Create Person instance on the HEAP (new allocation)
		try
		{
			address = new Address(city);
			cout << "Person at " << city << " created" << endl;
		}
		catch (bad_alloc& e)
		{
			cerr << "Error: " << e.what() << endl;
		}
	}

	~Person()
	{
		delete address;
		cout << "Person destroyed" << endl;
	}
};

class Person2
{
private:
	// Put constructors and destructor out of reach, within PRIVATE area
	Person2() {}
	Person2(const Person2& _) {}
	~Person2() {}

	// Reference counter showing how many instances are sharing Person2 object
	int ref_count;
public:
	// Force instance to be created on the HEAP
	static Person2* create()
	{
		Person2* p = nullptr;
		try
		{
			p = new Person2;
			
			// Initialize reference count when instance created
			p->ref_count = 1;

			return p;
		}
		catch (bad_alloc& e)
		{
			cout << "ERROR: " << e.what() << endl;
		}
	}

	// Update reference counter when Person2 variable shared
	void add_ref()
	{ 
		ref_count++; 
	}

	// Decrement reference counter, when sharing stops
	void release()
	{
		if (--ref_count == 0)
			// Re-allocate memory to HEAP
			delete this;
	}
};

int main()
{
	Address* a;

	{
		Person p("New York");
		// Sharing "p" address with "a" problematic as "p" address can be destroyed while "a" still using
		a = p.address;
	}

	getchar();
    return 0;
}

