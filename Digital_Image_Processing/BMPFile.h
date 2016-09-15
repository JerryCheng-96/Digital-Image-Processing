#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifndef _STDIO_H_
#include <stdio.h>
#define _STDIO_H_
#endif // !_STDIO_H_
#ifndef _STDLIB_H_
#include <stdlib.h>
#define _STDLIB_H_
#endif // !_STDLIB_H_

typedef struct FileHeader
{
	//unsigned char type;
	unsigned int size;
	unsigned short resv1;
	unsigned short resv2;
	unsigned int offset;
}bmpFileHeader;

typedef struct InfoHeader
{
	unsigned int headerSize;
	int weight;
	int height;
	unsigned short plane;
	unsigned short depth;
	unsigned int compression;
	unsigned int imageSize;
	int wres;
	int hres;
	unsigned int numberColor;
	unsigned int numberImportantColor;
}bmpInfoHeader;

typedef struct BMPFileContainer
{
	bmpFileHeader* fileHeader;
	bmpInfoHeader* infoHeader;
	unsigned char* pixelArray;
}BMPFile;


BMPFile* readBMP(char* path);
void writeBMP(BMPFile * bitmap, char * path);

int * binaryColorTable();
int * GSColorTable();

BMPFile * GSToBin(BMPFile * ori, unsigned char thres);
//BMPFile * GSToBinByBit(BMPFile * ori, int bit);

int* GSHist(BMPFile* bf);
int* findGSHistValley(int * hist);
//int findMidNumber(int * hist);