#include "BMPFile.h"

void main()
{
	BMPFile * bmpBW = readBMP("Lenna_BW.bmp");
	BMPFile * bmpGS = readBMP("applepickinggs.bmp");
	BMPFile * bmpTC = readBMP("Lenna.bmp");
	
	//writeBMP(bmpBW, "testwrite.bmp");
	//writeBMP(bmpGS, "testwritegs.bmp");
	//writeBMP(bmpTC, "testwritetc.bmp");
	writeBMP(GSToBinByBit(bmpGS, 2), "t.bmp");

}