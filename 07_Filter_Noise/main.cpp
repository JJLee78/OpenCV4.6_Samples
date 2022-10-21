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

void change_gaussian_bilateral(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;
	int sigmasize = pos + 1;
	Mat Blur;
	Mat dst;
	bilateralFilter(img, dst, -1, sigmasize, 5); // -1 : pixel distance between neighberhood pixel -1 means calculated by sigmaspace
	imshow("change_gaussian_bilateral", T_RESIZE(dst));
}


int main()
{
	Mat src = imread("..\\Data\\big.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());
	Mat noise = Mat(src.size(), src.type());

	int stddev = 10;
	randn(noise, 0, stddev);
	add(src, noise, dst, Mat(), CV_8U);

	//Mat dst1;
	//GaussianBlur(src, dst1, Size(), 5);
	Mat dst2;


	imshow("src(noisy)", T_RESIZE(dst));

	namedWindow("change_gaussian_bilateral");
	createTrackbar("level", "change_gaussian_bilateral", 0, 32, change_gaussian_bilateral, (void*)&dst); // change_gaussian : callback function to trackbar

	waitKey(0);
	return 0;
}