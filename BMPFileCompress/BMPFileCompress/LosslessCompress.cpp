#include"LosslessCompress.h"
using namespace std;

void RLCCompress::compress()
{
	FILE *fp;
	if ((fp = fopen((info.filename)) == NULL) {
		printf("Write GRAY.bmp ERROR!\n");
		exit(0);
	}
	of.open(info.filename + ".RLC",ios::app);
	if (!of) {
		cout << "Sorry, cannot find compression file!" << endl;
		return;
	}
	of << "Run_Length_Coding" << endl;

	int now;
	int item;
	int recnum;

	cout << "R:" << endl;
	for (int i = 0; i < info.height; i++) {
		now = 0;
		recnum = 1;
		item = info.R[i][0];
		while (1) {
			now++;
			if (now == info.width) {
				of << "(" << item << "," << recnum << ")" << endl;
				break;
			}

			if (info.R[i][now] == item) {
				recnum++;
			}
			else {
				of << "(" << item << "," << recnum << ")";
				item = info.R[i][now];
				recnum = 1;
			}
		}
	}
	cout << "G:" << endl;
	for (int i = 0; i < info.height; i++) {
		now = 0;
		recnum = 1;
		item = info.G[i][0];
		while (1) {
			now++;
			if (now == info.width) {
				of << "(" << item << "," << recnum << ")" << endl;
				break;
			}

			if (info.G[i][now] == item) {
				recnum++;
			}
			else {
				of << "(" << item << "," << recnum << ")";
				item = info.G[i][now];
				recnum = 1;
			}
		}
	}
	cout << "B:" << endl;
	for (int i = 0; i < info.height; i++) {
		now = 0;
		recnum = 1;
		item = info.B[i][0];
		while (1) {
			now++;
			if (now == info.width) {
				of << "(" << item << "," << recnum << ")" << endl;
				break;
			}

			if (info.B[i][now] == item) {
				recnum++;
			}
			else {
				of << "(" << item << "," << recnum << ")";
				item = info.B[i][now];
				recnum = 1;
			}
		}
	}
}
