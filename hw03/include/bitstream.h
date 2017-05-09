#pragma once

#include <iostream>
#include <fstream>




class BitOstream {
private:
	uint64_t bytes_written_;
	std::ostream& ofs_;
	std::vector<char> buffer_;
	std::size_t pos_;
    std::size_t bit_;
	void flush();
public:
	BitOstream(std::ostream& ofs);
	~BitOstream();
	BitOstream& operator<<(bool bit);
	BitOstream& operator<<(const std::vector<bool>& data);
	uint64_t bytes_written() const;
};

class BitIstream {
private:
	std::istream& ifs_;
	std::vector<char> buffer_;
	int cur_pos_;
	int bit_;
	uint64_t bytes_read_;
	void fill_buffer();
	int buffer_size() const;
public:
	BitIstream(std::istream& ifs);
	bool read_bit();
	uint64_t bytes_read() const;
};

