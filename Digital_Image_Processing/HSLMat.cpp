#include "HSLMat.h"

HSLMat::HSLMat()
{
	imageHeight = -1;
	imageWidth = -1;
	type = hsl;
	ph = NULL;
	ps = NULL;
	pl = NULL;
}

HSLMat::HSLMat(int ih, int iw)
{
	imageHeight = ih;
	imageWidth = iw;
	type = hsl;
	ph = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	ps = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pl = (double*)malloc(imageHeight * imageWidth * sizeof(double));
}

HSLMat::HSLMat(DataMat * dm)
{
	imageHeight = dm->imageHeight;
	imageWidth = dm->imageWidth;
	type = hsl;
	ph = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	ps = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pl = (double*)malloc(imageHeight * imageWidth * sizeof(double));

	if (dm->type == rgb)
	{
		RGBToHSL((RGBMat*)dm);
	}
}

HSLMat::~HSLMat()
{
}

