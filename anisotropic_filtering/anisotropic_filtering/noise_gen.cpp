#include "noise_gen.h"

int noise_gen (
	Mat img,                    //input image (is changed after generation)
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
			/*
			int mean = 128;
			int stddev = 50;
			Mat noise(img.rows, img.cols, CV_8U);
			randn(noise, mean, stddev);
			addWeighted(img, 0.5, noise, 0.5, 0, img);
			*/
			int N = GAUSSIAN_ITERATIONS;
			srand((unsigned)time(0));
			for( int it = 0 ; it < N ; ++it )
				for (int i = 0; i < w * h * (intensity / (N + 0.0)); i++)
				{
					img.at<uchar>(rand() % h, rand() % w) = uchar(rand() % 256);  //высота на ширину
				}
		} break;

		default:
			return 0; 
			break;
	}

	return 0;
}