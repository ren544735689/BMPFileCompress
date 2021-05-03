//#include"LosslessCompress.h"
//#include<iostream>
//using namespace std;
//
//int main()
//{
//	/*cout << sizeof(unsigned short) << endl;
//	cout << sizeof(long) << endl;
//	cout << sizeof(unsigned long) << endl;
//	cout << sizeof(FileHead) << endl;
//	cout << sizeof(InfoHead) << endl;
//	cout << sizeof(BMPFileHead) << endl;*/
//	
//	ReadBMPFile bmpfile("bmp.bmp", "E:");
//	bmpfile.output("RLC");	
//
//	RLCCompress rlccompress(bmpfile.getinfo());
//	rlccompress.compress();
//	rlccompress.decompress();
//
//	/*BMPInfo test = bmpfile.getinfo();
//for (int i = 0; i < 10; i++) {
//	cout << (int)test.R[i] << endl;
//}*/
//
//
//	//float ta[2][3] = { {1.0,2.0,3.0},{4.0,5.0,6.0} };
//	//float **p = new float *[2];//开辟行空间
//
//
//	////for (int i = 0; i < 3; i++)
//	////	p[i] = new float[i];//开辟列空间
//	//p[0] = new float[0];
//	//p[1] = new float[0];
//	//p[2] = new float[0];
//
//	//for (int i = 0; i < 2; i++) {    //赋值
//	//	for (int j = 0; j < 3; j++) {
//	//		p[i][j] = ta[i][j];
//	//		
//	//	}
//	//}
//	//for (int i = 0; i < 2; i++) {
//	//	for (int j = 0; j < 3; j++) {
//	//		cout << p[i][j] << endl;
//	//	}
//	//}
//}