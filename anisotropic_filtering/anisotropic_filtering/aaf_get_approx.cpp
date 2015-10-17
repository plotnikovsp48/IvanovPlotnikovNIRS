#include "aaf_get_approx.h"

uchar aaf_get_approx (
	Mat img,		//source image
	int alg,        //destination code for approx
	int i,          //x coordinate in [0, cols]
	int j,          //y coordinate in [0, rows]
	int r           //r = radius of square neighborhood (2n+1)*(2n+1)
	)
{
	assert( !img.empty() && img.rows >= 3 && img.cols >= 3); 
	assert( img.type() == CV_8U );
	assert( i > 0 && j > 0 && r > 0);
	assert( i + r < img.rows && i - r >= 0 
		&&  j + r < img.cols && j - r >= 0 );
	
	assert( alg >= 0 && alg < 4 );
	
	if (alg == 0)
		return (img.at<uchar>(i, j - r) + img.at<uchar>(i, j + r))*.5;
	if (alg == 1)
		return (img.at<uchar>(i - r, j) + img.at<uchar>(i + r, j))*.5;
	if (alg == 2)
		return (img.at<uchar>(i - r, j - r) + img.at<uchar>(i + r, j + r))*.5;
	if (alg == 3)
		return (img.at<uchar>(i - r, j + r) + img.at<uchar>(i + r, j - r))*.5;
}
