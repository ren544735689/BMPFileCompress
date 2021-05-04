#include"LosslessCompress.h"
#include<iostream>

using namespace std;

void UI();
void RLC();
void Huff();
void JEPG();


int main()
{
	UI();

	string cmd;
	cin >> cmd;
	while (cmd != "exit") {
		if (cmd == "RLCcompression") {
			RLC();
		}
		else if (cmd == "HuffmanCompression") {
			Huff();
		}
		else if (cmd == "JPEG-Form compression") {

		}
		else if (cmd == "clear") {
			system("cls");
			UI();
		}
		else {
			cout << "Unavailable command! Please check input!" << endl;
			cout << "\nPlease input your command here:" << endl;
		}
		cin >> cmd;
	}
}

void RLC()
{
	string location, name;
	cout << "Please input the BMP file location(NULL means current location):";
	cin >> location;
	cout << "Please input the BMP file name(not NULL):";
	cin >> name;
	
	string outputlocation;
	cout << "Please input the output file location:";
	cin >> outputlocation;
	cout << "OK!" << endl;

	cout << "Compression .bmp file...";
	ReadBMPFile file(location, name);
	file.output("RLC");
	RLCCompress rlc(file.getinfo());
	rlc.compress();
	cout << "Compression finished!";

	cout << "Decompression .bmp.RLC file...";
	rlc.decompress();
	cout << "Decompression finished!" << endl;

	cout << "Successfully compress and decompress the BMP File!" << endl;
}

void UI()
{
	cout << "========================BMP File Compression=========================" << endl;
	cout << "    Suupport both Lossless compression & lossy compression" << endl;
	cout << "             MADE by Ren Hauran & Zheng Hao" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "    Attention: " << endl;
	cout << "        1. the BMP file must be no larger than 2300*2000" << endl;
	cout << "        2. only support 24-Bit BMP file" << endl;
	cout << "        3. BMP file don't has Palatte" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "    The following command is available:" << endl;
	cout << "        RLCcompression			| Run-Length-Coding lossless compression" << endl;
	cout << "        HuffmanCompression		| Huffman coding based lossless compression" << endl;
	cout << "        JPEG-Form compression		| use DCT & quantization & output JPEG" << endl;
	cout << "        clear				| clear screen" << endl;
	cout << "        exit				| exit program" << endl;
	cout << "========================BMP File Compression=========================" << endl;
	cout << "\nPlease input your command here:" << endl;
}