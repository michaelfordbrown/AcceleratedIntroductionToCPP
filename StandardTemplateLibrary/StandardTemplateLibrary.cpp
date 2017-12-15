// StandardTemplateLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Containers

// int sum(array<int, 5> values) - Sum signature means fixed size array
// use template to allow for varying sized array
template<int n>
int sum(array<int, n> values)
{
	int result = 0;
	for (int value : values)
		result += value;
	return result;
}

int main()
{
	//ARRAY
	cout << "\nARRAY Container\n";

	array<int, 5> numbers = { { 1, 2, 3, 4, 5 } };
	array<int, 3> more_numbers = { { 1, 3, 5 } };

	cout << sum(numbers) << endl;
	cout << sum(more_numbers) << endl;

	//VECTOR
	cout << "\nVECTOR Container\n";

	try {
			vector<float> values{ 1, 2, 3 };
			values.push_back(4.5f); // append value at the end of the container
			values.push_back(5.0f); // append value at the end of the container
			values.pop_back(); // take end value out of container (5.0) and reduce size by one.

				// _DEBUG_ERROR("vector subscript out of range");
				// float v = values[5];

				// vector::at - Access Element returns a reference to the element at position n in the vector.
				// It throws out_of_range if n is out of bounds.
				float u = values.at(5);

				// Obtain and display the number of elements in container
				cout << "There are " << values.size() << " values" << endl;
				// for .. each loop through vector assigning iterative value to value
				for (float value : values)
					cout << value << "\t";
				cout << endl;
			}
			catch (const std::out_of_range& oor)
			{
				std::cerr << "Out of Range Error: " << oor.what() << std::endl;
			}
	
	//SET
	cout << "\nSET Container\n";

	string speech("to be or not to be, that is the question");
	cout << "Speech = " << speech << endl;
	cout << "Characters in Speech = \n";
	set<char> letters;
	// for ... each char (c) in speech
	for (char c : speech)
	{
		// isalpha  - Checks if the given character is an alphabetic character as classified by the currently installed C locale.
		// insert - Extends the container by inserting new unique elements, effectively increasing the container size by the number of elements inserted. 
		if (isalpha(c)) letters.insert(c);
	}

	for (char c : letters)
		cout << c << "\t";
	cout << endl;

	//MAP
	cout << "\nMAP Container\n";

	map<char, int> histogram;

	for (char c : speech)
	{
		// add (c) as a key in a sorted manner then increment associated int count
		if (isalpha(c)) histogram[c]++;
	}

	cout << "Character count for Speech =\n";
	for (auto u : histogram)
		//display key (char) and count (int)
		cout << u.first << "-" << u.second << "\t";
	cout << endl;

	getchar();
	return 0;
}


