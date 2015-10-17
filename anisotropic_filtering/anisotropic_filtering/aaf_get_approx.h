#ifndef AAF_GET_APPROX
#define AAF_GET_APPROX

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

/*  
Calculate the approximate value for "noise" point,
works with 3*3 neighborhoods
-----------------------------------------------------------
returns intensity ("color")
-----------------------------------------------------------
*/
uchar aaf_get_approx (
	Mat img,		//source image
	int alg,        //destination code for approx
	int i,          //x coordinate in [0, cols]
	int j,          //y coordinate in [0, rows]
	int r           //r = radius of square neighborhood (2n+1)*(2n+1)
	);

#endif