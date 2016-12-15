#include "BMPFile.h"
#include "DataMat.h"
#define WINSIZE 7

void main()
{
	//BMPFile * bmpBW = readBMP("Lenna_BW.bmp");
	BMPFile * bmpTC = NULL;
	RGBMat rm = { -1,-1,NULL,NULL,NULL };
	YUVMat ym = { -1,-1,NULL,NULL,NULL };
	HSLMat hm = { -1,-1,NULL,NULL,NULL };
	bmpTC = readBMP("output.bmp");
	unsigned char* pa = (unsigned char*)malloc(3 * bmpTC->infoHeader->height * bmpTC->infoHeader->weight * sizeof(unsigned char));
	
	InitRGBMat(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, &rm);
	IntToDouble(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, bmpTC->pixelArray, &rm);
	free(bmpTC->pixelArray);
	/*
	InitYUVMat(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, ym);
	RGBToYUV(ym, rm);
	Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, ym->py);
	YUVToRGB(ym, rm);	

	Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, rm->pr);
	Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, rm->pg);
	Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, rm->pb);

*/	
	
	InitHSLMat(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, &hm);

	RGBToHSL(&rm, &hm);
	Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, hm.pl);
	HSLToRGB(&hm, &rm);

	DoubleToInt(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, &rm, pa);
	bmpTC->pixelArray = pa;
	writeBMP(bmpTC, "testwritetc.bmp");


	
		
	//writeBMP(bmpBW, "testwrite.bmp");
	//writeBMP(bmpGS, "testwritegs.bmp");
	//writeBMP(bmpTC, "testwritetc.bmp");
	//writeBMP(GSToBin(bmpGS, 135), "t.bmp");

}

