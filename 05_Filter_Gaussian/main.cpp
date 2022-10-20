#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	int sigmasize = 5;
	GaussianBlur(src, dst, Size(), (double)sigmasize); // sigma size must be odd number!!
	String text = format("sigma = %d", sigmasize);
	putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1.0, LINE_AA);

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}