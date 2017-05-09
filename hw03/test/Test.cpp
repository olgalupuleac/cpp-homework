#include <iostream>
#include "Test.h"


std::unordered_set<std::string> Test::testNames;
std::unordered_set<std::string> Test::failedTestNames;

void Test::check(bool expr, const char *func, const char  *filename, uint64_t lineNum) {
	std::string func_name(func);
	testNames.insert(func_name);
	
	if (!expr) {
		failedTestNames.insert(func_name);
		std::cout << "test failed: " << func << " in " << filename << ":" << lineNum << std::endl;
	}
}

void Test::showFinalResult() {
	if (failedTestNames.empty()) {
		std::cout << "All tests passed.\n";
	}
	else {
		std::cout << "Failed " << failedTestNames.size() << " of " << testNames.size() << " tests.\n";
	}
}

bool Test::failed() {
	return failedTestNames.size();
}