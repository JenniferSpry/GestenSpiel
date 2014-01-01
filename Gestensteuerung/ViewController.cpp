#include <opencv2/opencv.hpp>
#include <math.h>
#include "ViewController.h"
#include "Obstacle.h"
#include "Bee.h"
#include "Enemy.h"

using namespace cv;
using namespace std;

ViewController::ViewController()
	:bee(180, 530, 400, 600, "bee"),
	obstacles(30),
	kindsOfFlower(3)
	{
	bg = imread("img/bg.png", 1);
	namedWindow( "Bienchen & Bl�mchen", 1 ); 
	kindsOfFlower[0] = "flower_0";
	kindsOfFlower[1] = "flower_1";
	kindsOfFlower[2] = "flower_2";
	createFlowers();
	createEnemies();
	}

ViewController::~ViewController(){};


void ViewController::createFlowers(){
	// create some flowers inside the game frame
	for (int i = 0; i < 8; i++){
		int x = (rand() % (int)(bg.cols - 50 + 1)); // 50 = flower width
		int y = (rand() % (int)(bg.rows + 1));
		int type = (rand() % (int)(2 + 1));
		//min + (rand() % (int)(max - min + 1))
		obstacles[i] = Obstacle(x, y, bg.cols, bg.rows, kindsOfFlower[type], 5);
	}
	// create the rest above the game frame
	for (int i = 8; i < obstacles.size(); i++){
		int x = (rand() % (int)(bg.cols - 50 + 1)); // 50 = flower width
		int y = (rand() % (int)(bg.rows + 400 + 1));
		int type = (rand() % (int)(2 + 1));
		obstacles[i] = Obstacle(x, -y, bg.cols, bg.rows, kindsOfFlower[type], 5);
	}
}

void ViewController::createEnemies(){
	// add enemies to the flowers
	// insert them above the game frame
	int amountOfFlowers = obstacles.size();
	obstacles.resize(amountOfFlowers+1);
	for (int i = amountOfFlowers; i < obstacles.size(); i++){
		int y = (rand() % (int)(bg.rows + 400 + 1));
		obstacles[i] = Enemy(200, -y, bg.cols, bg.rows, "enemy", -20);
	}
}


void ViewController::moveBG(int delta){
	// move background
	Mat temp; 
	bg.copyTo(temp);
	for (int x = 0; x < (bg.rows-delta); x++){
		temp.row(x).copyTo(bg.row(x+delta));
	}
	for (int j = 0; j < delta; j++){
		temp.row(bg.rows-delta+j).copyTo(bg.row(j));
	}
}

void ViewController::moveAndDrawFlowers(int delta){
	for (int i = 0; i < obstacles.size(); i++){
		obstacles[i].addToY(delta);
		obstacles[i].insertInto(viewImage);
	}
}

void ViewController::checkCollision(){
	for (int i = 0; i < obstacles.size(); i++){
		bee.collidesWith(obstacles[i]);
	}
}

void ViewController::draw(int delta, float xPosEntry){
	// draw view during game
	moveBG(delta);
	bg.copyTo(viewImage);
	moveAndDrawFlowers(delta);
	checkCollision();
	bee.setX(xPosEntry);
	bee.insertInto(viewImage);
	putText(viewImage, itos(bee.getPoints()), Point(10,viewImage.rows-10), CV_FONT_HERSHEY_SIMPLEX , 0.5, Scalar(255,255,255),2);
	imshow( "Bienchen & Bl�mchen", viewImage);
}

void ViewController::drawSolution(){
	// draw at the end of the game
	viewImage = viewImage * 0.5;
	if (bee.getPoints() > 0){
		// won
		Entity sol(80, 200, 400, 600, "won");
		sol.insertInto(viewImage);
	} else {
		// lost
		Entity sol(80, 200, 400, 600, "lost");
		sol.insertInto(viewImage);
	}
	putText(viewImage, itos(bee.getPoints()), Point(160,320), CV_FONT_HERSHEY_SIMPLEX , 1, Scalar(255,255,255),2);
	//this will be in the image
	putText(viewImage, "Press the spacebar", Point(160,350), CV_FONT_HERSHEY_SIMPLEX , 0.6, Scalar(255,255,255),1);
	putText(viewImage, "to play again", Point(160,370), CV_FONT_HERSHEY_SIMPLEX , 0.6, Scalar(255,255,255),1);
	imshow( "Bienchen & Bl�mchen", viewImage);
}

void ViewController::drawPause(){
	// draw at the end of the game
	viewImage = viewImage * 0.5;
	//this will be in the image
	putText(viewImage, "Press the spacebar to continue", Point(100,350), CV_FONT_HERSHEY_SIMPLEX , 0.6, Scalar(255,255,255),1);
	putText(viewImage, "Press Esc to leave", Point(100,370), CV_FONT_HERSHEY_SIMPLEX , 0.6, Scalar(255,255,255),1);
	imshow( "Bienchen & Bl�mchen", viewImage);
}

string ViewController::itos(int i){
	// integer to string helpermethod
	stringstream ss;
	ss << i;
	return ss.str();
}