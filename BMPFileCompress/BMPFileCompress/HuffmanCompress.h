#ifndef _HUFFMANCOMPRESS
#define _HUFFMANCOMPRESS

#include"Compress.h"
#include"HuffmanTree.h"
using namespace std;

class HuffmanCompress :public Compress {
private:
	HuffmanTreeNode* HuffmanTree;
	int chSetSize;
public:
	// ctor
	HuffmanCompress(BMPInfo info) :Compress(info) {}

public:
	virtual void compress();
	virtual void decompress();
};

#endif // !_HUFFMANCOMPRESS

