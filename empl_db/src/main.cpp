#include <iostream>
#include <string>
#include "EmployeesArray.h"

using namespace std;

int main() {
	string mode;
	cin >> mode;
	EmployeesArray employees;
	while (mode != "exit") {
		if (mode == "add") {
			cin >> employees;
		}
		if (mode == "list") {
			cout << employees;
		}
		if (mode == "load") {
			string filename;
			cin >> filename;
			ifstream ifs(filename, ifstream::binary);
			ifs >> employees;
		}
		if (mode == "save") {
			string filename;
			cin >> filename;
			ofstream ofs(filename, ofstream::binary);
			ofs << employees;
		}
		cin >> mode;
	}
	return 0;
}