
#include "gen_patches.h"

int gen_patches (
	Mat src,                //source image
	Mat dst,                //destination 
	int ksize               //size of patches
	)
{
	assert( !src.empty() && src.cols >= ksize && src.rows >= ksize );
	int a_test_0 = ksize % 2;
	assert( ksize > 0  && a_test_0 );

	if( src.type() != CV_8U )
		cvtColor(src, dst, CV_BGR2GRAY);
	else
		src.copyTo(dst);

	Mat ** patches_list = new Mat *[src.cols - ksize];

	for( int i = 0 ; i < src.cols - ksize ; ++i )
		patches_list[i] = new Mat [src.rows - ksize];

	for( int i = 0 ; i < src.cols - ksize ; ++i )
		for( int j = 0 ; j < src.rows - ksize ; ++j )
		{
			patches_list[i][j] = Mat( src, Rect(i, j, ksize, ksize) );

			//dst.at<uchar>(j + ksize/2, i + ksize/2) = glasseffect(patches_list[i][j], ksize/2, ksize/2, ksize);
			//imshow("test", patches_list[i][j]);
			//waitKey(10);
		};
	

	for( int i = 0 ; i < src.cols - ksize ; ++i )
		for( int j = 0 ; j < src.rows - ksize ; ++j )
		{
			dst.at<uchar>(j + ksize/2, i + ksize/2) = glasseffect(patches_list[i][j], ksize/2, ksize/2, ksize);
		}

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}