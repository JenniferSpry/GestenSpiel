#include <opencv2\opencv.hpp>
#include <string>
#include <ctime>
#include "windows.h"
#include "Steuerung.h"
#include "Bee.h"
using namespace cv;
using namespace std;

Mat bg;
Mat viewImage;
//Steuerung steuerung;
Bee bee;
clock_t lastFrame;

double getDelta() {
	long currentTime = clock();
	double delta = (double) currentTime - (double) lastFrame;
	lastFrame = clock();
	return delta;
}

void init(){
	lastFrame = clock();
	//steuerung.initialize();
	bee.init();
	bg = imread("img/bg.png", 1);
	namedWindow( "Bienchen & Blümchen", 1 ); 	
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
}

void loop(){
	while(true){
		/*if (!steuerung.process()){
			break;
		}*/
		//collisionmanagement
		int delta = getDelta()*0.2;
		moveBG(delta);
		bg.copyTo(viewImage);
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