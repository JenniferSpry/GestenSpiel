#include <opencv2/opencv.hpp>
#include "Entity.h"

using namespace cv;
using namespace std;

// Konstruktor
Entity::Entity(int posx, int posy, int maximumX, int maximumY, string name)
	: x(posx), 
	y(posy),
	maxX(maximumX),
	maxY(maximumY)
	{
		image = imread("img/"+name+".png", CV_LOAD_IMAGE_UNCHANGED);
		createMask();
		image = imread("img/"+name+".png", CV_LOAD_IMAGE_COLOR);
	}

Entity::Entity(){}

//Destruktor
Entity::~Entity(){}

void Entity::createMask(){
	mask.create(image.rows, image.cols, CV_8UC1);
	for (int x = 0; x < image.cols; x++){
		for (int y = 0; y < image.rows; y++){
			mask.at<unsigned char>(y, x) = image.at<Vec4b>(y, x)[3];
		}
	}
}

int Entity::getX() const{
	return x;
}

int Entity::getY() const{
	return y;
}

void Entity::setX(int enterX){
	if (enterX >= maxX + image.cols){
		x = maxX - image.cols;
	} else {
		x = enterX;
	}
}

void Entity::insertInto(Mat &viewImage){
	Rect roi(Point(x, y), image.size()); //region of interest
	Mat destinationROI = viewImage(roi);
	image.copyTo(destinationROI, mask);
}