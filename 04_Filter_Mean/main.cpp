#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	int ksize = 5;
	/*Mat kernel = Mat(Size(ksize, ksize), CV_32FC1);
	kernel = 1 / (float)(ksize * ksize);
	filter2D(src, dst, -1, kernel, Point(-1, -1), 0);*/
	//or
	blur(src, dst, Size(ksize, ksize)); // Bigger kernel size, More blurring 

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}