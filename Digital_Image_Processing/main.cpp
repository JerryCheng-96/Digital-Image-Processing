#include "BMPFile.h"

void main()
{
	BMPFile * bf = readGSBMP("Lenna_8-bit.bmp");
	int* histRes = GSHist(bf);
	
	for (int i = 0; i < 256; i++)
	{
		printf("%d\t", histRes[i]);
	}
}