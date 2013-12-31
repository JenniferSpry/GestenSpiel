#include <opencv2/opencv.hpp>
#include "Obstacle.h"

using namespace std;
using namespace cv;

// Konstruktor
Obstacle::Obstacle(int posx, int posy, int maximumX, int maximumY, string name, int amount)
	:Entity(posx, posy, maximumX, maximumY, name),
	worth(amount),
	collable(true)
{}

Obstacle::Obstacle(){}

int Obstacle::getWorth() const{
	return worth;
}

void Obstacle::setCollable(bool b){
	collable = b;
}

bool Obstacle::getCollable() const{
	return collable;
}

void Obstacle::addToY(int entryY){
	y = y + entryY;
	if (y > maxY){
		setCollable(true);
		// reposition
		x = (rand() % (int)(maxX - 50 + 1));
		y = 0 - (rand() % (int)(maxY + 400 + 1));
	}
}

int Obstacle::getHeight(){
	return image.rows;
}

int Obstacle::getWidth(){
	return image.cols;
}

void Obstacle::insertInto(Mat &viewImage){
	if (collable){
		if ((y >= 0) && (y < maxY)) {
			if ((y + image.rows) > maxY){
				// image at bottom
				//crop image
				Rect cropRoi(0, 0, image.cols, maxY-y);
				Mat croppedImage = image(cropRoi);
				//crop image
				Rect maskRoi(0, 0, image.cols, maxY-y);
				Mat croppedMask = mask(cropRoi);
				//insert
				Rect roi(Point(x, y), croppedImage.size());
				Mat destinationROI = viewImage(roi);
				croppedImage.copyTo(destinationROI, croppedMask);
			} else {
				Rect roi(Point(x, y), image.size()); //region of interest
				Mat destinationROI = viewImage(roi);
				image.copyTo(destinationROI, mask);
			}
		} else if (((y+image.rows) >= 0) && (y < maxY)) {
			//crop image
			Rect cropRoi(0, -y, image.cols, image.rows+y);
			Mat croppedImage = image(cropRoi);
			//crop image
			Rect maskRoi(0, -y, image.cols, image.rows+y);
			Mat croppedMask = mask(cropRoi);
			//insert
			Rect roi(Point(x, 0), croppedImage.size());
			Mat destinationROI = viewImage(roi);
			croppedImage.copyTo(destinationROI, croppedMask);
		}
	}
}