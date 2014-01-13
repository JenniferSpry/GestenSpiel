#include <opencv2/opencv.hpp>
#include <string>
#include <math.h>
#include "ViewController.h"
#include "Obstacle.h"
#include "Bee.h"
#include "Enemy.h"

using namespace cv;
using namespace std;

ViewController::ViewController()
	:bee(180, 530, 400, 600, "bee"),
	flowers(25),
	enemies(3)
	{
	bg = imread("img/bg.png", 1);
	namedWindow( "Bienchen & Blümchen", 1 ); 
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
		flowers[i] = Obstacle(x, y, bg.cols, bg.rows, "flower_"+itos(type), (type+1)*5);
	}
	// create the rest above the game frame
	for (int i = 8; i < flowers.size(); i++){
		int x = (rand() % (int)(bg.cols - 50 + 1)); // 50 = flower width
		int y = (rand() % (int)(bg.rows + 400 + 1));
		int type = (rand() % (int)(2 + 1));
		flowers[i] = Obstacle(x, -y, bg.cols, bg.rows, "flower_"+itos(type), (type+1)*5);
	}
}

void ViewController::createEnemies(){
	// create enemies
	// insert them above the game frame
	for (int i = 0; i < enemies.size(); i++){
		int y = (rand() % (int)(bg.rows + 400 + 1));
		enemies[i] = Enemy(200, -y, bg.cols, bg.rows, "enemy", -20);
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

void ViewController::moveAndDrawObstacles(int delta){
	for (int i = 0; i < flowers.size(); i++){
		flowers[i].addToY(delta);
		flowers[i].insertInto(viewImage);
	}
	for (int i = 0; i < enemies.size(); i++){
		enemies[i].addToY(delta);
		enemies[i].insertInto(viewImage);
	}
}

void ViewController::checkCollision(){
	for (int i = 0; i < flowers.size(); i++){
		bee.collidesWith(flowers[i]);
	}
	for (int i = 0; i < enemies.size(); i++){
		bee.collidesWith(enemies[i]);
	}
}

void ViewController::draw(int delta, float xPosEntry){
	// draw view during game
	moveBG(delta);
	bg.copyTo(viewImage);
	moveAndDrawObstacles(delta);
	checkCollision();
	bee.setX(xPosEntry);
	bee.insertInto(viewImage);
	putText(viewImage, itos(bee.getPoints()), Point(10,20), CV_FONT_HERSHEY_SIMPLEX , 0.5, Scalar(255,255,255),2);
	imshow( "Bienchen & Blümchen", viewImage);
}

void ViewController::drawSolution(){
	// draw at the end of the game
	viewImage = viewImage * 0.5;
	if (bee.getPoints() > 0){
		// won
		Entity sol(0, 200, 400, 600, "won");
		sol.insertInto(viewImage);
	} else {
		// lost
		Entity sol(0, 200, 400, 600, "lost");
		sol.insertInto(viewImage);
	}
	setTextMiddle(360, itos(bee.getPoints()), 2);
	//this will be in the image
	setTextMiddle(540, "Tippe die Leertaste,", 0.6);
	setTextMiddle(560, "um noch einmal zu spielen.", 0.6);
	setTextMiddle(580, "Tippe Esc zum beenden.", 0.6);
	imshow( "Bienchen & Blümchen", viewImage);
}

void ViewController::drawPause(){
	// draw at the end of the game
	viewImage = viewImage * 0.5;
	//this will be in the image
	Entity pauseImage(0, 180, 400, 600, "pause");
	pauseImage.insertInto(viewImage);
	setTextMiddle(540, "Tippe die Leertaste,", 0.6);
	setTextMiddle(560, "um weiter zu spielen.", 0.6);
	setTextMiddle(580, "Tippe Esc zum beenden.", 0.6);
	imshow( "Bienchen & Blümchen", viewImage);
}

void ViewController::drawStart(float xPosEntry){
	// draw at the beginning of the game
	moveBG(0);
	bg.copyTo(viewImage);
	viewImage = viewImage * 0.5;
	bee.setX(xPosEntry);
	bee.insertInto(viewImage);
	//this will be in the image
	Entity explanation(0, 100, 400, 600, "explanation");
	explanation.insertInto(viewImage);
	setTextMiddle(470, "Tippe die Leertaste,", 0.6);
	setTextMiddle(490, "um das Spiel zu beginnen.", 0.6);
	setTextMiddle(510, "Tippe Esc zum beenden.", 0.6);
	imshow( "Bienchen & Blümchen", viewImage);
}

void ViewController::drawCamSearch(){
	// draw at the beginning of the game
	moveBG(0);
	bg.copyTo(viewImage);
	viewImage = viewImage * 0.5;
	//this will be in the image
	setTextMiddle(200, "Es konnte keine Webcam", 0.9);	
	setTextMiddle(230, "gefunden werden.", 0.9);
	setTextMiddle(320, "Tippe die Leertaste, ", 0.6);
	setTextMiddle(340, "um sie noch einmal zu suchen.", 0.6);
	setTextMiddle(580, "Tippe Esc zum beenden.", 0.6);
	imshow( "Bienchen & Blümchen", viewImage);
}

string ViewController::itos(int i){
	// integer to string helpermethod
	stringstream ss;
	ss << i;
	return ss.str();
}

void ViewController::setTextMiddle(int y, string s, double fontSize){
	//Helpermathod to insert Text in the screen middle
	Size textsize = getTextSize(s, CV_FONT_HERSHEY_SIMPLEX, fontSize, 1, 0);
	int xpos = bg.cols / 2 - textsize.width / 2;
	putText(viewImage, s, Point(xpos,y), CV_FONT_HERSHEY_SIMPLEX , fontSize, Scalar(255,255,255),1);
}