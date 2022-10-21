#include "opencv2/opencv.hpp"
#include <iostream>
#include "JJLIB.h"
using namespace cv;
using namespace std;


int main()
{
	Mat src = imread("..\\Data\\big.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	int sigma = 10;
	
	//////////
	//Mat gauss = getGaussianKernel(8 * sigma + 1, sigma, CV_32FC1); //ksize = 8 * sigma + 1 , sigma : standard deviation
	//Mat gauss_transpose;
	//transpose(gauss, gauss_transpose);
	//filter2D(src, dst, -1, gauss, Point(-1, -1));
	//filter2D(dst, dst, -1, gauss_transpose, Point(-1, -1));
	//--or--//

	GaussianBlur(src, dst, Size(), (double)sigma); // Size() will decide kernel size automatically. kernel size must be odd number...(ext:  -4 0 +4 -> kernel size : 9)
	
	////////

	String text = format("sigma = %d", sigma);
	putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1.0, LINE_AA);

	imshow("src", T_RESIZE(src));
	imshow("dst", T_RESIZE(dst));
	waitKey(0);
	return 0;
}