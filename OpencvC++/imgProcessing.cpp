#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

#define w 400

using namespace cv;
using namespace std;


void drawLine(Mat img, Point start, Point end);

void main()
{
	Mat black_image = Mat::zeros(w, w, CV_8UC3);
	cout << black 
	//string path = "Resources/shapes.png";
	//Mat img = imread(path);
	drawLine(black_image, Point(10,10), Point(w/2,w/2));
	imshow("image", black_image);
	waitKey(0);
}

void drawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	line(
		img,
		start,
		end,
		Scalar(255, 0, 0),
		thickness);
}