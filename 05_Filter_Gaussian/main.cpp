#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int64 t0;
int64 t1;
#define TBEGIN t0 = cv::getTickCount();
#define TEND t1 = cv::getTickCount();
#define TRES cout << "Elapsed time : " << (t1 / t0) * 1000 / getTickFrequency() << endl;

int main()
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	int sigma = 9;
	TBEGIN;
	Mat gauss = getGaussianKernel(8 * sigma + 1, sigma, CV_32FC1); //ksize = 8 * sigma + 1
	GaussianBlur(src, dst, Size(), (double)sigma); // sigma size must be odd number!!
	cout << "--Gaussian Kernerl--" << endl;
	//cout << gauss;
	TEND;
	TRES;
	String text = format("sigma = %d", sigma);
	putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1.0, LINE_AA);

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}