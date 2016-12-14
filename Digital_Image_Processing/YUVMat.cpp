#include "YUVMat.h"



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

