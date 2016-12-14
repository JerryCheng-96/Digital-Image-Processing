#include "DataMat.h"



DataMat::DataMat()
{
}


DataMat::~DataMat()
{
}

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

YUVMat::YUVMat()
{
	imageHeight = -1;
	imageWidth = -1;
	type = yuv;
	py = NULL;
	pu = NULL;
	pv = NULL;
}

YUVMat::YUVMat(int ih, int iw)
{
	imageHeight = ih;
	imageWidth = iw;
	type = yuv;
	py = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pu = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pv = (double*)malloc(imageHeight * imageWidth * sizeof(double));
}

YUVMat::~YUVMat()
{
}

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

HSLMat::~HSLMat()
{
}
