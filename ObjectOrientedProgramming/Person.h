#pragma once
class Person
{
	// By default CLASS access specifier is PRIVATE (no need to state but does not hurt)
	private:
		//  STATIC means all instances of the class share this member variable
		static int lifeExpectancy;

	// PROTECTED limits access within CLASS and those CLASS's derived from BASE CLASS
	protected:
		int ssn;

	// PUBLIC access provides unlimited access
	public:
		// CONST used as alternative to #define to define constant values
		const static int female = 0;
		const static int male = 1;

		int age;
		string name;
		int sex;

		// Any construction of class pointed to needs heap memory (e.g. new() and delete() operations)
		Address *address;

		// Initial Person definition constructor (override default constructor)
		Person(int age, string name, int sex);

		// Second Person definition constructor that has been extended to include CLASS Address
		Person(int age, string name, int sex,
			int house_number, string street_name,
			string city);

		// Person deconstructor (override default) that handles memory allocation (DELETE operations)
		~Person();

		// Person copy function (override default) that uses Person reference
		Person(const Person& p)
			// Set CLASS member variables from referenced parameter "p"
			: age(p.age), name(p.name), sex(p.sex)
		{
			// AUTO will evaluate to type determined on RHS
			auto* a = p.address;

			try
			{
				// THIS used to refer to current CLASS
				// NEW used to allocate heap memory by returned address
				this->address = new Address(
					a->house_number,
					a->street_name,
					a->city);
			}
			// std::bad_alloc is the type of the object thrown as exceptions by the allocation functions to report failure to allocate storage.
			catch (const bad_alloc& e)
			{
				cout << "Bad Memory Allocation for member variable address (" << e.what() << ")\n";
			}
		}

		// VIRTUAL function is a member function that you expect to be redefined in derived classes.
		virtual void greet();

		//  STATIC function needed when working with STATIC member variable
		static int getLifeExpectancy();
};

