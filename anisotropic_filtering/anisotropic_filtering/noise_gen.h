#ifndef NOISE_GEN
#define NOISE_GEN

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <ctime>

#define SIMPLE_NOISE 0
#define GAUSSIAN_NOISE 1
#define GAUSSIAN_ITERATIONS 20

using namespace cv;

int noise_gen (
	Mat img,                    //input image (is changed after generation)
	double intensity = 0.25,    //intensity of noise
	int type = SIMPLE_NOISE   //type of noise generator
	);

#endif