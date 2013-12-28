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
		void drawSolution();
	private:
		cv::Mat bg;
		cv::Mat viewImage;
		void createFlowers();
		void createEnemies();
		void moveBG(int delta);
		void moveAndDrawFlowers(int delta);
		void checkCollision();
		Bee bee;
		std::vector<Obstacle> obstacles;
		std::vector<std::string> kindsOfFlower;
		std::string itos(int i);
};
#endif