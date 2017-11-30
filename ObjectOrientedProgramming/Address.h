#pragma once
class Address
{
	// PUBLIC access provides unlimited access
	public:
		int house_number;
		string street_name;
		string city;

		// Constructor for Address CLASS
		Address(int house_number, string const& street_name, 
			string const& city)
			// Set member functions
			:house_number(house_number), street_name(street_name), city(city)
		{

		}

};

