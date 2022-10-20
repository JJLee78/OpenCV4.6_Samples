#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

void histgoram_stretching();
void histgoram_equalization();

int main(void)
{
	Mat src = imread("..\\Data\\lenna.bmp", 1);
	imshow("lenna", src);
	waitKey(0);

	return 0;
}