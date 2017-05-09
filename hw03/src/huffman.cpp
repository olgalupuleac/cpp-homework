#include <iostream>
#include <assert.h>
#include "file_exceptions.h"
#include "debug.h"
#include "huffman.h"

using std::pair;
using std::istream;
using std::ostream;
using std::string;
using std::unordered_map;
using std::vector;

ostream& operator<<(ostream& os, const compression_statistics& statistics) {
	os << statistics.uncompressed_file << "\n" << statistics.compressed_file << "\n"
		<< statistics.additional_data << "\n";
	return os;
}

bool operator==(const compression_statistics& rhs,
	const compression_statistics& lhs) {
	return rhs.compressed_file == lhs.compressed_file &&
		rhs.uncompressed_file == lhs.uncompressed_file &&
		rhs.additional_data == lhs.additional_data;
}

uint64_t original_file_size(const unordered_map<char,
	uint64_t>& frequency_map) {
	uint64_t file_size = 0;
	for (auto char_and_freq : frequency_map) {
		file_size += char_and_freq.second;
	}
	return file_size;
}

uint64_t additional_data_size(std::size_t freq_map_size) {
	return sizeof(uint64_t) + freq_map_size * (sizeof(uint64_t) + sizeof(char));
}

unordered_map<char, uint64_t> count_char_freq(istream& ifs) {
	if (!ifs)
		throw fileException();
	unordered_map<char, uint64_t> frequency_map;
	while (ifs) {
		char c;
		ifs.read(&c, sizeof(c));
		for (int i = 0; i < ifs.gcount(); i++)
			frequency_map[c]++;
	}
	return frequency_map;
}

void deserialize_char_freq(ostream& ofs,
	const unordered_map<char, uint64_t>& frequency_map) {
	uint64_t size = frequency_map.size();
	ofs.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (auto x : frequency_map) {
		char c = x.first;
		uint64_t freq = x.second;
		ofs.write((&c), sizeof(c));
		ofs.write(reinterpret_cast<char*>(&freq), sizeof(freq));
	}
}

unordered_map<char, uint64_t> serialize_char_freq(istream& ifs) {
	if (!ifs)
		throw fileException();
	unordered_map<char, uint64_t> frequency_map;
	uint64_t size;
	ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (uint64_t i = 0; i < size; i++) {
		char c;
		ifs.read(&c, sizeof(c));
		uint64_t freq;
		ifs.read(reinterpret_cast<char*>(&freq), sizeof(freq));
		frequency_map[c] = freq;
	}
	return frequency_map;
}

compression_statistics compress(istream& ifs, ostream& ofs) {
	unordered_map<char, uint64_t> frequency_map = count_char_freq(ifs);
	deserialize_char_freq(ofs, frequency_map);
	HuffTree codes_tree(frequency_map);
	BitOstream bit_ofs(ofs);
	unordered_map<char, vector<bool> > codes = codes_tree.chars_to_code();
	ifs.clear();
	ifs.seekg(0, ifs.beg);
	while (ifs) {
		char c;
		ifs.read(&c, sizeof(c));
		bit_ofs << codes[c];
	}
	eprintf("file size %d, compressed size %d, additional data %d\n", (int)original_file_size(frequency_map), (int)bit_ofs.bytes_written(),
		(int)additional_data_size(frequency_map.size()));
	return{ original_file_size(frequency_map), bit_ofs.bytes_written(),
		additional_data_size(frequency_map.size()) };
}


compression_statistics decompress(istream& ifs, ostream& ofs) {
	unordered_map<char, uint64_t> frequency_map = serialize_char_freq(ifs);
	uint64_t file_size = original_file_size(frequency_map);
	HuffTree codes_tree(frequency_map);
	unordered_map<vector<bool>, char> keys = codes_tree.codes_to_char();
	BitIstream bit_ifs(ifs);
	uint64_t written_bytes = 0;
	if (frequency_map.size() == 1) { //if code is empty it is impossible to read it from file as it leads to fileFormatException
		char c = (*frequency_map.begin()).first;
		for (std::size_t i = 0; i < file_size; i++) {
			ofs.write(&c, sizeof(c));
		}
	}
	else {
		auto keys_end = keys.end();
		while (written_bytes < file_size) {
			vector<bool> cur_code;
			while (keys.find(cur_code) == keys_end) {
				cur_code.push_back(bit_ifs.read_bit());
			}
			ofs.write(&keys[cur_code], sizeof(char));
			written_bytes++;
			eprintf("%c", keys[cur_code]);
		}
	}
	return{ file_size, bit_ifs.bytes_read(), additional_data_size(frequency_map.size()) };
}
