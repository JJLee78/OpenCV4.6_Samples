#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void setLabel(Mat& img, const vector<Point>& pts, const String& label)
{
	Rect rc = boundingRect(pts);
	rectangle(img, rc, Scalar(0, 0, 255), 1);
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

int main()
{
	Mat img = imread("..\\Data\\polygon.bmp", IMREAD_COLOR);
	Mat gray = imread("..\\Data\\polygon.bmp", IMREAD_GRAYSCALE);
	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	for (vector<Point>& pts : contours) 
	{
		if (contourArea(pts) < 400)
			continue;
		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);
		int vtc = (int)approx.size();

		if (vtc == 3)
			setLabel(img, pts, "TRI");
		else if (vtc == 4)
			setLabel(img, pts, "RECT");
		else if (vtc > 4)
		{
			double len = arcLength(pts, true);
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);
			if (ratio > 0.8)
				setLabel(img, pts, "CIR");
		}
	}

	imshow("img", img);
	waitKey();
	return 0;
}
