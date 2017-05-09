#include "HuffmanTest.h"
#include "debug.h"

int main() {
	HuffmanTest huff_test;
	huff_test.runAllTests();
	huff_test.showFinalResult();
	if (huff_test.failed()) {
		eprintf("return 1\n");
		return 1;
	}
	return 0;
}