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

	if (infoHeader->plane == 1 && infoHeader->compression == 0 && infoHeader->weight % 4 == 0
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
	if (bitmap == NULL)
	{
		return;
	}

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
	if (ori == NULL)
	{
		return NULL;
	}

	bmpFileHeader* fHeader = (bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* iHeader = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	BMPFile* res = (BMPFile*)malloc(sizeof(BMPFile));
	unsigned char* pixelArray;
	int imageSize = 0;
	int rowSize = 0;
	int rowNum = 0;
	int blanksToFill = 0;
	int currPos = 0;
	unsigned char currByte = 0;
	int resolution = ori->infoHeader->height * ori->infoHeader->weight;

	if (ori->infoHeader->weight % 32 != 0)
	{
		rowSize = (ori->infoHeader->weight / 32 + 1) * 4;
		blanksToFill = rowSize - ori->infoHeader->weight / 8;
		
	}
	else
	{
		rowSize = ori->infoHeader->weight / 8;
		blanksToFill = 0;
	}
	imageSize = rowSize * ori->infoHeader->height;

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

	int i = 0;
	currPos = 0;
	while (i < resolution)
	{
		if (ori->pixelArray[i] > thres)
		{
			currByte += 128 >> (i % 8);
		}
		if ((i + 1) % 8 == 0)
		{
			pixelArray[currPos] = currByte;
			currByte = 0;
			currPos++;
		}
		if ((i + 1) % iHeader->weight == 0)
		{
			currPos += blanksToFill;
		}
		i++;
	}
	
	return res;

}

int * GSHist(BMPFile * bf)
{
	if (bf == NULL)
	{
		return NULL;
	}

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

int * findGSHistValley(int * hist)
{
	int * res = (int *)calloc(256, sizeof(int));
	int * newHist = (int *)calloc(256, sizeof(int));
	int cnt = 0;

	if (hist == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < 256; i++)
	{
		res[i] = -1;
		newHist[i] = -1;
	}

	for (int j = 1; j < 255; j++)
	{
		if (hist[j] < hist[j - 1] && hist[j] < hist[j + 1])
		{
			res[cnt] = j;
			newHist[cnt] = hist[j];
			cnt++;
		}
	}

	return res;
}


