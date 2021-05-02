#include"LosslessCompress.h"
#include<iostream>
using namespace std;

void RLCCompress::compress()
{
	FILE *fp = fopen((info.filename + ".RLC").c_str(), "wb");
	if (fp == NULL) {
		printf("Sorry, cannot find compression file!\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_END);

	int now;
	int item;
	int recnum;

	cout << "R:" << endl;
	for (int i = 0; i < info.height; i++) {
		now = 0;
		recnum = 1;
		item = info.R[i * info.width];
		while (1) {
			now++;
			if (now == info.width) {
				fwrite(&item, 1, 1, fp);
				fwrite(&recnum, 1, 1, fp);
				break;
			}

			if (info.R[i * info.width + now] == item) {
				recnum++;
			}
			else {
				fwrite(&item, 1, 1, fp);
				fwrite(&recnum, 1, 1, fp);
				item = info.R[i * info.width + now];
				recnum = 1;
			}
		}
	}
	cout << "G:" << endl;
	for (int i = 0; i < info.height; i++) {
		now = 0;
		recnum = 1;
		item = info.G[i * info.width];
		while (1) {
			now++;
			if (now == info.width) {
				fwrite(&item, 1, 1, fp);
				fwrite(&recnum, 1, 1, fp);
				break;
			}

			if (info.G[i * info.width + now] == item) {
				recnum++;
			}
			else {
				fwrite(&item, 1, 1, fp);
				fwrite(&recnum, 1, 1, fp);
				item = info.G[i * info.width + now];
				recnum = 1;
			}
		}
	}
	cout << "B:" << endl;
	for (int i = 0; i < info.height; i++) {
		now = 0;
		recnum = 1;
		item = info.B[i * info.width];
		while (1) {
			now++;
			if (now == info.width) {
				fwrite(&item, 1, 1, fp);
				fwrite(&recnum, 1, 1, fp);
				break;
			}

			if (info.B[i * info.width + now] == item) {
				recnum++;
			}
			else {
				fwrite(&item, 1, 1, fp);
				fwrite(&recnum, 1, 1, fp);
				item = info.B[i * info.width + now];
				recnum = 1;
			}
		}
	}
}

void RLCCompress::decompress()
{
	FILE *ofp = fopen((info.filename + ".RLC.bmp").c_str(), "wb");
	if (ofp == NULL) {
		printf("Sorry, cannot find output-original(*.RLC.bmp) file!\n");
		exit(0);
	}
	fseek(ofp, 56, SEEK_SET);			// 56 is the total BMP head size

	FILE *ifp = fopen((info.filename + ".RLC").c_str(), "r");
	if (ofp == NULL) {
		printf("Sorry, cannot find after-compression(*.RLC) file!\n");
		exit(0);
	}
	fseek(ifp, 56, SEEK_SET);			// 56 is the total BMP head size

	int color;							// the current color
	int recnum;							// the current color recursion number
	
	int nowheight = 0;					// now process height
	int nowwidth = 0;

	while (1) {
		fread(&color, 1, 1, ifp);
		fread(&recnum, 1, 1, ifp);

		nowwidth += recnum;
		if (nowwidth == info.width) {	// if we process one line
			nowwidth = 0;
			nowheight++;

		}
		if (nowheight == info.height) {	// if we process one color field
			nowheight = 0;
			nowwidth = 0;
			break;
		}
	}

	/*for (j = 1; j <= width; j++) {
		fread(&B[i][j], 1, 1, f);
		fread(&G[i][j], 1, 1, f);
		fread(&R[i][j], 1, 1, f);
	}
	if (offset != 0) fread(&a, offset, 1, f);*/
}

