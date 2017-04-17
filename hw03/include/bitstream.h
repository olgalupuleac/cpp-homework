#pragma once

#include <iostream>
#include <fstream>
#include "huffman_tree.h"

class BitOstream {
private:
    std::ofstream ofs;
    uint8_t buffer[100000] = { 0 };
    std::size_t pos;
    std::size_t bit;
public:
    BitOstream(std::string filename);
    void push(std::string& data);
    void write(const HuffTree& tree);
    void write(std::size_t& size);
    ~BitOstream();
};

void bit_stream(std::ifstream& ifs, std::unordered_map<std::string, char>& keys, std::string filename, std::size_t file_size);
