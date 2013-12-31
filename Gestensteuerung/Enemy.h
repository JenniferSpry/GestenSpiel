#ifndef ENEMY_H
#define ENEMY_H
#include <string>

#include "Obstacle.h"

class Enemy : public Obstacle{
	public:
		Enemy(int posx, int posy, int maximumX, int maximumY, std::string name, int amount);
		void addToY(int entryY);
		void insertInto(cv::Mat &viewImage);
};
#endif