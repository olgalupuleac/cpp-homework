#include <algorithm>
#include <string.h>
#include "bitstream.h"

using std::size_t;
using std::pair;
using std::ifstream;
using std::ofstream;
using std::string;


BitOstream::BitOstream(string filename) :pos(0), bit(0) {
    ofs.open(filename, ofstream::binary);
}

void BitOstream::push(std::string& data) {
    for (char c : data) {
        if (c == '1')
            buffer[pos] |= (1 << bit);
        bit++;
        //eprintf("I'm working\n");
        if (bit == 8) {
            pos++;
            bit = 0;
            if (pos == sizeof(buffer) - 1) {
                eprintf("flush\n");
                ofs.write((char*)buffer, sizeof(buffer));
                memset(buffer, 0, sizeof(buffer));
                pos = 0;
            }
        }
    }
}

void BitOstream::write(const HuffTree& tree) {
    size_t s = tree.leaf_num();
    ofs.write((char*)&s, sizeof(size_t));
    for (size_t i = 0; i < tree.leaf_num(); i++) {
        pair<char, size_t> leaf = tree.get(i);
        char c = leaf.first;
        size_t freq = leaf.second;
        ofs.write(&c, sizeof(char));
        ofs.write((char*)&freq, sizeof(size_t));
    }
}

void BitOstream::write(size_t& size) {
    ofs.write((char*)&size, sizeof(size_t));
}

BitOstream::~BitOstream() {
    if (bit + pos) ofs.write((char*)buffer, pos + 1);
    ofs.close();
}

void bit_stream(std::ifstream& ifs, std::unordered_map<string, char>& keys, std::string filename, std::size_t file_size) {
    uint8_t read_buffer[1000];
    string write_buffer;
    string cur_code;
    size_t num_to_read = file_size;
    eprintf("\n\nfile size %d", (int)file_size);
    ofstream ofs(filename, ofstream::binary);
    while (!ifs.eof() && num_to_read) {
        ifs.read((char*)read_buffer, sizeof(read_buffer));
        for (size_t i = 0; i < (size_t) ifs.gcount(); i++) {
            for (size_t bit = 0; bit < 8; bit++) {
                cur_code += std::to_string((read_buffer[i] >> bit) & 1);
                if (keys.find(cur_code) != keys.end()) {
                    write_buffer += keys[cur_code];
                    cur_code.clear();
                }
            }
            if (write_buffer.size() > 1000) {
                eprintf("flush %d bytes\n", (int)std::min(write_buffer.size(), num_to_read));
                ofs.write(write_buffer.c_str(), std::min(write_buffer.size(), num_to_read));
                if (num_to_read > write_buffer.size()) num_to_read -= write_buffer.size();
                else {
                    num_to_read = 0;
                }
                write_buffer.clear();
            }
        }
        ofs.write(write_buffer.c_str(), std::min(write_buffer.size(), num_to_read));
    }
    
}
