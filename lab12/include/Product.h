#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED
#include <iostream>

class Product {
public:
	Product();
	Product(const char* name, int quantity, double price);
	Product(const Product& other);
	Product& operator=(const Product& other);
	~Product();
	friend std::ostream& operator<<(std::ostream& os, Product& p);
	friend std::ostream& operator<<(std::ostream& os, const Product& p);
private:
	char *name_;
	int quantity_;
	double price_;
};

#endif // PRODUCT_H_INCLUDED
