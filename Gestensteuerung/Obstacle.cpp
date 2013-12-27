#include <opencv2/opencv.hpp>
#include "Obstacle.h"

using namespace std;

// Konstruktor
Obstacle::Obstacle(int posx, int posy, string name, int amount)
	:Entity(posx, posy, name),
	worth(amount)
{}

int Obstacle::getWorth() const{
	return worth;
}