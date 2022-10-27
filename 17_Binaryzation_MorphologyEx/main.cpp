#include "opencv2/opencv.hpp"
#include <iostream>
#include "JJLIB.h"

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\big.bmp", IMREAD_GRAYSCALE);
	
	Mat bin;
	//threshold(src, bin, 50, 255, THRESH_BINARY);
	adaptiveThreshold(src, bin, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 51, 3);



	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());

	imshow("src", T_RESIZE(src));
	imshow("dst", T_RESIZE(bin));
	imshow("Opening", T_RESIZE(dst1));
	imshow("Closing", T_RESIZE(dst2));;
	waitKey(0);
	return 0;
}