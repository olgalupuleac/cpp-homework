#include "Product.h"
#include <cstring>


Product::Product(): quantity_(0), price_(0) {
	name_ = new char[1];
	name_[0] = '\0';
}

Product::Product(const char* name, int quantity, double price):quantity_(quantity), price_(price) {
	name_ = new char[strlen(name) + 1];
	strcpy(name_, name);
}

Product::Product(const Product& other) : quantity_(other.quantity_), price_(other.price_) {
	name_ = new char[strlen(other.name_) + 1];
	strcpy(name_, other.name_);
}

Product& Product::operator=(const Product& other) {
	delete[] name_;
	name_ = new char[strlen(other.name_) + 1];
	strcpy(name_, other.name_);
	quantity_ = other.quantity_;
	price_ = other.price_;
	return *this;
}

Product::~Product() {
	delete[] name_;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
	return os << p.name_ << " " << p.quantity_ << " " << p.price_;
}