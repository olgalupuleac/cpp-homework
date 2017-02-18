#pragma once
#include "employees.h"

class EmployeesArray {
public:
	EmployeesArray();
	EmployeesArray(int32_t n);
	~EmployeesArray();
	void add(const Employee *e);
	int total_salary() const;
	friend ostream& operator<<(ostream& os, EmployeesArray& e);
	friend istream& operator>> (istream& is, EmployeesArray& e);
	friend ofstream& operator<<(ofstream& ofs, EmployeesArray& e);
	friend ifstream& operator>> (ifstream& ifs, EmployeesArray& e);
private:
	Employee **_employees;
	int32_t _size;
	int32_t _cp;
	EmployeesArray(const EmployeesArray& other) {}
	void operator=(const EmployeesArray& other) {}
};
