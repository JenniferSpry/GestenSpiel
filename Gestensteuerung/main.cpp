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
vector<Obstacle> obstacles(16);

double getDelta() {
	long currentTime = clock();
	double delta = (double) currentTime - (double) lastFrame;
	lastFrame = clock();
	return delta;
}

void createFlowers(){
	for (int i = 0; i < obstacles.size(); i++){
		int x = (rand() % (int)(bg.cols - 50 + 1)); // 50 = flower width
		int y = (rand() % (int)(bg.rows + 400 + 1));
		//min + (rand() % (int)(max - min + 1))
		obstacles[i] = Obstacle(x, -y, bg.cols, bg.rows, "flower", 5);
	}
}

void init(){
	lastFrame = clock();
	//steuerung.initialize();
	bg = imread("img/bg.png", 1);
	createFlowers();
	namedWindow( "Bienchen & Bl�mchen", 1 ); 
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

void moveAndDrawFlowers(int delta){
	for (int i = 0; i < obstacles.size(); i++){
		obstacles[i].addToY(delta);
		obstacles[i].insertInto(viewImage);
	}
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
		moveAndDrawFlowers(delta);
		bee.insertInto(viewImage);
		imshow( "Bienchen & Bl�mchen", viewImage);
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