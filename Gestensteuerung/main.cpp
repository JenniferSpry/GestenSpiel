#include <opencv2\opencv.hpp>
#include <string>
#include <ctime>
#include <vector>
#include "windows.h"
#include "Steuerung.h"
#include "Bee.h"
#include "Obstacle.h"
using namespace cv;
using namespace std;

Mat bg;
Mat viewImage;
//Steuerung steuerung;
clock_t lastFrame;
int dist;
const int maxDistance = 2000;
Bee bee(180, 530, 400, 600, "bee");
Obstacle flower(30, -70, 400, 600, "flower", 5);
//vector<Obstacle> obstacles(100);
//int obstacleAmount = 5;

double getDelta() {
	long currentTime = clock();
	double delta = (double) currentTime - (double) lastFrame;
	lastFrame = clock();
	return delta;
}

//void createFlowers(int amount){
//	//for (int i = 0; i < amount; i++){
//		int x = (rand() % (int)(bg.cols - 50 + 1)); // 50 = flower width
//		//obstacles[0] = Obstacle(x, -50, bg.cols, (maxDistance-bg.rows), "flower", 5);
//	//}
//}

void init(){
	lastFrame = clock();
	//steuerung.initialize();
	bg = imread("img/bg.png", 1);
	//createFlowers(20);
	namedWindow( "Bienchen & Blümchen", 1 ); 
	dist = 0;
}

void moveBG(int delta){
	Mat temp; 
	bg.copyTo(temp);
	for (int x = 0; x < (bg.rows-delta); x++){
		temp.row(x).copyTo(bg.row(x+delta));
	}
	for (int j = 0; j < delta; j++){
		temp.row(bg.rows-delta+j).copyTo(bg.row(j));
	}
	dist = dist + delta;
}

void moveAndDrawFlowers(){
	//for (int i = 0; i < 20; i++){
		flower.insertInto(viewImage);
	//}
}

void loop(){
	while(dist < maxDistance){
		/*if (!steuerung.process()){
			break;
		}*/
		//collisionmanagement
		int delta = getDelta()*0.1;
		//cout << "delta: " << delta <<endl;
		moveBG(delta);
		bg.copyTo(viewImage);
		flower.addToY(delta);
		moveAndDrawFlowers();
		bee.insertInto(viewImage);
		imshow( "Bienchen & Blümchen", viewImage);
		// end
		int key = waitKey(30);
		if (key != -1){
			break;
		}
	}
}


int main(){
	init();
	loop();
	//steuerung.process();
	return 0;
}