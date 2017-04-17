#include "huffman.h"

int main() {
	std::cout << "Enter filename and result filename\n";
	std::string filename;
	std::string res_filename;
	std::cin >> filename >> res_filename;
    HuffmanArchiver zipper(filename, filename + ".hfm");
    HuffmanArchiver unzipper(filename + ".hfm", res_filename);
    zipper.zip();
    unzipper.unzip();
    return 0;
}