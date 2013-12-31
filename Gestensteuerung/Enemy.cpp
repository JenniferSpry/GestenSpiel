#include <opencv2/opencv.hpp>
#include "Enemy.h"

using namespace std;
using namespace cv;

// Konstruktor
Enemy::Enemy(int posx, int posy, int maximumX, int maximumY, string name, int amount)
	:Obstacle(posx, posy, maximumX, maximumY, name, amount)
{}

void Enemy::addToY(int entryY){
	y = y + entryY;
	if (y > maxY){
		setCollable(true);
		// reposition
		x = (rand() % (int)(maxX - 50 + 1));
		y = 0 - (rand() % (int)(maxY + 400 + 1));
	}
	setX(abs(300*(sin((double)y) * 0.2)));
}

void Enemy::insertInto(Mat &viewImage){
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