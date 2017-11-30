#pragma once

class EmpFactory
{
	// PUBLIC access provides unlimited access
	public:
		Employee makeEmp(int id)
		{
			Employee emp;

			// Access PRIVATE member variable from Employee CLASS
			emp.taxId = id;

			return emp;
		}
};