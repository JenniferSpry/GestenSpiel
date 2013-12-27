#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <string>

#include "Entity.h"

class Obstacle : public Entity{
	public:
		Obstacle(int posx, int posy, int maximumX, int maximumY, std::string name, int amount);
		int getWorth() const;
	private:
		int worth;
};
#endif