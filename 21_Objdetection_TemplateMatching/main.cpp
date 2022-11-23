#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("..\\Data\\circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("..\\Data\\crystal.bmp", IMREAD_COLOR);

	img = img + Scalar(50, 50, 50); // 실제 상황에서 이미지 밝기 차이가 난다는 것을 가정

	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3); // 실제 상황에서 노이즈가 추가되는 것을 가정

	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);
	
	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv : " << maxv << endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);
	waitKey(0);
	return 0;
}