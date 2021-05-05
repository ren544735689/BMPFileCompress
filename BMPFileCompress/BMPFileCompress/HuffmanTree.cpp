#pragma warning(disable:4996)

#include"huffmanTree.h"

HuffmanTreeNode* initialHuffmanTree(int *size, string huffmanTreeFile, string characterSetFile)
{
	int characterSetSize = 0;
	int huffmanArraySize;
	char *characterSet;   //imitate array with changeable length
	int *characterSetWeight;  //imitate array with changeable length
	int min1;   //the index with min weight
	int min2;   //the index with secongMin weight
	int i;      //counter
	HuffmanTreeNode *p;
	HuffmanTreeNode *huffmanArray;  //imitate array with changeable length
	ifstream inf;
	inf.open(characterSetFile);

	if (!inf)
	{
		cout << "\nError caused by opening characterSetFile!" << endl;
		return nullptr;
	}
	//read characterSetSize from characterSetFile
	inf >> characterSetSize;
	*size = characterSetSize;
	huffmanArraySize = 2 * characterSetSize - 1;
	huffmanArray = (HuffmanTreeNode *)malloc((huffmanArraySize + 1)
		* sizeof(HuffmanTreeNode));
	if (characterSetSize > 0)
	{
		if (huffmanArray == NULL)
		{
			cout << "No memory available!\n" << endl;
			return nullptr;
		}
		if ((characterSet = (char *)malloc(characterSetSize * sizeof(char))) == NULL)
		{
			cout << "No memory available!\n" << endl;
			return nullptr;
		}
		if ((characterSetWeight = (int *)malloc(characterSetSize * sizeof(int))) == NULL)
		{
			cout << "No memory available!\n" << endl;
			return nullptr;
		}
		for (i = 0; i < characterSetSize; i++)
		{
			inf.get(characterSet[i]);
			//cout << "test::" << characterSet[i] << endl;;
		}

		for (i = 0; i < characterSetSize; i++) {
			inf >> characterSetWeight[i];
			//cout << "test::" << characterSetWeight[i] << endl;;
		}	

		//initialize huffmanArray's primary character node
		for (p = huffmanArray + 1, i = 1; i <= characterSetSize; ++i, ++p)
		{
			p->weight = characterSetWeight[i - 1];
			p->value = characterSet[i - 1];
			p->parent = 0;
			p->lchild = 0;
			p->rchild = 0;
			p->size = 1;  //primary size is 1
		}
		//initialize huffmanArray's generated node
		for (; i <= huffmanArraySize; ++i, ++p)
		{
			p->weight = 0;    //empty
			p->value = ' ';   //space
			p->parent = 0;
			p->lchild = 0;
			p->rchild = 0;
			p->size = 1;
		}

		for (i = characterSetSize + 1; i <= huffmanArraySize; i++)
		{
			//select the min and secondMin node from huffmanArray
			select(huffmanArray, i - 1, &min1, &min2);
			//generate new tree and update some information
			huffmanArray[min1].parent = i;
			huffmanArray[min2].parent = i;
			huffmanArray[i].size = huffmanArray[min1].size + huffmanArray[min2].size + 1;
			huffmanArray[i].lchild = min1;
			huffmanArray[i].rchild = min2;
			huffmanArray[i].weight = huffmanArray[min1].weight + huffmanArray[min2].weight;
		}

		ofstream outf;
		outf.open(huffmanTreeFile);
		if (!outf)
		{
			cout << "Error caused by opening huffmanTreeFile!" << endl;
			return nullptr;
		}
		//print huffmanArray's size for using of reading huffmanTreeFile
		outf << huffmanArraySize << endl;
		//print all node's information
		for (i = 1; i <= huffmanArraySize; i++)
			outf << i << "\t" << huffmanArray[i].weight<<"\t"<< huffmanArray[i].value << "\t" << huffmanArray[i].parent << "\t" << huffmanArray[i].lchild << "\t" << huffmanArray[i].rchild << "\t" << huffmanArray[i].size << "\n";
	}
	return huffmanArray;
}

void select(HuffmanTreeNode *huffmanArray, int boundary, int *minWeightIndex,
	int*secondMinWeightIndex)
{
	int i, j;   //counter

	//find first item whose parent is 0
	for (j = 1; j <= boundary && huffmanArray[j].parent != 0; j++)
		;
	*minWeightIndex = i = j;
	//travel the part and update indexs
	for (i++; i <= boundary; i++)
		//parent must be 0
		if (huffmanArray[i].parent == 0)
		{
			//compare rules: weight > size
			if (huffmanArray[i].weight < huffmanArray[*minWeightIndex].weight)
			{
				*secondMinWeightIndex = *minWeightIndex;
				*minWeightIndex = i;
			}
			//if weight equals, then compare their sizes
			else if (huffmanArray[i].weight == huffmanArray[*minWeightIndex].weight)
			{
				if (huffmanArray[i].size < huffmanArray[*minWeightIndex].size)
				{
					*secondMinWeightIndex = *minWeightIndex;
					*minWeightIndex = i;
				}
				//update *secondMinWeightIndex
				else
					*secondMinWeightIndex = i;
			}
			else
				;
		}

	//if *minWeightIndex not changed, then *secondMinWeightIndex is empty,
	//so travel from (j+1) and find the index.
	if (j == *minWeightIndex)
	{
		//initialize its value with endIndex because endIndex's parent is 0 and endIndex isn't *minWeightIndex
		*secondMinWeightIndex = boundary;
		//skip the *minWeightIndex and travel
		for (j++; j < boundary; j++)
		{
			if (huffmanArray[j].parent == 0)
			{
				//same compare rules.
				if (huffmanArray[j].weight < huffmanArray[*secondMinWeightIndex].weight)
					*secondMinWeightIndex = j;
				else if (huffmanArray[j].weight == huffmanArray[*secondMinWeightIndex].weight)
				{
					if (huffmanArray[j].size < huffmanArray[*secondMinWeightIndex].size)
						*secondMinWeightIndex = j;
				}
				else
					;
			}
		}
	}
}

bool encode(HuffmanTreeNode *huffmanArray, int size, string fileRes, string fileDes)
{
	//ifstream inf;	//file stream for input
	FILE* inf;
	ofstream outf;	//file stream for output
	char c;       //character has read
	char temp[100000];  //temp string to save current character's huffman code
	int start;    //current character's huffman code's start position in string
	int parent;
	int child;
	int index;   //current character's index in huffmanArray

	if (huffmanArray == NULL)
	{
		cout << "huffmanArray is NULL!" << endl;
		getch();
		return false;
	}
	inf=fopen(fileRes.c_str(),"r");
	if (inf==NULL)
	{
		cout << "Error caused by opening encodeFileRes!" << endl;
		return false;
	}
	outf.open(fileDes);
	if (!outf)
	{
		cout << "Error caused by opening encodeFileRes!" << endl;
		return false;
	}
	//when error occurs or file is over, loop exits
	while (!feof(inf))
	{
		int i;
		fread(&c, 1, 1, inf);
		//cout << "test::c " << c << endl;
		//find current character's index

		for (i = 1; i <= size; i++)
			if (huffmanArray[i].value == c)
				break;
		//if the character is not in characterSet
		if (i > size && !feof(inf))
		{
			cout << "Error occurs because of invalid character!" << c << endl;
			return false;
		}
		index = i;
		temp[size - 1] = '\0';
		start = size - 1;
		for (child = index, parent = huffmanArray[index].parent;
			parent != 0;
			child = parent, parent = huffmanArray[parent].parent)
		{
			if (huffmanArray[parent].lchild == child)
				temp[--start] = '0';
			else
				temp[--start] = '1';
		}
		for (int i = start; i < size - 1;i++) {
			outf << temp[i];
		}
	}
	return true;
}

bool decode(HuffmanTreeNode *huffmanArray, int size, string fileRes, string fileDes)
{
	FILE *fpIn;
	FILE *fpOut;
	char c;
	int cursor = size;

	if (huffmanArray == NULL)
	{
		fprintf(stderr, "\nhuffmanArray is NULL!"
			"Press any key to return...\n");
		getch();
		return false;
	}

	if ((fpIn = fopen(fileRes.c_str(), "rb")) == NULL)
	{
		fprintf(stderr, "\nError caused by opening encodeFileDes!"
			"Press any key to return...\n");
		getch();
		return false;
	}
	if ((fpOut = fopen(fileDes.c_str(), "wb")) == NULL)
	{
		fprintf(stderr, "\nError caused by opening decodeFileDes!"
			"Press any key to return...\n");
		getch();
		return false;
	}
	rewind(fpIn);
	rewind(fpOut);
	while (!feof(fpIn) && !ferror(fpIn) && !ferror(fpOut))
	{
		c = fgetc(fpIn);
		//if cursor goes to leaf
		if (huffmanArray[cursor].lchild == 0 && huffmanArray[cursor].rchild == 0)
		{
			//print the value and move cursor to root
			fputc(huffmanArray[cursor].value, fpOut);
			cursor = size;

		}
		if (c == '0')
			cursor = huffmanArray[cursor].lchild;
		else if (c == '1')
			cursor = huffmanArray[cursor].rchild;
		else
			;
	}

	fflush(fpOut);
	fclose(fpIn);
	fclose(fpOut);
	return true;
}