#include "huffman.h"
#include "file_exceptions.h"

enum Action {
	COMPRESS,
	DECOMPRESS,
	UNKNOWN
};

struct Args {
	std::string input_file;
	std::string output_file;
	Action action;
	Args():action(UNKNOWN){}
};

Args parse_arguments(int argc, char* argv[]) {
	if (argc != 6)  
		throw parseException();
	Args res;
	int i = 1;
	while (i < 5) {
		if (std::string(argv[i]) == "-c")
			res.action = COMPRESS;
		if (std::string(argv[i]) == "-u")
			res.action = DECOMPRESS;
		if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file")
			res.input_file = std::string(argv[++i]);
		if	(std::string(argv[i]) == "-o" || std::string(argv[i]) == "--output")
			res.output_file = std::string(argv[++i]);
		i++;
	}
	if(res.action == UNKNOWN || res.input_file == "" || res.output_file == "")
		throw parseException();
	return res;
}

int main(int argc, char* argv[]) {
	try {
		std::ifstream ifs;
		std::ofstream ofs;
		char read_buffer[10241];
		char write_buffer[10241];
		ifs.rdbuf()->pubsetbuf(read_buffer, sizeof read_buffer);
		ofs.rdbuf()->pubsetbuf(write_buffer, sizeof write_buffer);
		Args args = parse_arguments(argc, argv);
		ifs.open(args.input_file, std::ifstream::binary);
		ofs.open(args.output_file, std::ofstream::binary);
		if (args.action == COMPRESS) 
			try {
				std::cout << compress(ifs, ofs);
			}
			catch (const fileException& e) {
				std::cerr << e.what() << "\n";
			}
		else
			try {
			     std::cout << decompress(ifs, ofs);
		    }
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << "\n";
			}
	}
	catch (const parseException& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
