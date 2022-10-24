#include "opencv2/opencv.hpp"
#include <iostream>
#include "JJLIB.h"
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\pepper.bmp", IMREAD_COLOR);

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes); // Pick luminence from src_ycrcb
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // ..and equalize histogram of luminence
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", T_RESIZE(src));
	imshow("dst", T_RESIZE(dst));
	waitKey(0);
	return 0;
}