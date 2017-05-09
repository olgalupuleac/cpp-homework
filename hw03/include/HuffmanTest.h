#pragma once
#include <cstddef>
#include "Test.h"
#include "huffman.h"

class HuffmanTest : public Test {
public:
	void testTreeNodeConstructor();
	void testTreeNodeParentFrequency();
	void testTreeNodeCalculateCodes();
	void testHuffTree();
	void testHuffTreeCode();
	void testHuffTreeEncode();
	void testBitOstream();
	void testBitIstream();
	void testCountCharFreq();
	void testCharFreqSerialization();
	void testArchiverSimple();
	void testArchiverBigFile();
	void testArchiverEmptyFile();
	void testArchiverOnlyCharacter();
	void runAllTests();
};
