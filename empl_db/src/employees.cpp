#include "employees.h"
#include <string>
#include <cstring>

Employee::Employee() {
	_name = NULL;
}

Employee::~Employee() {
	delete[] _name;
}

ostream& operator<<(ostream& os, Employee *e) {
	return e->print(os);
}

istream& operator>> (istream& is, Employee *e) {
	return e->read(is);
}

ofstream& operator<<(ofstream& ofs, Employee *e) {
	return e->save(ofs);
}

ifstream& operator>> (ifstream& ifs, Employee *e) {
	return e->load(ifs);
}

ostream& Developer::print(ostream& os) {
	return os << "Developer\nName: " << string(_name) \
		<< "\nBase Salary: " << _base_salary \
		<< "\nHas Bonus: " << (_has_bonus ? "+" : "-") << endl;
}

ostream& SalesManager::print(ostream& os) {
	return os << "Sales Manager\nName: " << string(_name) \
		<< "\nBase Salary: " << _base_salary \
		<< "\nSold items: " << _sold_nm \
		<< "\nItem price: " << _price << endl;
}

istream& Developer::read(istream& is) {
	string name;
    is >> name >> _base_salary >> _has_bonus;
	delete[] _name;
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());
	return is;
}

istream& SalesManager::read(istream& is) {
	string name;
	is >> name >> _base_salary >> _sold_nm >> _price;
	delete[] _name;
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());
	return is;
}

ifstream& Developer::load(ifstream& ifs) {
	string name;
	getline(ifs, name, (char) 0);
	delete[] _name;
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());
	ifs.read((char*) &_base_salary, 4);
	ifs.read((char*) &_has_bonus, sizeof(bool));
	return ifs;
}

ifstream& SalesManager::load(ifstream& ifs) {
	string name;
	getline(ifs, name, (char)0);
	delete[] _name;
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());
	ifs.read((char*)&_base_salary, 4);
	ifs.read((char*)&_sold_nm, 4);
	ifs.read((char*)&_price, 4);
	return ifs;
}

ofstream& Developer::save(ofstream& ofs) {
	int32_t type = 1;
	ofs.write((char*) &type, 4);
	ofs.write(_name, strlen(_name) + 1);
	ofs.write((char*) &_base_salary, 4);
	ofs.write((char*)&_has_bonus, sizeof(bool));
	return ofs;
}

ofstream& SalesManager::save(ofstream& ofs) {
	int32_t type = 2;
	ofs.write((char*)&type, 4);
	ofs.write(_name, strlen(_name) + 1);
	ofs.write((char*)&_base_salary, 4);
	ofs.write((char*)&_sold_nm, 4);
	ofs.write((char*)&_price, 4);
	return ofs;
}
