#pragma once
#include <unordered_set>
#include <string>
#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__)

class Test {
protected:
	static std::unordered_set<std::string> testNames;
	static std::unordered_set<std::string> failedTestNames;
public:
	/*
	���� ������� expr �� ���������, �� ������� check ������� ���������� �� ������; ��� ���������� ������ ��������� ��� ������� � ������, ��� ����� � ������ � ����� ������, �� ������� ���������� ����� check (��������, �test failed: testIsWIn() in TestBoard.cpp:34�).
	*/
	static void check(bool expr, const char *func, const char  *filename, uint64_t lineNum);

	static bool failed();
	/*
	������� ������� ��������� ���������� ������������, ��������, �All test passed.� ��� �Failed 2 of 8 tests.�.
	*/
	static void showFinalResult();


	/*
	��� ������� ��������� ��� ����� �� ������������ ������. ������ ��� ������� ����������� �� main � test.cpp.
	*/
	virtual void runAllTests() = 0;
};

