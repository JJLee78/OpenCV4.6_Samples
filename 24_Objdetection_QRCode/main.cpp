#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\qrcode.png");
	Mat dst = src.clone();

	QRCodeDetector detector;
	//Mat frame;
	vector<Point> points;
	String info = detector.detectAndDecode(src, points);
	if (!info.empty())
	{
		polylines(dst, points, true, Scalar(0, 0, 255), 2);
		putText(dst, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255));
	}


	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}