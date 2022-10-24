#include "opencv2/opencv.hpp"
#include <iostream>
#include "JJLIB.h"
using namespace cv;
using namespace std;

int lower_hue = 40;
int upper_hue = 80;
Mat mask;
Mat src_hsv;
void on_hue_changed(int, void*)
{
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask); // pick only lowerb~upperb color
	imshow("mask", T_RESIZE(mask));

}


int main()
{
	Mat src = imread("..\\Data\\candies.png", IMREAD_COLOR);
	cvtColor(src, src_hsv, COLOR_BGR2HSV);
	imshow("src", T_RESIZE(src));

	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);
	cv::waitKey(0);
	return 0;
}