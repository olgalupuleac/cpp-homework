#include "EmployeesArray.h"
#include <cstring>
#include <cstdlib>

EmployeesArray::EmployeesArray() : _size(0), _cp(1) {
	_employees = new Employee*[1];
}

EmployeesArray::EmployeesArray(int32_t n) : _size(0), _cp(n) {
	_employees = new Employee*[n];
}

EmployeesArray::~EmployeesArray() {
	for (int i = 0; i < _size; i++) delete _employees[i];
	delete[] _employees;
}

int EmployeesArray::total_salary() const {
	int res = 0;
	for (int i = 0; i < _size; i++) res += _employees[i]->salary();
	return res;
}

void EmployeesArray::add(const Employee *e) {
    if (_cp <= _size) {
        Employee** new_employees = new Employee*[2 * _cp];
        memcpy(new_employees, _employees, _size * sizeof(Employee*));
        swap(_employees, new_employees);
        _cp *= 2;
        delete[] new_employees;
    }
    _employees[_size++] = (Employee*) e;

}

ostream& operator<<(ostream& os, EmployeesArray& e) {
	for (int i = 0; i < e._size; i++) {
		os << i+1 << ". " << e._employees[i];
	}
	return os << "== Total salary: " << e.total_salary() << '\n' << endl;
}

istream& operator>>(istream& is, EmployeesArray& e) {
	int type;
	is >> type;
	Employee* new_person = NULL;
	if (type == 1) {
		new_person = (Employee*) new Developer;
	}
	if (type == 2) {
		new_person = (Employee*) new SalesManager;
	}
	is >> new_person;
	e.add(new_person);
	return is;
}

ofstream& operator<<(ofstream& ofs, EmployeesArray& e) {
	ofs.write((char*)&(e._size), 4);
	for (int i = 0; i < e._size; i++) {
		ofs << e._employees[i];
	}
	return ofs;
}

ifstream& operator>>(ifstream& ifs, EmployeesArray& e) {
	int32_t n;
	ifs.read((char*) &n, 4);
	for (int i = 0; i < n; i++) {
		int32_t type;
		ifs.read((char*)&type, 4);
		Employee* new_person;
		if (type == 1) {
			new_person = (Employee*) new Developer;
		}
		else {
			new_person = (Employee*) new SalesManager;
		}
		ifs >> new_person;
		e.add(new_person);
	}
	return ifs;
}
