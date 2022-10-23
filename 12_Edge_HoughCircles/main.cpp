#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat T_RESIZE(Mat src)
{
	int a, b, screenWidth, screenHeight;
	float newRatio;
	float newHeightRatio;
	namedWindow("size_temp", WND_PROP_FULLSCREEN);
	setWindowProperty("size_temp", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	Rect win = getWindowImageRect("size_temp");
	destroyWindow("size_temp");

	if (src.cols < src.rows)
	{
		if (win.height <= src.rows)
		{
			newRatio = (float)win.height / (float)src.rows;
			Mat dst;
			cv::resize(src, dst, Size(src.cols * newRatio - 80, src.rows * newRatio - 80));  //subtract TASKBAR SIZE
			return dst;
		}
	}
	else if (src.cols >= src.rows)
	{
		if (win.width <= src.cols)
		{
			newRatio = (float)win.width / (float)src.cols;
			Mat dst;
			cv::resize(src, dst, Size(src.cols * newRatio - 80, src.rows * newRatio - 80));
			return dst;
		}
	}
	return src;
}

int main()
{
	Mat src = imread("..\\Data\\big.bmp", IMREAD_GRAYSCALE);
	Mat dst;

	Mat blurred;
	blur(src, blurred, Size(3, 3));
	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 27);

	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles)
	{
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	
	imshow("src", T_RESIZE(src));
	imshow("HoughCircles", T_RESIZE(dst));
	waitKey(0);


	return 0;
}