#include "BMPFile.h"
#include "DataMat.h"
#define WINSIZE 17

void main()
{
	//BMPFile * bmpBW = readBMP("Lenna_BW.bmp");
	BMPFile * bmpTC = readBMP("SSCplx.bmp");
	RGBMat* rm = (RGBMat*)malloc(sizeof(RGBMat));
	unsigned char* pa = (unsigned char*)malloc(3 * bmpTC->infoHeader->height * bmpTC->infoHeader->weight * sizeof(unsigned char));
		
	IntToDouble(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, bmpTC->pixelArray, rm);
	//Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, rm->pr);
	//Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, rm->pg);
	Gaussian(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, WINSIZE, rm->pb);
	DoubleToInt(bmpTC->infoHeader->height, bmpTC->infoHeader->weight, rm, pa);
	bmpTC->pixelArray = pa;
	writeBMP(bmpTC, "testwritetc.bmp");
		
	//writeBMP(bmpBW, "testwrite.bmp");
	//writeBMP(bmpGS, "testwritegs.bmp");
	//writeBMP(bmpTC, "testwritetc.bmp");
	//writeBMP(GSToBin(bmpGS, 135), "t.bmp");

}