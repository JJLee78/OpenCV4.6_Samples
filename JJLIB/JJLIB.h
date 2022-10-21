#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#pragma once

#ifdef CREATEDLL_EXPORTS
#define JJLIB_API __declspec(dllexport)
#else
#define JJLIB_API __declspec(dllimport)
#endif

int64 t0;
int64 t1;
#define TBEGIN t0 = cv::getTickCount();
#define TEND t1 = cv::getTickCount();
#define TRES cout << "Elapsed time : " << (t1 / t0) * 1000 / getTickFrequency() << endl;

extern "C" JJLIB_API void testfunc();
extern "C" JJLIB_API Mat T_RESIZE(Mat src);
//extern "C" JJLIB_API double Sub(double a, double b);
//extern "C" JJLIB_API double Mul(double a, double b);
//extern "C" JJLIB_API double Div(double a, double b);

