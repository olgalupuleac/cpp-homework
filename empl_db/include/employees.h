#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <fstream>
using namespace std;

class Employee {
public:
	Employee();
	virtual ~Employee();
	virtual int salary() const = 0;
	friend ostream& operator<<(ostream& os, Employee *e);
	friend istream& operator>> (istream& is, Employee *e);
	friend ofstream& operator<<(ofstream& ofs, Employee *e);
	friend ifstream& operator>> (ifstream& ifs, Employee *e);
protected:
	virtual ostream& print(ostream& os) = 0;
	virtual istream& read(istream& is) = 0;
	virtual ofstream& save(ofstream& ofs) = 0;
	virtual ifstream& load(ifstream& ifs) = 0;
	char *_name;
private:
	Employee(const Employee& other) {}
	void operator=(const Employee& other) {}
};

class Developer: public Employee {
public:
	int salary() const {
		int salary = _base_salary;
		if (_has_bonus) { salary += 1000; }
		return salary;
	}
	ostream& print(ostream& os);
	istream& read(istream& is);
	ofstream& save(ofstream& ofs);
	ifstream& load(ifstream& ifs);
private:
	int32_t _base_salary;
	bool _has_bonus;
};

class SalesManager : public Employee {
public:
	int salary() const {
		return (int) (_base_salary + _sold_nm * _price * 0.01);
	}
	ostream& print(ostream& os);
	istream& read(istream& is);
	ofstream& save(ofstream& ofs);
	ifstream& load(ifstream& ifs);
private:
	int32_t _base_salary;
	int32_t _sold_nm, _price;
};

#endif
