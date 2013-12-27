#include <opencv2/opencv.hpp>
#include "Bee.h"
#include "Obstacle.h"

using namespace std;

// Konstruktor
Bee::Bee(int posx, int posy, int maximumX, int maximumY, string name)
	:Entity(posx, posy, maximumX, maximumY, name),
	points(0)
{}

void Bee::addPoints(int p){
	points = points + p;
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
						cout << "points: " << points << endl;
					}
				}
			}
		}
	}
}