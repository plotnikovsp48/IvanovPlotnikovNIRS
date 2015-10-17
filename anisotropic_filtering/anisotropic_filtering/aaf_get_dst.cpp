#include "aaf_get_dst.h"

int aaf_get_dst (
	Mat img, 
	int i, 
	int j, 
	int r
	)
{
	
	assert( !img.empty() && img.rows >= 3 && img.cols >= 3); 
	assert( img.type() == CV_8U );
	assert( i > 0 && j > 0 && r > 0);
	assert( i + r < img.rows && i - r >= 0 
		&&  j + r < img.cols && j - r >= 0 );


	int dx = abs(img.at<uchar>(i, j - r) - img.at<uchar>(i, j + r));
	int dy = abs(img.at<uchar>(i - r, j) - img.at<uchar>(i + r, j));
	int dz1 = abs(img.at<uchar>(i - r, j - r) - img.at<uchar>(i + r, j + r));
	int dz2 = abs(img.at<uchar>(i - r, j + r) - img.at<uchar>(i + r, j - r));

	int min = dx; 
	int alg = 0;
	
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

	return alg;
}