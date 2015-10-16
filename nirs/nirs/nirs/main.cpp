#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

int main()
{
	Mat img = imread("test2.jpg", 1);

	imshow("win_name", img);
	//imwrite("rec.jpg", img);
	waitKey(0);
	return 1;
}
