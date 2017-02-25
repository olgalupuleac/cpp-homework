#include <iostream>
#include <ostream>
#include <cassert>
#include "my_vector.h"
#include "Product.h"

void print(const my_vector<Product>& v) {
	std::cout << v << std::endl;
}

template <class T>
void vector_info(const my_vector<T>& v) {
	std::cout << "vector:\n"<< v << std::endl;
	std::cout << "size : " << v.size() << "\ncapacity : " << v.capacity() << std::endl;
}

template <class T>
void test_default_constructor() {
	std::cout << "testing default constructor\n";
	my_vector<T> v;
	vector_info(v);
	std::cout << std::endl;
}

template <class T>
void test_reserve(size_t n) {
	std::cout << "testing reserve\n";
	my_vector<T> v;
	v.reserve(n);
	vector_info(v);
	std::cout << std::endl;
}

template <class T>
void test_resize(size_t n) {
	std::cout << "testing resize\n";
	my_vector<T> v;
	v.resize(n);
	vector_info(v);
	std::cout << std::endl;
}

template <class T>
void test_push_back(const T& obj, size_t n) {
	std::cout << "testing push_back\n";
	my_vector<T> v;
	vector_info(v);
	for (size_t i = 0; i < n; i++) {
		v.push_back(obj);
		std::cout << "after push\n";
		vector_info(v);
	}
	std::cout << std::endl;
}

template <class T>
void test_constructor(size_t n) {
	std::cout << "testing constructor\n";
	my_vector<T> v(n);
	vector_info(v);
	std::cout << std::endl;
}

template <class T>
void test_copy_constructor(const T& obj, size_t n) {
	std::cout << "testing copy constructor\n";
	my_vector<T> v(n);
	v.push_back(obj);
	vector_info(v);
	std::cout << "creating another vector\n";
	my_vector<T> u(v);
	vector_info(u);
	std::cout << std::endl;
}

template <class T>
void test_assignment_operator(size_t n) {
	std::cout << "testing assignment operator\n";
	my_vector<T> v(n);
	vector_info(v);
	my_vector<T> u = v;
	vector_info(u);
	std::cout << std::endl;
}

template <class T>
void test_size(size_t n) {
	std::cout << "testing vector.size()\n";
	my_vector<T> v;
	std::cout << "size shold be 0, it is " << v.size() <<  std::endl;
	my_vector<T> u(n);
	std::cout << "size shold be " << n << ", it is " << v.size() << std::endl;
	std::cout << std::endl;
}

template <class T>
void test_capacity(size_t n) {
	std::cout << "testing v.capacity()\n";
	my_vector<T> v;
	std::cout << "capacity shold be 0, it is " << v.capacity() << std::endl;
	my_vector<T> u(n);
	std::cout << "size : " << n << "/n capacity : " << v.capacity() << std::endl;
	std::cout << std::endl;
}

template <class T>
void test_empty(size_t n) {
	std::cout << "testing v.empty()\n";
	my_vector<T> v;
	if (v.empty()) std::cout << "empty vector, OK"<< std::endl;
	else std::cout << "something went wrong" << std::endl;
	my_vector<T> u(n);
	if (n != 0 && !u.empty()) std::cout << "vector is not empty, OK" << std::endl;
	else {
		std::cout << "result: vector is empty\n";
		vector_info(u);
	}
	std::cout << std::endl;
}

template <class T>
void test_pop_back(const T& obj, size_t n) {
	std::cout << "testing pop_back\n";
	my_vector<T> v(n);
	vector_info(v);
	for (size_t i = 0; i < n + 1; i++) {
		v.pop_back();
		std::cout << "after pop\n";
		vector_info(v);
	}
	std::cout << std::endl;
}

template <class T>
void test_get_set(const T& obj, size_t n) {
	std::cout << "testing operator[]\n";
	my_vector<T> v(n);
	vector_info(v);
	v[0] = obj;
	vector_info(v);
	const my_vector<T> u(v);
	vector_info(u);
	std::cout << std::endl;
}

template <class T>
void test_clear(size_t n) {
	std::cout << "testing v.clear()\n";
	my_vector<T> v(n);
	vector_info(v);
	v.clear();
	vector_info(v);
	std::cout << std::endl;
}

template <class T>
void test_destructor(size_t n) {
	std::cout << "trying to test destructor\n";
	my_vector<T>* v = new my_vector<T>(n);
	delete v;
}

template <class T>
void test_my_vector(const T& obj, size_t n) {
	test_default_constructor<T>();
	test_reserve<T>(n);
	test_resize<T>(n);
	test_push_back<T>(obj, n);
	test_copy_constructor<T>(obj, n);
	test_constructor<T>(n);
	test_assignment_operator<T>(n);
	test_size<T>(n);
	test_capacity<T>(n);
	test_empty<T>(n);
	test_pop_back<T>(obj, n);
	test_get_set<T>(obj, n);
	test_clear<T>(n);
	test_destructor<T>(n);
}

int main() {
	test_my_vector<int>(10, 5);
	test_my_vector<Product>(Product("asdf", 4, 12.0), 3);
    return 0;
}
