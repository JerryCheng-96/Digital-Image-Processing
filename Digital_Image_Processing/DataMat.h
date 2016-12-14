#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifndef _STDIO_H_
#include <stdio.h>
#define _STDIO_H_
#endif // !_STDIO_H_
#ifndef _STDLIB_H_
#include <stdlib.h>
#define _STDLIB_H_
#endif // !_STDLIB_H_

typedef unsigned char BYTE;

class DataMat
{
public:
	DataMat();
	~DataMat();
	enum MatType { rgb = 0, hsl = 1, yuv = 2 };

	int imageHeight;
	int imageWidth;
	MatType type;

	static void Gaussian(int imageHeight, int imageWidth, int winSize, double* comp);
};


class RGBMat :
	public DataMat
{
public:
	RGBMat();
	RGBMat(int ih, int iw);
	RGBMat(DataMat* dm);
	~RGBMat();

	double* pr;
	double* pg;
	double* pb;

	void IntToDouble(int imageHeight, int imageWidth, BYTE * lpdata);
	void HSLToRGB(HSLMat* hm);
	void YUVToRGB(YUVMat* ym);

};

class YUVMat :
	public DataMat
{
public:
	YUVMat();
	YUVMat(int ih, int iw);
	YUVMat(DataMat* dm);
	~YUVMat();

	double* py;
	double* pu;
	double* pv;

	void RGBToYUV(RGBMat* rm);
};

class HSLMat :
	public DataMat
{
public:
	HSLMat();
	HSLMat(int ih, int iw);
	HSLMat(DataMat* dm);
	~HSLMat();

	double* ph;
	double* ps;
	double* pl;

	void RGBToHSL(RGBMat* rm);
};

