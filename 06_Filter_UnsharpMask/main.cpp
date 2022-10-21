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

void change_gaussian(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;
	int sigmasize = pos + 1;
	Mat Blur;
	GaussianBlur(img, Blur, Size(), (double)sigmasize); // sigma size must be odd number!!
	Mat g = img - Blur;
	float a = 1.f;
	Mat dst = img + (g * a);
	imshow("change_gaussian", dst);
}

void change_alpha(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;
	int sigmasize = 1;
	float a = (float)pos;
	Mat Blur;
	GaussianBlur(img, Blur, Size(), (double)sigmasize); // sigma size must be odd number!!
	Mat g = img - Blur;
	//float a = 1.f;
	Mat dst = img + (g * a);
	imshow("change_alpha", dst);
}

int main()
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	imshow("src", src);
	namedWindow("change_gaussian");
	createTrackbar("level", "change_gaussian", 0, 16, change_gaussian, (void*)&src); // change_gaussian : callback function to trackbar
	namedWindow("change_alpha");
	createTrackbar("level2", "change_alpha", 0, 16, change_alpha, (void*)&src); // more a, more sharpen. more sigma for what..?

	waitKey(0);
	return 0;
}