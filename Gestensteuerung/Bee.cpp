#include <opencv2/opencv.hpp>
#include "Bee.h"

using namespace std;

// Konstruktor
Bee::Bee(int posx, int posy, string name)
	:Entity(posx, posy, name),
	points(0)
{}

void Bee::addPoint(){
	points++;
}