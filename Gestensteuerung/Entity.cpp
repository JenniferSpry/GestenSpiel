#include <opencv2/opencv.hpp>
#include "Entity.h"

using namespace cv;
using namespace std;

/*
	Base class for all Objects in the Game
	Does only get used in this simple form to insert the min/lost picture
*/

// Konstruktor
Entity::Entity(int posx, int posy, int maximumX, int maximumY, string name)
	: x(posx), 
	y(posy),
	maxX(maximumX),
	maxY(maximumY)
	{
		image = imread("img/"+name+".png", CV_LOAD_IMAGE_UNCHANGED);
		createMask();
		//load image again without transparancy, so copyTo with the background will work
		image = imread("img/"+name+".png", CV_LOAD_IMAGE_COLOR);
	}

//c++ needs a standard constructor for vectors
Entity::Entity(){}

//Destruktor
Entity::~Entity(){}

void Entity::createMask(){
	//reads the aplha channel and stores it in a seperate image to use as mask
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
	} else if(abs(enterX - x) <= 200){
		x = enterX;
		//cout << enterX << endl;
	} 
}

void Entity::insertInto(Mat &viewImage){
	// insert entities image into the view-image
	// only works if image in inside the game frame
	Rect roi(Point(x, y), image.size()); //region of interest
	Mat destinationROI = viewImage(roi);
	image.copyTo(destinationROI, mask);
}