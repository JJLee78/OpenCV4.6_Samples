#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	float kernel[3 * 3] = { -1, -1, 0,
							-1, 0, 1,
							0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, kernel);
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128); // Point(-1,-1) is anchor which means start from center of kernel box , / 128 is delta value. add this value to each element after filtering

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}