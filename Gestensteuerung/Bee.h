#ifndef BEE_H
#define BEE_H
#include <string>
#include "Obstacle.h"
#include "Entity.h"

class Bee : public Entity{
	public:
		Bee(int posx, int posy, int maximumX, int maximunY, std::string name);
		void addPoints(int p);
		int getPoints() const;
		void collidesWith(Obstacle &ob);
		void insertInto(cv::Mat &viewImage);
	private:
		int points;
		cv::Mat hurtImage;
		bool hurt;
		int hurtTime;
};
#endif