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

void RGBMat::IntToDouble(int imageHeight, int imageWidth, BYTE * lpdata)
{
	for (int i = 0; i < imageHeight * imageWidth; i++)
	{
		pb[i] = lpdata[i * 3] / 255.0;
		pg[i] = lpdata[i * 3 + 1] / 255.0;
		pr[i] = lpdata[i * 3 + 2] / 255.0;
	}
}

void RGBMat::YUVToRGB(YUVMat * ym)
{
	for (int i = 0; i < (ym->imageHeight * ym->imageWidth); i++)
	{
		pr[i] = ym->py[i] + 1.13983*(ym->pv[i] - (128 / 255.0));
		pg[i] = ym->py[i] - 0.39465*(ym->pu[i] - (128 / 255.0)) - 0.58060*(ym->pv[i] - (128 / 255.0));
		pb[i] = ym->py[i] + 2.03211*(ym->pu[i] - (128 / 255.0));
	}
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

YUVMat::YUVMat(DataMat * dm)
{
	imageHeight = dm->imageHeight;
	imageWidth = dm->imageWidth;
	type = yuv;
	py = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pu = (double*)malloc(imageHeight * imageWidth * sizeof(double));
	pv = (double*)malloc(imageHeight * imageWidth * sizeof(double));

	if (dm->type == rgb)
	{
		RGBToYUV((RGBMat*)dm);
	}
}

YUVMat::~YUVMat()
{
}

void YUVMat::RGBToYUV(RGBMat * rm)
{
	for (int i = 0; i < (rm->imageHeight * rm->imageWidth); i++)
	{
		py[i] = 0.299*(rm->pr[i]) + 0.587*(rm->pg[i]) + 0.114*(rm->pb[i]);
		pu[i] = -0.169*(rm->pr[i]) - 0.331*(rm->pg[i]) + 0.5*(rm->pb[i]) + (128 / 255.0);
		pu[i] = 0.5*(rm->pr[i]) - 0.419*(rm->pg[i]) - 0.081*(rm->pb[i]) + (128 / 255.0);
	}
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
