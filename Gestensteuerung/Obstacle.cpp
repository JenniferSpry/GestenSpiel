#include <opencv2/opencv.hpp>
#include "Obstacle.h"

using namespace std;

// Konstruktor
Obstacle::Obstacle(int posx, int posy, int maximumX, int maximumY, string name, int amount)
	:Entity(posx, posy, maximumX, maximumY, name),
	worth(amount)
{}

Obstacle::Obstacle(){}

int Obstacle::getWorth() const{
	return worth;
}