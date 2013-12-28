#include <opencv2/opencv.hpp>
#include "Bee.h"
#include "Obstacle.h"

using namespace std;
using namespace cv;

// Konstruktor
Bee::Bee(int posx, int posy, int maximumX, int maximumY, string name)
	:Entity(posx, posy, maximumX, maximumY, name),
	points(0),
	hurt(false),
	hurtTime(8)
	{
	hurtImage = imread("img/hurt-bee.png", CV_LOAD_IMAGE_COLOR);
	}

void Bee::addPoints(int p){
	points = points + p;
}

int Bee::getPoints() const{
	return points;
}

void Bee::collidesWith(Obstacle &ob){
	// the 20 assures that it does not hit everything it just touches
	if (ob.getCollable()){ // has it allready been hit just now?
		if (ob.getY()+ob.getHeight() > y+20){
			if (ob.getY() < y+image.rows-20){
				if (ob.getX()+ob.getWidth() > x+20){
					if (ob.getX() < x+image.cols-20){
						ob.setCollable(false);
						addPoints(ob.getWorth());
						if (ob.getWorth() < 0){
							hurt = true;
							hurtTime = 8;
						}
						cout << "points: " << points << endl;
					}
				}
			}
		}
	}
}

void Bee::insertInto(Mat &viewImage){
	Rect roi(Point(x, y), image.size());
	Mat destinationROI = viewImage(roi);
	if (hurt){
		hurtImage.copyTo(destinationROI, mask);
		hurtTime--;
		if (hurtTime <= 0){
			hurt = false;
		}
	} else {
		image.copyTo(destinationROI, mask);
	}
}