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

	Mat dst1, dst2;
	Canny(src, dst1, 0, 50); // 0 : lower weak edge threshold, detect more edges
	Canny(src, dst2, 0, 255);

	imshow("src", T_RESIZE(src));
	imshow("dst1", T_RESIZE(dst1));
	imshow("dst2", T_RESIZE(dst2));
	waitKey(0);
	return 0;
}