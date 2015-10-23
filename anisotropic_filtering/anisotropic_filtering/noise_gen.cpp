#include "noise_gen.h"

int noise_gen (
	Mat img,                    //input image (is changed after generation)
	int gauss_stdev,            //standard deviation for AWGN
	double intensity,			//intensity of noise
	int type					//type of noise generator
	)
{
	assert( !img.empty() ) ; 
	assert( intensity > 0.0 && intensity < 1.0 );

	int w = img.cols;
	int h = img.rows;
	switch( type )
	{
		
		case SIMPLE_NOISE : 
		{
			srand((unsigned)time(0));
			for (int i = 0; i < w * h * intensity; i++)
			{
				img.at<uchar>(rand() % h, rand() % w) = uchar(rand() % 256);  //высота на ширину
			}
		} break;

		case GAUSSIAN_NOISE :
		{

			int mean = 0;
			int stddev = 15;
			Mat noise(img.rows, img.cols, CV_8S);
			randn(noise, mean, stddev);
			//addWeighted(img, 0.7, noise, 0.7, 0, img);
			for( int i = 0 ; i < img.rows ; ++i )
				for( int j = 0 ; j < img.cols ;++j )
					img.at<uchar>(i,j) = cv::saturate_cast<uchar>(img.at<uchar>(i,j)+noise.at<char>(i,j));

		} break;

		default:
			return 0; 
			break;
	}

	return 0;
}