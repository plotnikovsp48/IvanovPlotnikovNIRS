#ifndef AAF_GET_DST
#define AAF_GET_DST

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

/*  
Calculate the "best" destination for further approximation,
works with (2r+1)*(2r+1) neighborhoods
works with grayscale CV_8U images
-----------------------------------------------------------
returns 0, 1, 2, 3 for 3*3 neighborhood
-----------------------------------------------------------
*/
int aaf_get_dst (
	Mat img,		//source image
	int i,          //x coordinate in [0, cols]
	int j,          //y coordinate in [0, rows]
	int r           //r = radius of square neighborhood (2n+1)*(2n+1)
	);

#endif