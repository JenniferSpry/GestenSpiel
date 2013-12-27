#include <opencv2/opencv.hpp>
#include "Bee.h"

using namespace std;

// Konstruktor
Bee::Bee(int posx, int posy, int maximumX, int maximumY, string name)
	:Entity(posx, posy, maximumX, maximumY, name),
	points(0)
{}

void Bee::addPoint(){
	points++;
}