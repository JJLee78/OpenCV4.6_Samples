#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, 0, noArray(), hist, dims, histSize, ranges);

	return hist;
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

int main(void)
{
	Mat src = imread("..\\Data\\lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());
	double Gmin, Gmax;
	
	minMaxLoc(src, &Gmin, &Gmax);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar srcVal = src.at<uchar>(i, j);
			dst.at<uchar>(i, j) = ((srcVal - Gmin) / (Gmax - Gmin))* 255;  // histgoram stretching

		}
	}
	imshow("src", src);
	imshow("dst", dst);
	imshow("srchist", getGrayHistImage(calcGrayHist(src)));
	imshow("dsthist", getGrayHistImage(calcGrayHist(dst)));

	waitKey(0);

	return 0;
}