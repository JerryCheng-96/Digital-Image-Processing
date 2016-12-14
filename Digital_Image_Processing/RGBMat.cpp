#include "RGBMat.h"



RGBMat::RGBMat()
{
	imageHeight = -1;
	imageWidth = -1;
	type = rgb;
	pr = NULL;
	pg = NULL;
	pb = NULL;
}

RGBMat::RGBMat(int ih, int iw)
{
	imageHeight = ih;
	imageWidth = iw;
	type = rgb;
	pr = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pg = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pb = (double*)malloc(imageHeight * imageWidth * sizeof(double));
}

RGBMat::RGBMat(DataMat * dm)
{
	imageHeight = dm->imageHeight;
	imageWidth = dm->imageWidth;
	type = rgb;
	pr = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pg = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pb = (double*)malloc(imageHeight * imageWidth * sizeof(double));

	switch (dm->type)
	{
	case hsl:
		HSLToRGB((HSLMat*)dm);
	case yuv:
		YUVToRGB((YUVMat*)dm);
	default:
		break;
	}
}

RGBMat::~RGBMat()
{
}





