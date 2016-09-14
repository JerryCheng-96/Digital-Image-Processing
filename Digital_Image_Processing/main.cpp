#include "BMPFile.h"

void main()
{
	BMPFile * bmpBW = readBMP("Lenna_BW.bmp");
	BMPFile * bmpGS = readBMP("Lenna_8-bit.bmp");
	BMPFile * bmpTC = readBMP("Lenna.bmp");
	
	writeBMP(bmpBW, "testwrite.bmp");
	writeBMP(bmpGS, "testwritegs.bmp");
	writeBMP(bmpTC, "testwritetc.bmp");
	writeBMP(GSToBin(bmpGS, 128), "t.bmp");
}