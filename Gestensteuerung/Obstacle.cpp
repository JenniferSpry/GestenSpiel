#include <opencv2/opencv.hpp>
#include "Obstacle.h"

using namespace std;

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