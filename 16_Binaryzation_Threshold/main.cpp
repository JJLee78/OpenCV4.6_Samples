#include "opencv2/opencv.hpp"
#include <iostream>
#include "JJLIB.h"

using namespace cv;
using namespace std;

void on_threshold(int pos, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	Mat dst1;
	//cout << pos << endl;
	threshold(src1, dst1, pos, 255, THRESH_BINARY);
	imshow("dst", T_RESIZE(dst1));


}
void on_adaptive(int pos, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	Mat dst1;
	int bsize = pos;
	if (bsize % 2 == 0)
		bsize--;
	if (bsize < 3)
		bsize = 3;

	adaptiveThreshold(src1, dst1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);
	imshow("dst", T_RESIZE(dst1));
	//imshow("adaptive", dst1);


}

int main()
{
	Mat src = imread("..\\Data\\big.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat(src.size(), src.type());

	imshow("src", T_RESIZE(src));

	namedWindow("dst");
	createTrackbar("Blocksize", "dst", 0, 255, on_adaptive, (void*)&src);
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src);
	setTrackbarPos("Blocksize", "dst", 11);
	setTrackbarPos("Threshold", "dst", 128);
	waitKey();
	return 0;
}