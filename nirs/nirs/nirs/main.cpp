#include"glasseffect.h"

int main()
{
	Mat img1 = imread("test2.jpg", 1);

	//imshow("win_name", img);
	//imwrite("rec.jpg", img); //сохранение картинки
	int w = img1.cols;
	int h = img1.rows;
	Mat img;
	if (img1.type() != CV_8U)
	{
		cv::cvtColor(img1, img, CV_BGR2GRAY);
		cv::cvtColor(img1, img1, CV_BGR2GRAY);
	}

	//const int del = 1;

	//cout << w << " " << h;

	int r = 1;

	srand((unsigned)time(0));
	for (int i = 0; i < w*h*.25; i++)
	{
		img1.at<uchar>(rand() % h, rand() % w) = uchar(rand() % 256);//высота на ширину
	}


	GaussianBlur(img1, img, Size(3,3), 0.0);
	//medianBlur(img1, img, 3);
	/*for (int i = r; i < h - r; i++)
	{
		for (int j = r; j < w-r; j++)
		{
			img.at<uchar>(i, j) = glasseffect(img1, i, j, r);
		}
	}*/

	Mat img2;
	img.copyTo(img2);

	
	imshow("1", img);
	/*for (int i = r; i < h - r; i++)
	{
		for (int j = r; j < w - r; j++)
		{
			img2.at<uchar>(i, j) = glasseffect(img, i, j, r);
		}
	}*/
	//medianBlur(img, img2, 1);
	imshow("2", img1);
	//imshow("3", img2);
	cv::waitKey(0);
	return 1;
}
