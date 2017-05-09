#include <algorithm>
#include <vector>
#include <cstdint>
#include <string.h>
#include <assert.h>
#include "file_exceptions.h"
#include "bitstream.h"
#include "debug.h"


using std::pair;
using std::istream;
using std::ostream;
using std::string;
using std::vector;

const int BUFFER_SIZE = 10000;

BitOstream::BitOstream(std::ostream& ofs) : bytes_written_(0),
    ofs_(ofs), pos_(0), bit_(0) {
	buffer_.resize(BUFFER_SIZE);
}

BitOstream& BitOstream::operator<<(bool bit) {
	if (!bit_)
		bytes_written_++;
	if (bit)
		buffer_[pos_] |= (1 << bit_);
	bit_++;
	if (bit_ == 8) {
		bit_ = 0;
		pos_++;
		if (pos_ == buffer_.size()) {
			flush();
		}
	}
	return *this;
}

BitOstream& BitOstream::operator<<(const vector<bool>& data) {
	for (bool bit : data)
		*this << bit;
	return *this;
}


void BitOstream::flush() {
	if (bit_) {
		pos_++;
		bit_ = 0;
	}
    ofs_.write(&buffer_[0], pos_);
	std::fill(buffer_.begin(), buffer_.end(), 0);
	pos_ = 0;
}

BitOstream::~BitOstream() {
	flush();
	eprintf("bitostream destructor\n");
}

uint64_t BitOstream::bytes_written() const {
	return bytes_written_;
}


BitIstream::BitIstream(std::istream& ifs) :ifs_(ifs), bytes_read_(0) {
	buffer_.resize(BUFFER_SIZE);
	fill_buffer();
}

void BitIstream::fill_buffer() {
	ifs_.read(&buffer_[0], buffer_.size());
	bit_ = 0;
	cur_pos_ = 0;
	bytes_read_ += static_cast<uint64_t>(ifs_.gcount());
	eprintf("fill buffer %d\n", (int)ifs_.gcount());
}

bool BitIstream::read_bit() {
	if (!buffer_size()) 
		throw fileFormatException();
	assert(cur_pos_ < buffer_size());
	bool res = (buffer_[cur_pos_] >> bit_) & 1;
	eprintf("read bit %d\n", (int)res);
	bit_++;
	if (bit_ == 8) {
		bit_ = 0;
		cur_pos_++;
		if (cur_pos_ >= buffer_size())
			fill_buffer();
	}
	return res;
}

int BitIstream::buffer_size() const {
	return static_cast<int>(ifs_.gcount());
}

uint64_t BitIstream::bytes_read() const {
	return bytes_read_;
}
