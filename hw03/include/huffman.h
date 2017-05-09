#pragma once

#include "huffman_tree.h"
#include "bitstream.h"

struct compression_statistics {
	uint64_t uncompressed_file;
	uint64_t compressed_file;
	uint64_t additional_data;
};

std::ostream& operator<<(std::ostream& os, const compression_statistics& statistics);

bool operator==(const compression_statistics& rhs, const compression_statistics& lhs);

uint64_t original_file_size(const std::unordered_map<char,
	uint64_t>& frequency_map);

uint64_t additional_data_size(std::size_t freq_map_size);

std::unordered_map<char, uint64_t> count_char_freq(std::istream& ifs);

void deserialize_char_freq(std::ostream& ofs,
	const std::unordered_map<char, uint64_t>& frequency_map);

std::unordered_map<char, uint64_t> serialize_char_freq(std::istream& ifs);

compression_statistics compress(std::istream& ifs, std::ostream& ofs);
compression_statistics decompress(std::istream& ifs, std::ostream& ofs);
