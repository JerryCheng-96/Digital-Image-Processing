#include "BMPFile.h"

BMPFile * readGSBMP(char * path)
{
	FILE* bitmap = NULL;
	bmpFileHeader* fileHeader = NULL;
	bmpInfoHeader* infoHeader = NULL;
	unsigned char* pixelArray = NULL;
	BMPFile* bmpFile = NULL;

	bitmap = fopen(path, "rb");
	if (bitmap == NULL)
	{
		printf("File open failed.\n");
		return NULL;
	}

	fseek(bitmap, 2, SEEK_SET);

	fileHeader = (bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	infoHeader = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));

	fread(fileHeader, sizeof(bmpFileHeader), 1, bitmap);
	fread(infoHeader, sizeof(bmpInfoHeader), 1, bitmap);

	if (infoHeader->plane == 1 && infoHeader->depth == 8 && infoHeader->compression == 0)
	{
		pixelArray = (unsigned char*)calloc(infoHeader->imageSize, sizeof(unsigned char));
		fseek(bitmap, fileHeader->offset, SEEK_SET);
		fread(pixelArray, sizeof(unsigned char), infoHeader->imageSize, bitmap);
		bmpFile = (BMPFile*)malloc(sizeof(BMPFile));
		bmpFile->fileHeader = fileHeader;
		bmpFile->infoHeader = infoHeader;
		bmpFile->pixelArray = pixelArray;
		return bmpFile;
	}
	else
	{
		printf("File not legal.\n");
		return NULL;
	}
}

int * GSHist(BMPFile * bf)
{
	int * hist = (int*)malloc(256 * sizeof(int));
	unsigned char* pixelArray = bf->pixelArray;

	for (int j = 0; j < 256; j++)
	{
		hist[j] = 0;
	}
	
	for (int i = 0; i < bf->infoHeader->imageSize; i++)
	{
		hist[(int)pixelArray[i]]++;
	}

	return hist;
}
