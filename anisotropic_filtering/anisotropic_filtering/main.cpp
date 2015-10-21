#include "main.h"

int main(int argc, char ** argv)
{
	/*  INPUT  */
	Mat src;

	bool show_time = true;
	bool verbose = true;
	bool show_other_filters = true;
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
	noisy.copyTo(dst);

	//restoration
	double t;
	const int r = 1;
	const int w = dst.cols;
	const int h = dst.rows;

	if( show_time )
	{
		cout << "start" << endl;
		t = getTickCount();
	}

	uchar** arrayP = new uchar*[h];
	for (int i = 0; i < h; i++)
	{
		arrayP[i] = new uchar[w];
	}
	//omp_set_num_threads(4);
	//#pragma omp parallel for
	for(int it  = 0 ; it < iterations ; ++it)
	{
		//#pragma omp parallel for
		for (int i = r; i < h - r; i++)
		{
			//#pragma omp parallel for
			for (int j = 0; j < w; j++)
			{
				arrayP[i][j] = dst.at<uchar>(i, j);
			}
		}

		//#pragma omp parallel for
		for (int i = r; i < h - r; i++)
		{
			//#pragma omp parallel for
			for (int j = r; j < w - r; j++)
			{
				uchar ax = arrayP[i][j - r]; uchar bx = arrayP[i][j + r];
				uchar ay = arrayP[i - r][j]; uchar by = arrayP[i + r][j];
				uchar az1 = arrayP[i - r][j - r]; uchar bz1 = arrayP[i + r][j + r];
				uchar az2 = arrayP[i - r][j + r]; uchar bz2 = arrayP[i + r][j - r];


				uchar dx = abs(ax - bx);
				uchar dy = abs(ay - by);
				uchar dz1 = abs(az1 - bz1);
				uchar dz2 = abs(az2 - bz2);

				uchar min = dx;
				uchar alg = 0;

				if (min > dy)
				{
					min = dy;
					alg = 1;
				}
				if (min > dz1)
				{
					min = dz1;
					alg = 2;
				}
				if (min > dz2)
					alg = 3;


				if (alg == 0)
					dst.at<uchar>(i, j) = (ax + bx)*.5;
				if (alg == 1)
					dst.at<uchar>(i, j) = (ay + by)*.5;
				if (alg == 2)
					dst.at<uchar>(i, j) = (az1 + bz1)*.5;
				if (alg == 3)
					dst.at<uchar>(i, j) = (az2 + bz2)*.5;
			}
		}
	}
	if( show_time )
	{
		t = ( getTickCount() - t ) / getTickFrequency();
		cout << "time passed = " << t << endl;
	}
	/*  other filters  */
	t = getTickCount();
	Mat median;
	medianBlur(noisy, median, 3);
	if (show_time)
	{
		t = (getTickCount() - t) / getTickFrequency();
		cout << "time passed = " << t << endl;
	}
	t = getTickCount();

	Mat gaussian;
	GaussianBlur(noisy, gaussian, Size(3,3), 0.0);
	if (show_time)
	{
		t = (getTickCount() - t) / getTickFrequency();
		cout << "time passed = " << t << endl;
	}
	/*  OUTPUT  */
	imwrite("aff_3x3.bmp",    dst);
	
	if( show_other_filters )
	{
		imwrite("gauss_3x3.bmp",  gaussian);
		imwrite("median_3x3.bmp", median);
	}
	//cout << (1 >> 1) << " " << (1 << 1);
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
	//waitKey(0);

	return 0;
}