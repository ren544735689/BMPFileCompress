#include"HuffmanCompress.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<fstream>
using namespace std;

void HuffmanCompress::compress()
{
	char ch;
	vector<char> table;
	vector<int> weight;
	vector<char>::iterator i = table.begin();
	vector<int>::iterator j = weight.begin();

	bool flag = false;
	FILE *inf = fopen(info.filename.c_str(), "rb");

	while (!feof(inf)) {
		fread(&ch, 1, 1, inf);
		flag = false;
		
		for ( ; i !=table.end(); i++,j++) {
			if (*i == ch) {
				flag = true;
				(*j)+=1;
				break;
			}
		}
		if (!flag) {
			table.emplace_back(ch);
			weight.emplace_back(1);
		}
	}
	
	ofstream outputchtable;
	outputchtable.open("HuffmanTable.txt");
	outputchtable << table.size();
	
	
	for (i = table.begin(); i !=table.end(); i++) {
		outputchtable << *i;
	}
	outputchtable << endl;
	for (j = weight.begin(); j != weight.end(); i++) {
		outputchtable << *j << " ";
	}

	char* huffmantree = nullptr;
	strcpy(huffmantree, "HuffmanTree.txt");
	char* huffmantable = nullptr;
	strcpy(huffmantable, "HuffmanTable.txt");
	char* resfile = nullptr;
	strcpy(huffmantable, info.filename.c_str());
	char* desfile = nullptr;
	strcpy(desfile, "HuffmanCompression.HUF");

	HuffmanTree = initialHuffmanTree(&chSetSize, huffmantree, huffmantable);
	encode(HuffmanTree, chSetSize, resfile, desfile);
}

void HuffmanCompress::decompress()
{
	char* resfile=nullptr;
	strcpy(resfile, "HuffmanCompression.HUF");
	char* desfile=nullptr;
	strcpy(desfile, "HuffmanDecompression.HUF");
	decode(HuffmanTree, 2 * chSetSize - 1, resfile, desfile);
}