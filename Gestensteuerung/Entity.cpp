#include <opencv2/opencv.hpp>
#include "Entity.h"

using namespace cv;
using namespace std;

// Konstruktor
Entity::Entity(int posx, int posy, string name)
	: x(posx), 
	y(posy) 
	{
		image = imread("img/"+name+".png", CV_LOAD_IMAGE_UNCHANGED);
		createMask();
		image = imread("img/"+name+".png", CV_LOAD_IMAGE_COLOR);
	}

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
	x = enterX;
}

void Entity::insertInto(Mat &viewImage){
	Rect roi(Point(x, y), image.size()); //region of interest
	Mat destinationROI = viewImage(roi);
	image.copyTo(destinationROI, mask);
}