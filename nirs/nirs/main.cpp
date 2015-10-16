#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	cout << "test" << endl;
	namedWindow("test", CV_WINDOW_AUTOSIZE);
	waitKey(0);
	return 0;
}