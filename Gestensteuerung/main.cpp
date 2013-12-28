#include <opencv2\opencv.hpp>
#include <string>
#include <ctime>
//#include "windows.h"
#include "Steuerung.h"
#include "ViewController.h"
using namespace cv;
using namespace std;

//Steuerung steuerung;
clock_t lastFrame;
int dist;
const int maxDistance = 4000;
ViewController view;

double getDelta() {
	long currentTime = clock();
	double delta = (double) currentTime - (double) lastFrame;
	lastFrame = clock();
	return delta;
}

void init(){
	lastFrame = clock();
	//steuerung.initialize();
	dist = 0;
}

void loop(){
	while(dist < maxDistance){
		int delta = getDelta()*0.1;
		view.draw(delta);
		dist = dist + delta;
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