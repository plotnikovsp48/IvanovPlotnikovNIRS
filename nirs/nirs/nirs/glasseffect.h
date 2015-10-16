#ifndef GLASSEFFECT
#define GLASSEFFECT

#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<ctime>

using namespace cv;
using namespace std;

uchar glasseffect(Mat img, int i, int j, int nn);

#endif