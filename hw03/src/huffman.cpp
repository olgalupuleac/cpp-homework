#include "huffman.h"

using std::size_t;
using std::pair;
using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;

size_t get_char_freq(ifstream& ifs, unordered_map<char, size_t>& frequency_map) {
    size_t file_size = 0;
    char buffer[1000];
    while (!ifs.eof()) {
        ifs.read(buffer, sizeof(buffer));
        file_size += (size_t) ifs.gcount();
        for (size_t i = 0; i < (size_t) ifs.gcount(); i++)
            frequency_map[buffer[i]]++;
    }
    return file_size;
}


void HuffmanArchiver::zip() {
    ifstream ifs(in_, ifstream::binary);
    unordered_map<char, size_t> frequency_map;
    size_t file_size = get_char_freq(ifs, frequency_map);
    eprintf("hello?\n");
    eprintf("input file size %d\n", (int)file_size);
    HuffTree codes_tree(frequency_map);
    codes_tree.calculate_codes();
    BitOstream bitos(out_);
    bitos.write(file_size);
    bitos.write(codes_tree);
    unordered_map<char, string> codes;
    code(codes_tree, codes);
    ifs.clear();
    ifs.seekg(0, ifs.beg);
    string code;
    char buffer[1000];
    while (!ifs.eof()) {
        ifs.read(buffer, sizeof(buffer));
        for (size_t i = 0; i < (size_t) ifs.gcount(); i++)
            code += codes[buffer[i]];
        bitos.push(code);
    }
}


void read_tree(ifstream& ifs, unordered_map<char, size_t>& char_freq) {
    size_t size;
    ifs.read((char*)&size, sizeof(size_t));
    eprintf("\n\nsize %d\n", (int)size);
    for (size_t i = 0; i < size; i++) {
        char c;
        ifs.read(&c, sizeof(char));
        size_t freq;
        ifs.read((char*)&freq, sizeof(size_t));
        char_freq[c] = freq;
        eprintf("freq is %d and char is %c\n", (int)freq, c);
    }
}

void HuffmanArchiver::unzip() {
    ifstream ifs(in_, ifstream::binary);
    size_t file_size;
    ifs.read((char*)&file_size, sizeof(size_t));
    unordered_map<char, size_t> char_freq;
    read_tree(ifs, char_freq);
    HuffTree codes_tree(char_freq);
    codes_tree.calculate_codes();
    unordered_map<string, char> keys;
    decode(codes_tree, keys);
    bit_stream(ifs, keys, out_, file_size);
}