#include "main.h"

int main(int argc, char ** argv)
{
	/*  INPUT  */
	Mat src;

	bool show_time = false;
	bool verbose = false;
	bool show_other_filters = false;
	int iterations = 1;
	
	if ( argc > 1 )
		src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	else
	{
		src = imread("test.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		if ( src.empty() )
			src = imread("test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	}

	if ( src.empty() )
	{
		cout << "Either specify the path to the image or put \"test.bmp\" image in folder" << endl;
		return -1;
	}

	if ( argc > 2 )
	{
		string parm = argv[2];
		
		if ( parm[0] != '-' )
			cout << "bad parameters, check manual, executing with default parameters" << endl;
		else
		{
			for( int i = 1 ; i < parm.length() ; i ++ )
			{	
				if ( parm[i] == 't' )
					show_time = true;
				if ( parm[i] == 'v' )
					verbose = true;
				if ( parm[i] == 'o' )
					show_other_filters = true;
				if ( '2' <= parm[i] && parm[i] <= '9' )
					iterations = (parm[i] - '0');
			}
		}
	}

	/*  PROCESSING  */
	imshow("default image", src);

	//adding noise
	Mat noisy;
	src.copyTo(noisy);
	noise_gen(noisy, 0.25, 1);
	imshow("image with additive noise", noisy);

	Mat dst;
	Mat buffer;
	noisy.copyTo(buffer);
	noisy.copyTo(dst);

	//restoration
	double t;
	int r = 1;
	int w = dst.cols;
	int h = dst.rows;
	int dest = 0;

	if( show_time )
	{
		cout << "start" << endl;
		t = getTickCount();
	}

	for(int it  = 0 ; it < iterations ; ++it)
	{
		for (int i = r; i < h - r; i++)
		{
			for (int j = r; j < w-r; j++)
			{
				dest = aaf_get_dst(buffer, i, j, r);
				dst.at<uchar>(i, j) = aaf_get_approx(buffer, dest, i, j, r);
			}
		}
		dst.copyTo(buffer);
	}
	if( show_time )
	{
		t = ( getTickCount() - t ) / getTickFrequency();
		cout << "time passed = " << t << endl;
	}
	/*  other filters  */
	
	Mat median;
	medianBlur(noisy, median, 3);
	
	Mat gaussian;
	GaussianBlur(noisy, gaussian, Size(3,3), 0.0);

	/*  OUTPUT  */
	imwrite("aff_3x3.bmp",    dst);
	
	if( show_other_filters )
	{
		imwrite("gauss_3x3.bmp",  gaussian);
		imwrite("median_3x3.bmp", median);
	}

	if ( verbose )
	{
		imshow("restored image (aff)",      dst);
		if( show_other_filters )
		{
			imshow("restored image (median)",   median);
			imshow("restored image (gaussian)", gaussian);
		}
		waitKey(0);
	}

	return 0;
}