#include <opencv2/opencv.hpp>
#include "Bee.h"

using namespace cv;
using namespace std;

// Konstruktor
Bee::Bee():
	x(300),
	y(500)
{}

//Destruktor
Bee::~Bee(){}

void Bee::init(){
	image = imread("img/bee.png", CV_LOAD_IMAGE_UNCHANGED);
	createMask();
	image = imread("img/bee.png", CV_LOAD_IMAGE_COLOR);
}

void Bee::createMask(){
	mask.create(image.rows, image.cols, CV_8UC1);
	for (int x = 0; x < image.cols; x++){
		for (int y = 0; y < image.rows; y++){
			mask.at<unsigned char>(y, x) = image.at<Vec4b>(y, x)[3];
		}
	}
}

int Bee::getX(){
	return x;
}

int Bee::getY(){
	return y;
}

void Bee::setX(int enterX){
	x = enterX;
}

void Bee::insertInto(Mat &viewImage){
	Rect roi(Point(x, y), image.size()); //region of interest
	Mat destinationROI = viewImage(roi);
	image.copyTo(destinationROI, mask);
}