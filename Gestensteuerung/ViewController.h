#ifndef VIEWCONTROLLER_H 
#define VIEWCONTROLLER_H
#include <opencv2/opencv.hpp>
#include <vector>
#include "Obstacle.h"
#include "Bee.h"
#include "Enemy.h"

class ViewController{
	public:
		ViewController();
		~ViewController();
		void draw(int delta, float xPosEntry);
		void drawSolution();
		void drawPause();
		void drawStart(float xPosEntry);
	private:
		cv::Mat bg;
		cv::Mat viewImage;
		void createFlowers();
		void createEnemies();
		void moveBG(int delta);
		void moveAndDrawObstacles(int delta);
		void checkCollision();
		Bee bee;
		std::vector<Obstacle> flowers;
		std::vector<Enemy> enemies;
		std::vector<std::string> kindsOfFlower;
		std::string itos(int i);
};
#endif