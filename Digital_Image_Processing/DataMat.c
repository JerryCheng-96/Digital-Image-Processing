#include "DataMat.h"

void Gaussian(int imageHeight, int imageWidth, int winSize, double * pData)
{
	double* gMat = (double*)malloc(winSize * winSize * sizeof(double));
	double* pMat = (double*)malloc(winSize * winSize * sizeof(double));

	GaussianMat(gMat, winSize, winSize / 6.0);

	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			GetWindow(imageHeight, imageWidth, pData, i, j, winSize, pMat);
			pData[i * imageWidth + j] = DotProduct(gMat, pMat, winSize);
		}
	}
}

void GaussianMat(double * pMat, int winSize, double sigma)
{
	int center = winSize / 2;
	double sum = 0;
	const double Pi = 3.1415926535;

	for (int i = 0; i < winSize; i++)
	{
		for (int j = 0; j < winSize; j++)
		{
			pMat[i*winSize + j] = (1 / (2 * Pi * sigma * sigma)) * exp(-((i - center)*(i - center) + (j - center)*(j - center)) / (2 * sigma * sigma));
			sum += pMat[i*winSize + j];
		}
	}

	for (int i = 0; i < winSize * winSize; i++)
	{
		pMat[i] /= sum;
	}

}

void GetWindow(int imageHeight, int imageWidth, double * pData,
	int x, int y, int winSize, double * pWindow)
{
	int i, j, u, v;

	for (i = 0; i < winSize; i++)
	{
		for (j = 0; j < winSize; j++)
		{
			u = x + i - winSize / 2;
			v = y + j - winSize / 2;
			if (u < 0)
			{
				u = -u - 1;
			}
			if (v < 0)
			{
				v = -v - 1;
			}
			if (u >= imageHeight)
			{
				u = 2 * imageHeight - u - 1;
			}
			if (v >= imageWidth)
			{
				v = 2 * imageWidth - v - 1;
			}
			pWindow[i * winSize + j] = pData[u * imageWidth + v];
		}
	}
}

double DotProduct(double * pMat1, double * pMat2, int size)
{
	double res = 0.0;

	for (int i = 0; i < size * size; i++)
	{
		res += pMat1[i] * pMat2[i];
	}
	return res;
}


void InitRGBMat(int imageHeight, int imageWidth, RGBMat* rm)
{
	rm->imageHeight = imageHeight;
	rm->imageWidth = imageWidth;
	rm->pb = (double*)malloc(rm->imageHeight * rm->imageWidth * sizeof(double));
	rm->pg = (double*)malloc(rm->imageHeight * rm->imageWidth * sizeof(double));
	rm->pr = (double*)malloc(rm->imageHeight * rm->imageWidth * sizeof(double));
}

void IntToDouble(int imageHeight, int imageWidth, BYTE * lpdata, RGBMat* rm)
{
	for (int i = 0; i < imageHeight * imageWidth; i++)
	{
		rm->pb[i] = lpdata[i * 3] / 255.0;
		rm->pg[i] = lpdata[i * 3 + 1] / 255.0;
		rm->pr[i] = lpdata[i * 3 + 2] / 255.0;
	}
}

void DoubleToInt(int imageHeight, int imageWidth, RGBMat * rm, BYTE * pData)
{
	for (int i = 0; i < imageHeight * imageWidth; i++)
	{
		pData[i * 3] = rm->pb[i] * 255.0;
		pData[i * 3 + 1] = rm->pg[i] * 255.0;
		pData[i * 3 + 2] = rm->pr[i] * 255.0;
	}
}

void YUVToRGB(YUVMat * ym, RGBMat* rm)
{
	for (int i = 0; i < (ym->imageHeight * ym->imageWidth); i++)
	{
		rm->pr[i] = ym->py[i] + 1.13983*(ym->pv[i] - (128 / 255.0));
		rm->pg[i] = ym->py[i] - 0.39465*(ym->pu[i] - (128 / 255.0)) - 0.58060*(ym->pv[i] - (128 / 255.0));
		rm->pb[i] = ym->py[i] + 2.03211*(ym->pu[i] - (128 / 255.0));
	}
}


void HSLToRGB(HSLMat * hm, RGBMat* rm)
{
	double q = 0;
	double p;
	double hk;
	double t[3] = { 0.0 };

	for (int i = 0; i < (hm->imageHeight * hm->imageWidth); i++)
	{
		if (hm->ps[i] == 0)
		{
			rm->pr[i] = rm->pg[i] = rm->pb[i] = hm->pl[i];
		}
		else
		{
			if (hm->pl[i] < 0.5)
			{
				q = hm->pl[i] * (1 + hm->ps[i]);
			}
			else
			{
				q = hm->pl[i] + hm->ps[i] - (hm->pl[i] * hm->ps[i]);
			}

			p = 2 * hm->pl[i] - q;
			hk = hm->ph[i] / 360.0;

			t[0] = hk + 0.33333333333;
			t[1] = hk;
			t[2] = hk - 0.33333333333;

			for (int j = 0; j < 3; j++)
			{
				if (t[j] < 0)
				{
					t[j] += 1.0;
				}
				else if (t[j] > 1)
				{
					t[j] -= 1.0;
				}

				if (t[j] < (1 / 6.0))
				{
					t[j] = p + ((q - p) * 6.0 * t[j]);
				}
				else if (t[j] >= (1 / 6.0) && t[j] < 0.5)
				{
					t[j] = q;
				}
				else if (t[j] >= 0.5 && t[j] < (2 / 3.0))
				{
					t[j] = p + ((q - p)*6.0*(2 / 3.0 - t[j]));
				}
				else
				{
					t[j] = p;
				}
			}

			rm->pr[i] = t[0];
			rm->pg[i] = t[1];
			rm->pb[i] = t[2];

		}
	}
}

/*
void HSLToRGB(int imageHeight, int imageWidth, double* ph, double* ps, double* pl, double* pr, double* pg, double* pb)
{
	double q = 0;
	double p;
	double hk;
	double t[3] = { 0.0 };

	for (int i = 0; i < (imageHeight * imageWidth); i++)
	{
		if (ps[i] == 0)
		{
			pr[i] = pg[i] = pb[i] = pl[i];
		}
		else
		{
			if (pl[i] < 0.5)
			{
				q = pl[i] * (1 + ps[i]);
			}
			else
			{
				q = pl[i] + ps[i] - (pl[i] * ps[i]);
			}

			p = 2 * pl[i] - q;
			hk = ph[i] / 360.0;

			t[0] = hk + 0.33333333333;
			t[1] = hk;
			t[2] = hk - 0.33333333333;

			for (int j = 0; j < 3; j++)
			{
				if (t[i] < 0)
				{
					t[i] += 1.0;
				}
				else if (t[i] > 1)
				{
					t[i] -= 1.0;
				}

				if (t[i] < (1 / 6.0))
				{
					t[i] = p + ((q - p) * 6 * t[i]);
				}
				else if (t[i] >= (1 / 6.0) && t[i] < 0.5)
				{
					t[i] = q;
				}
				else if (t[i] >= 0.5 && t[i] < (2 / 3.0))
				{
					t[i] = p + ((q - p)*6.0*(2 / 3.0 - t[i]));
				}
				else
				{
					t[i] = p;
				}
			}

			pr[i] = t[0];
			pg[i] = t[1];
			pb[i] = t[2];

		}
	}
}
*/

void InitYUVMat(int imageHeight, int imageWidth, YUVMat * ym)
{
	ym->imageHeight = imageHeight;
	ym->imageWidth = imageWidth;
	ym->py = (double*)malloc(ym->imageHeight * ym->imageWidth * sizeof(double));
	ym->pu = (double*)malloc(ym->imageHeight * ym->imageWidth * sizeof(double));
	ym->pv = (double*)malloc(ym->imageHeight * ym->imageWidth * sizeof(double));
}

void RGBToYUV(YUVMat* ym, RGBMat * rm)
{
	for (int i = 0; i < (rm->imageHeight * rm->imageWidth); i++)
	{
		ym->py[i] = 0.299*(rm->pr[i]) + 0.587*(rm->pg[i]) + 0.114*(rm->pb[i]);
		ym->pu[i] = -0.169*(rm->pr[i]) - 0.331*(rm->pg[i]) + 0.5*(rm->pb[i]) + (128 / 255.0);
		ym->pv[i] = 0.5*(rm->pr[i]) - 0.419*(rm->pg[i]) - 0.081*(rm->pb[i]) + (128 / 255.0);
	}
}

void InitHSLMat(int imageHeight, int imageWidth, HSLMat * hm)
{
	hm->imageHeight = imageHeight;
	hm->imageWidth = imageWidth;
	hm->ph = (double*)malloc(hm->imageHeight * hm->imageWidth * sizeof(double));
	hm->ps = (double*)malloc(hm->imageHeight * hm->imageWidth * sizeof(double));
	hm->pl = (double*)malloc(hm->imageHeight * hm->imageWidth * sizeof(double));
}

void RGBToHSL(RGBMat * rm, HSLMat* hm)
{
	double min = 0;
	double max = 0;

	for (int i = 0; i < (rm->imageHeight * rm->imageWidth); i++)
	{
		min = MinThree(rm->pr[i], rm->pg[i], rm->pr[i]);
		max = MaxThree(rm->pr[i], rm->pg[i], rm->pr[i]);

		hm->pl[i] = 0.5*(max + min);

		if (max == min)
		{
			hm->ph[i] = 0;
		}
		else if (max == rm->pr[i])
		{
			hm->ph[i] = 60 * ((rm->pg[i] - rm->pb[i]) / (max - min));
			if (rm->pg[i] < rm->pb[i])
			{
				hm->ph[i] += 360;
			}
		}
		else if (max == rm->pg[i])
		{
			hm->ph[i] = 60 * ((rm->pb[i] - rm->pr[i]) / (max - min)) + 120;
		}
		else if (max == rm->pb[i])
		{
			hm->ph[i] = 60 * ((rm->pr[i] - rm->pg[i]) / (max - min)) + 240;
		}

		if (hm->pl[i] == 0 || max == min)
		{
			hm->ps[i] = 0;
		}
		else if (hm->pl[i] <= 0.5)
		{
			hm->ps[i] = (max - min) / (2 * hm->pl[i]);
		}
		else if (hm->pl[i] > 0.5)
		{
			hm->ps[i] = (max - min) / (2 - 2 * hm->pl[i]);
		}
	}
}



double MinThree(double a, double b, double c)
{
	if (a <= b && a <= c)
	{
		return a;
	}
	else if (b <= c && b <= a)
	{
		return b;
	}
	else if (c <= a && c <= b)
	{
		return c;
	}
}

double MaxThree(double a, double b, double c)
{
	if (a >= b && a >= c)
	{
		return a;
	}
	else if (b >= c && b >= a)
	{
		return b;
	}
	else if (c >= a && c >= b)
	{
		return c;
	}
}
