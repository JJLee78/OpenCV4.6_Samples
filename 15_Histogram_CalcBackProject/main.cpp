#include "opencv2/opencv.hpp"
#include <iostream>
#include "JJLIB.h"
using namespace cv;
using namespace std;

int main()
{
	Mat ref = imread("..\\Data\\ref.png", IMREAD_COLOR);
	Mat mask = imread("..\\Data\\mask.bmp", IMREAD_GRAYSCALE);
	Mat ref_ycrcb;
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128;
	int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };
	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges); //calculate histogram of area from ref.png(with mask image)
	
	

	Mat src, src_ycrcb;
	src = imread("..\\Data\\kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true); //calculate back project from calculated histogram 'hist'

	imshow("src", T_RESIZE(src));
	imshow("dst", T_RESIZE(backproj));
	waitKey(0);
	return 0;
}