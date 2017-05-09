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
	≈сли условие expr не выполнено, то функци€ check выводит информацию об ошибке; эта информаци€ должна содержать им€ функции с тестом, им€ файла с тестом и номер строки, на которой находитьс€ вызов check (например, Уtest failed: testIsWIn() in TestBoard.cpp:34Ф).
	*/
	static void check(bool expr, const char *func, const char  *filename, uint64_t lineNum);

	static bool failed();
	/*
	‘ункци€ выводит финальную статистику тестировани€, например, УAll test passed.Ф или УFailed 2 of 8 tests.Ф.
	*/
	static void showFinalResult();


	/*
	Ёта функци€ запускает все тесты из производного класса. »менно эта функци€ запускаетс€ из main в test.cpp.
	*/
	virtual void runAllTests() = 0;
};

