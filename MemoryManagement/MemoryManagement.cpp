// MemoryManagement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Address
{
public:
	string city;

	// Default constructor
	Address() {}

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

class Person3
{
public:
	shared_ptr<Address> address;

	Person3(string const& city)
	{
		address = make_shared<Address>(city);
		cout << "Created person" << endl;
	}

	~Person3()
	{
		cout << "Destroyed person" << endl;
	}
};
void inc(int& x) { x++; }

int meaningOfLife() { return 42; }

void move_rvalue()
{
	//int a = 0;
	//inc(a);

	//inc(1); not possible

	// RValue reference of meaningOf
	// meaningOfLife() = 5;
	// int& x = meaningOfLife();

	// RValue reference of meaningOfLife
	// int&& y = meaningOfLife();
	//cout << y << endl;

	
	Address book[100];

	// Address occupying 2 locations in memory
	//book[55] = Address("Paris");

	// move accepts either an lvalue or rvalue argument, and return it as an rvalue without triggering a copy construction 
	book[55] = move(Address("Paris"));

}

// std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope. 
unique_ptr<Address> create_address(string const& city)
{
	//return unique_ptr<Address>(new Address(city));
	// OR
	// make_unique - Constructs an object of type T and wraps it in a std::unique_ptr
	return make_unique<Address>(city);
}

int main()
{
	//move_rvalue();

	/*Address* a;

	{
		Person p("New York");
		// Sharing "p" address with "a" problematic as "p" address can be destroyed while "a" still using
		a = p.address;
	}
	*/

	/*
	// Unique Pointers (non sharing)
	auto a = create_address("Paris");
	a->city = "New " + a->city;

	cout << "Renamed city: " << a->city << endl;

	// auto v(a); // Copy constructor of unique_ptr has been marked "delete".
	*/

	// std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. Several shared_ptr objects may own the same object. 

	shared_ptr<Address> a;
	{
		Person3 p("Paris");
		a = p.address;
	}

	// Shared pointer has not died although the Person3 has been destroyed
	cout << a->city << endl;

	//
	getchar();
    return 0;
}

