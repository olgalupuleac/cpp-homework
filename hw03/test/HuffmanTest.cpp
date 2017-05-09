#include <sstream>
#include <streambuf>
#include <stdlib.h>
#include "HuffmanTest.h"
#include "debug.h"


using std::unordered_map;
using std::vector;
using std::stringstream;
using std::pair;

void HuffmanTest::testTreeNodeConstructor() {
	eprintf("%s\n", __func__);
	TreeNode node(1, 'a');
	DO_CHECK(node.id() == 'a');
	DO_CHECK(node.frequency() == 1);
}

void HuffmanTest::testTreeNodeParentFrequency() {
	eprintf("%s\n", __func__);
	TreeNode left(1, 'a');
	TreeNode right(2, 'b');
	TreeNode parent(&left, &right, 1000);
	DO_CHECK(parent.frequency() == 3);
}

void HuffmanTest::testTreeNodeCalculateCodes() {
	eprintf("%s\n", __func__);
	TreeNode left(1, 'a');
	TreeNode right(2, 'b');
	TreeNode parent(&left, &right, 1000);
	parent.calculate_codes();
	DO_CHECK(left.codeForDebug() == "0" && right.codeForDebug() == "1");
}

void HuffmanTest::testHuffTree() {
	eprintf("%s\n", __func__);
	unordered_map<char, uint64_t> frequency_map = { {'a', 1}, {'b', 1}, {'c', 10} };
	HuffTree tree(frequency_map);
	TreeNode a(1, 'a');
	TreeNode b(1, 'b');
	TreeNode c(10, 'c');
	TreeNode ab(&a, &b, 1000);
	TreeNode abc(&ab, &c, 1001);
	DO_CHECK(abc == tree.root());
}

void HuffmanTest::testCharFreqSerialization() {
	eprintf("%s\n", __func__);
	stringstream file;
	unordered_map<char, uint64_t> frequency_map = { {'a', 1}, {'f', 3},
	     {'w', 56}, {'k', 246} };
	deserialize_char_freq(file, frequency_map);
	unordered_map<char, uint64_t> result = serialize_char_freq(file);
    DO_CHECK(frequency_map == result);
}



void HuffmanTest::testHuffTreeCode() {
	eprintf("%s\n", __func__);
	unordered_map<char, uint64_t> frequency_map = { { 'a', 1 },{ 'b', 2 },
	{ 'c', 2}, {'d',10} };
	HuffTree tree(frequency_map);
	unordered_map<char, vector<bool> > codes = tree.chars_to_code();
	vector<bool> a = { 0, 1, 0 };
	vector<bool> b = { 0, 1, 1 };
	vector<bool> c = { 0, 0 };
	vector<bool> d = { 1 };
	DO_CHECK(a == codes['a']);
	DO_CHECK(b == codes['b']);
	DO_CHECK(c == codes['c']);
	DO_CHECK(d == codes['d']);
}

void HuffmanTest::testHuffTreeEncode() {
	eprintf("%s\n", __func__);
	unordered_map<char, uint64_t> frequency_map = { { 'a', 1 },{ 'b', 1 },
	{ 'c', 10 } };;
	HuffTree tree(frequency_map);
	unordered_map<vector<bool>, char> keys = tree.codes_to_char();
	vector<bool> a = { 0, 0 };
	vector<bool> b = { 0, 1 };
	vector<bool> c = { 1 };
	DO_CHECK('a' == keys[a]);
	DO_CHECK('b' == keys[b]);
	DO_CHECK('c' == keys[c]);
}


void HuffmanTest::testBitOstream() {
	eprintf("%s\n", __func__);
	stringstream file;
	{
		BitOstream bit_os(file);
		vector<bool> data;
		for (uint64_t i = 0; i < 16005; i++) {
			data.push_back(i % 8 == 3 || i % 8 == 7);
		}
		bit_os << data;
	}
	unsigned char mask = (1 << 3) | (1 << 7);
	char c;
	for (uint64_t i = 0; i < 16005 / 8; i++) {
		file.read(&c, sizeof(c));
		DO_CHECK(c == static_cast<char>(mask));
		DO_CHECK(!file.eof());
	}
	char last = (1 << 3);
	file.read(&c, sizeof(c));
	DO_CHECK(last == c);
	file.read(&c, sizeof(c));
	DO_CHECK(file.eof());
}

void HuffmanTest::testBitIstream() {
	eprintf("%s\n", __func__);
	stringstream file;
	char mask = (1 << 2) | (1 << 5);
	for (uint64_t i = 0; i < 20003; i++) {
		file.write(&mask, sizeof(mask));
	}
	BitIstream bit_is(file);
	for (uint64_t i = 0; i < 160024; i++) {
		DO_CHECK((i % 8 == 2 || i % 8 == 5) == bit_is.read_bit());
	}
}


void HuffmanTest::testCountCharFreq() {
	eprintf("%s\n", __func__);
	std::string str("abbaccd ab");
	stringstream file(str);
	unordered_map<char, uint64_t> frequency_map = count_char_freq(file);
	unordered_map<char, uint64_t> result = { { 'a', 3 },{ 'b', 3 },
	{ 'c', 2 },{ 'd',1 }, {' ', 1} };
	DO_CHECK(original_file_size(frequency_map) == 10);
	DO_CHECK(frequency_map == result);
}

void HuffmanTest::testArchiverSimple() {
	eprintf("%s\n", __func__);
	std::string str("adxtryfuvuftxrszb   ohuv\n\nhjkbiv");
	stringstream in_file(str);
	stringstream zipped_file;
	stringstream out_file;
	compression_statistics during_compress = compress(in_file, zipped_file);
	compression_statistics during_decompress = decompress(zipped_file, out_file);
	DO_CHECK(during_compress == during_decompress);
	DO_CHECK(during_compress.uncompressed_file == in_file.str().size());
	DO_CHECK(during_compress.compressed_file + during_compress.additional_data  == zipped_file.str().size());
	eprintf("%s\n", out_file.str().c_str());
	eprintf("hello\n");
	DO_CHECK(str == out_file.str());
}

void HuffmanTest::testArchiverBigFile() {
	eprintf("%s\n", __func__);
	std::string in;
	srand(455687);
	for (uint64_t i = 0; i < 500000; i++) {
		in += static_cast<char>(rand());
	}
	eprintf("done\n");
	stringstream in_file(in);
	stringstream zipped_file;
	stringstream out_file;
	compression_statistics during_compress = compress(in_file, zipped_file);
	compression_statistics during_decompress = decompress(zipped_file, out_file);
	DO_CHECK(during_compress == during_decompress);
	DO_CHECK(during_compress.uncompressed_file == in_file.str().size());
	DO_CHECK(during_compress.compressed_file + during_compress.additional_data == zipped_file.str().size());
	DO_CHECK(in == out_file.str());
}

void HuffmanTest::testArchiverEmptyFile() {
	eprintf("%s\n", __func__);
	stringstream in_file;
	stringstream zipped_file;
	stringstream out_file;
	compression_statistics during_compress = compress(in_file, zipped_file);
	compression_statistics during_decompress = decompress(zipped_file, out_file);
	DO_CHECK(during_compress == during_decompress);
	DO_CHECK(during_compress.uncompressed_file == in_file.str().size());
	DO_CHECK(during_compress.compressed_file + during_compress.additional_data == zipped_file.str().size());
	DO_CHECK("" == out_file.str());
}

void HuffmanTest::testArchiverOnlyCharacter() {
	eprintf("%s\n", __func__);
	stringstream in_file("aaaaaaaaaaaaaaa");
	stringstream zipped_file;
	stringstream out_file;
	compression_statistics during_compress = compress(in_file, zipped_file);
	compression_statistics during_decompress = decompress(zipped_file, out_file);
	DO_CHECK(during_compress == during_decompress);
	DO_CHECK(during_compress.uncompressed_file == in_file.str().size());
	DO_CHECK(during_compress.compressed_file + during_compress.additional_data == zipped_file.str().size());
	eprintf("%s\n", out_file.str().c_str());
	DO_CHECK("aaaaaaaaaaaaaaa" == out_file.str());
}

void HuffmanTest::runAllTests() {
	testTreeNodeConstructor();
	testTreeNodeParentFrequency();
	testTreeNodeCalculateCodes();
	testHuffTree();
	testCharFreqSerialization();
	testHuffTreeCode();
	testHuffTreeEncode();
	testBitOstream();
	testCountCharFreq();
	testBitIstream();
	testArchiverSimple();
	testArchiverBigFile();
	testArchiverEmptyFile();
	testArchiverOnlyCharacter();
}
