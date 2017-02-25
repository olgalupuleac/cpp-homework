#ifndef MY_VECTOR_H_INCLUDED
#define MY_VECTOR_H_INCLUDED
#include <cstddef>
#include <algorithm>
#include <utility>

template <class T>
class my_vector {
public:
	my_vector() : capacity_(0), size_(0), array_(NULL) {}

	my_vector(size_t n) : capacity_(0), size_(0), array_(NULL) {
		resize(n);
	}

	my_vector(const my_vector& other) : capacity_(other.capacity_), size_(other.size_){
		array_ = new T [capacity_]();
		for (size_t i = 0; i < size_; i++) array_[i] = other.array_[i];
	}

	my_vector& operator=(const my_vector& other) {
		size_ = other->size_;
		capacity_ = other->capacity_;
		my_vector tmp(other);
		std::swap(array_, tmp.array_);
		return *this;
	}

	~my_vector() {
		delete[] array_;
	}

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		return capacity_;
	}

	bool empty() const {
		return !size_;
	}

	void resize(size_t n) {
		reserve(n);
		size_ = n;
	}

	void reserve(size_t n) {
		if (n > capacity_) {
			capacity_ = std::max((size_t) 1, capacity_);
			while (capacity_ < n) capacity_ *= 2;
			T* tmp = new T[capacity_]();
			for (size_t i = 0; i < size_; i++) tmp[i] = array_[i];
			delete[] array_;
			array_ = tmp;
		}
	}

	T& operator[](size_t index) {
		return array_[index];
	}

	const T& operator[](size_t index) const {
		return array_[index];
	}

	void push_back(const T& t) {
		if (size_ >= capacity_) reserve(size_ + 1);
		array_[size_++] = t;
	}

	void pop_back() {
		if (size_) size_--;
	}

	void clear() {
		size_ = 0;
	}

private:
	size_t capacity_;
	size_t size_;
	T* array_;
};


template <class T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& v) {
	if (v.empty()) return os;
	for (size_t i = 0; i < v.size() - 1; i++) {
		os << v[i] << " ";
	}
	return os << v[v.size() - 1];
}

#endif