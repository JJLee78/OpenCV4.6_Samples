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
	Mat src = imread("..\\Data\\building.jpg", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type(), Scalar(0));

	Mat edge;
	Canny(src, edge, 50, 150); // 0 : lower weak edge threshold, detect more edges
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	vector<Vec4i> linesP;
	Mat dst2;
	HoughLinesP(edge, linesP, 1, CV_PI / 180, 160, 50, 5);
	cvtColor(edge, dst2, COLOR_GRAY2BGR);

	for (int i = 0; i < lines.size(); i++)
	{
		float r = lines[i][0];
		float t = lines[i][1];
		double cos_t = cos(t);
		double sin_t = sin(t);
		double x0 = r * cos_t;
		double y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
		cout << "pt1 / pt2 : " << pt1 << " " << pt2 << endl;
	

	}
	for (Vec4i l : linesP)
	{
		line(dst2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 2, LINE_AA);
		circle(dst2, Point(l[0], l[1]), 2, Scalar(0, 255, 255), 3);
		circle(dst2, Point(l[2], l[3]), 2, Scalar(0, 0, 255), 3);
	}


	imshow("src", T_RESIZE(src));
	imshow("edge", T_RESIZE(edge));

	imshow("HoughLines", T_RESIZE(dst));
	imshow("HoughLinesP", T_RESIZE(dst2));
	waitKey(0);


	return 0;
}