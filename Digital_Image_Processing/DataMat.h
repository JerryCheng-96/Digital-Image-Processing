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

#ifndef _MATH_H_
#include <math.h>
#define _MATH_H_
#endif // !_MATH_H_


typedef unsigned char BYTE;

typedef	struct RM
{
	int imageHeight;
	int imageWidth;
	double* pr;
	double* pg;
	double* pb;
} RGBMat;

typedef struct YM
{
	int imageHeight;
	int imageWidth;
	double* py;
	double* pu;
	double* pv;
} YUVMat;

typedef struct HM
{
	int imageHeight;
	int imageWidth;
	double* ph;
	double* ps;
	double* pl;
} HSLMat;


void Gaussian(int imageHeight, int imageWidth, int winSize, double* pData);
void GaussianMat(double* pMat, int winSize, double sigma);
void GetWindow(int imageHeight, int imageWidth, double* pData, int x, int y, int winSize, double* pWindow);
double DotProduct(double* pMat1, double* pMat2, int size);

void InitRGBMat(int imageHeight, int imageWidth, RGBMat* rm);
void IntToDouble(int imageHeight, int imageWidth, BYTE * lpdata, RGBMat* rm);
void DoubleToInt(int imageHeight, int imageWidth, RGBMat* rm, BYTE* pData);
void HSLToRGB(HSLMat* hm, RGBMat* rm);
//void HSLToRGB(int imageHeight, int imageWidth, double* ph, double* ps, double* pl, double* pr, double* pg, double* pb);
void YUVToRGB(YUVMat* ym, RGBMat* rm);

void InitYUVMat(int imageHeight, int imageWidth, YUVMat* ym);
void RGBToYUV(YUVMat* ym, RGBMat* rm);

void InitHSLMat(int imageHeight, int imageWidth, HSLMat* hm);
void RGBToHSL(RGBMat* rm, HSLMat* hm);
double MinThree(double a, double b, double c);
double MaxThree(double a, double b, double c);
