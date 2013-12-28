#ifndef VIEWCONTROLLER_H 
#define VIEWCONTROLLER_H
#include <opencv2/opencv.hpp>
#include <vector>
#include "Obstacle.h"
#include "Bee.h"

class ViewController{
	public:
		ViewController();
		~ViewController();
		void draw(int delta);
	private:
		cv::Mat bg;
		cv::Mat viewImage;
		void createFlowers();
		void moveBG(int delta);
		void moveAndDrawFlowers(int delta);
		void checkCollision();
		Bee bee;
		std::vector<Obstacle> obstacles;
		std::vector<std::string> kindsOfFlower;
};
#endif