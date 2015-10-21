#ifndef GEN_PATCHES
#define GEN_PATCHES

#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "glasseffect.h"

using namespace cv;
using namespace std;

int gen_patches (
	Mat src,                //source image
	Mat dst,                //destination 
	int ksize = 3           //size of patches
	);

#endif