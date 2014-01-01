#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <string>

#include "Entity.h"

class Obstacle : public Entity{
	public:
		Obstacle(int posx, int posy, int maximumX, int maximumY, std::string name, int amount);
		Obstacle();
		int getWorth() const;
		void setCollable(bool b);
		bool getCollable() const;
		void addToY(int entryY);
		int getHeight();
		int getWidth();
		void insertInto(cv::Mat &viewImage);
		void complexInsert(cv::Mat &viewImage);
	private:
		int worth;
		bool collable; //so it will only register as hit once
};
#endif