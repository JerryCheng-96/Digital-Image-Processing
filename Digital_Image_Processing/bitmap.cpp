#include "BMPFile.h"

BMPFile * readBMP(char * path)
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

	if (infoHeader->plane == 1 && infoHeader->compression == 0 
		&& (infoHeader->depth == 1 || infoHeader->depth == 8 || infoHeader->depth == 24))
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

	fclose(bitmap);
	bitmap = NULL;
}

void writeBMP(BMPFile * bitmap, char * path)
{
	FILE * dest = fopen(path, "wb");

	if (dest == NULL)
	{
		printf("File open failed.\n");
	}
	
	fwrite("BM", sizeof(unsigned char), 2, dest);
	//fseek(dest, 2, SEEK_SET);
	fwrite(bitmap->fileHeader, sizeof(bmpFileHeader), 1, dest);		//Writing file header
	fwrite(bitmap->infoHeader, sizeof(bmpInfoHeader), 1, dest);		//Writing info header

	switch (bitmap->infoHeader->depth)								//Writing color table
	{
	case 1:fwrite(binaryColorTable(), sizeof(int), 2, dest);
		break;
	case 8:fwrite(GSColorTable(), sizeof(int), 256, dest);
		break;
	default:
		break;
	}

	fwrite(bitmap->pixelArray, sizeof(unsigned char), 
		bitmap->infoHeader->imageSize, dest);						//Writing the pixel data

	fclose(dest);
	dest = NULL;
}

int * binaryColorTable()
{
	int * colorTable = (int*)calloc(2, sizeof(int));
	colorTable[0] = 0;
	colorTable[1] = 0xFFFFFF;
	return colorTable;
}

int * GSColorTable()
{
	int * colorTable = (int*)calloc(256, sizeof(int));
	for (int i = 0; i < 256; i++)
	{
		colorTable[i] = i * 0x10101;
	}
	return colorTable;
}

BMPFile * GSToBin(BMPFile * ori, unsigned char thres)
{
	bmpFileHeader* fHeader = (bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* iHeader = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	BMPFile* res = (BMPFile*)malloc(sizeof(BMPFile));
	unsigned char* pixelArray;
	int imageSize = 0;

	if (ori->infoHeader->imageSize % 7 != 0)
	{
		imageSize = ori->infoHeader->imageSize / 7 + 1;
	}
	else
	{
		imageSize = ori->infoHeader->imageSize / 7;
	}

	pixelArray = (unsigned char*)calloc(imageSize, sizeof(unsigned char));

	res->fileHeader = fHeader;
	res->infoHeader = iHeader;
	res->pixelArray = pixelArray;

	*fHeader = *(ori->fileHeader);
	*iHeader = *(ori->infoHeader);

	iHeader->depth = 1;
	iHeader->imageSize = imageSize;
	fHeader->offset = 0x3e;
	fHeader->size = 0x3e + iHeader->imageSize;

	for (int j = 0; j < imageSize; j++)
	{
		pixelArray[j] = (unsigned char)0;
	}

	for (int i = 0; i < ori->infoHeader->imageSize; i++)
	{
		if (ori->pixelArray[i] > thres)
		{
			res->pixelArray[i / 7] += 128 >> (i % 7);
		}
	}

	return res;

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