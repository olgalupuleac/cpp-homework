#pragma once

#include <stdexcept>

class parseException : public std::runtime_error {
public:
	parseException() : std::runtime_error("Invalid arguments"){}
};


class fileException : public std::runtime_error {
public:
	fileException() : std::runtime_error("Cannot open this file") {}
};


class fileFormatException : public std::runtime_error {
public:
	fileFormatException() : std::runtime_error("Cannot decompress this file"){}
};
