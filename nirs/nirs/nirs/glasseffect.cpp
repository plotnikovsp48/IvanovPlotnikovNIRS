#include"glasseffect.h"

uchar glasseffect(Mat img, int i, int j, int r)
{
	//int r = nn - 2;

	int dx = abs(img.at<uchar>(i, j - r) - img.at<uchar>(i, j + r));
	int dy = abs(img.at<uchar>(i - r, j) - img.at<uchar>(i + r, j));
	int dz1 = abs(img.at<uchar>(i - r, j - r) - img.at<uchar>(i + r, j + r));
	int dz2 = abs(img.at<uchar>(i - r, j + r) - img.at<uchar>(i + r, j - r));

	int min = dx; int alg = 0;
	if (min > dy)
	{
		min = dy;
		alg = 1;
	}
	if (min > dz1)
	{
		min = dz1;
		alg = 2;
	}
	if (min > dz2)
		alg = 3;

	if (alg == 0)
		return (img.at<uchar>(i, j - r) + img.at<uchar>(i, j + r))*.5;
	if (alg == 1)
		return (img.at<uchar>(i - r, j) + img.at<uchar>(i + r, j))*.5;
	if (alg == 2)
		return (img.at<uchar>(i - r, j - r) + img.at<uchar>(i + r, j + r))*.5;
	if (alg == 3)
		return (img.at<uchar>(i - r, j + r) + img.at<uchar>(i + r, j - r))*.5;
}