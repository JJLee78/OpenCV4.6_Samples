#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type(), Scalar(0));
	

	//Median filter//
	/*int kernelSIze = 3;
	Mat kernel = Mat(Size(kernelSIze, kernelSIze), src.type());
	for (int i = 1; i < src.rows - 1; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			dst.at<uchar>(i, j) = src.at<uchar>(i, j);
			vector<uchar> filter;
			for (int m = i-1; m < i+1; m++)
			{
				for (int n = j - 1; n < j+1 + 1; n++)
				{
					filter.push_back(src.at<uchar>(m, n));
				}
			}
			sort(filter.begin(), filter.end());
			dst.at<uchar>(i, j) = filter[(kernelSIze * kernelSIze) / 2];
		}
	}*/
	//----or----//
	
	
	// add noise (randn)
	Mat noise = Mat(src.size(), src.type());
	int stddev = 10;
	randn(noise, 0, stddev);
	add(src, noise, src, Mat(), CV_8U);
	//


	// add noise (salt-pepper)
	//int pick = src.total() * 0.05;
	//for (int i = 0; i < pick; i++)
	//{
	//	src.at<uchar>(rand() % src.cols, rand() % src.rows) = rand() % 2 == 1 ? 255 : 0;  //Add NOISE
	//}
	//

	medianBlur(src, dst, 3); //denoising

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	
	return 0;
}