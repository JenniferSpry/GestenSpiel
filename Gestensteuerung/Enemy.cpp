#include <opencv2/opencv.hpp>
#include "Enemy.h"

using namespace std;
using namespace cv;

/*
	represents wasps
	has its own class because they move in a sine wave
	and do not vanish if hit
*/

// Konstruktor
Enemy::Enemy(int posx, int posy, int maximumX, int maximumY, string name, int amount)
	:Obstacle(posx, posy, maximumX, maximumY, name, amount)
{}

Enemy::Enemy(){}

void Enemy::addToY(int entryY){
	y = y + entryY + 1;
	if (y > maxY){
		setCollable(true);
		// reposition
		x = (rand() % (int)(maxX - 50 + 1));
		y = 0 - (rand() % (int)(maxY + 400 + 1));
	}
	setX(170 + (170 *( sin((double)y * 0.01))));
}

void Enemy::insertInto(Mat &viewImage){
	// allways insert, even if hit
	complexInsert(viewImage);
}