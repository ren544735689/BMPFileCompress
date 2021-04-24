#ifndef _LOSSLESSCOMPRESS
#define _LOSSLESSCOMPRESS

#include"Compress.h"
using namespace std;

class RLCCompress :public Compress{
public:
	// ctor
	RLCCompress(BMPInfo info):Compress(info){}

public:
	virtual void compress();
	virtual void decompress();
};

class HuffmanCompress :public Compress {
public:
	// ctor
	HuffmanCompress(BMPInfo info) :Compress(info) {}

public:
	virtual void compress();
	virtual void decompress();
};

#endif // !_LOSSLESSCOMPRESS

