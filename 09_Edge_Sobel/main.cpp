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
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type(), Scalar(0));


	/// SOBEL FILTER ////
	//Mat mx = Mat_<float>({ 3, 3 }, { -1.f, 0, 1.f, -2.f, 0, 2.f, -1.f, 0, 1.f }); //sobel filter mask, x
	//Mat my = Mat_<float>({ 3, 3 }, { -1.f, -2.f, -1.f, 0, 0, 0, 1.f, 2, 1.f  }); //sobel filter mask, y
	//Mat dx, dy;
	//filter2D(src, dx, -1, mx, Point(-1, -1), 0); // x partial derivative
	//filter2D(src, dy, -1, my, Point(-1, -1), 0); // y partial derivative
	//dx.convertTo(dx, CV_32FC1);
	//dy.convertTo(dy, CV_32FC1);
	// --- or --- // 
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;
	
	imshow("src", T_RESIZE(src));
	//imshow("dx", T_RESIZE(dx));
	//imshow("dy", T_RESIZE(dy));
	imshow("mag", T_RESIZE(mag));
	imshow("edge", T_RESIZE(edge));
	waitKey(0);
	return 0;
}
