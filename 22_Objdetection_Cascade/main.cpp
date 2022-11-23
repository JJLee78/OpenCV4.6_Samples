#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("..\\Data\\kids.png", IMREAD_COLOR);
	CascadeClassifier classifier("..\\classifiers\\haarcascade_frontalface_default.xml");
	if (classifier.empty())
	{
		cerr << "XML LOAD FAIL" << endl;
		return 0;
	}

	vector<Rect> faces;
	classifier.detectMultiScale(src, faces);
	for (Rect rc : faces)
		rectangle(src, rc, Scalar(255, 0, 255), 2);

	imshow("src", src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}