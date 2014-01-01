#include <opencv2\opencv.hpp>
#include <string>
#include <ctime>
#include "Steuerung.h"
#include "ViewController.h"
using namespace cv;
using namespace std;

//Steuerung steuerung;
clock_t lastFrame;
int dist;
const int maxDistance = 2000;
ViewController view;
bool gameOn = true;

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
		//steuerung.process(); //muss hier rein, da für jede Runde im loop die Steuerung angesprochen werden muss
		
		float xPos = 0;//steuerung.getXPosition();//Schon für die Breite des "Spielfelds" angepasste xPosition erfragen
		int delta = getDelta()*0.1;
		//Auch xPos an view übergeben
		view.draw(delta, xPos); //hier wird alles gezeichnet (inkl Biene)
		dist = dist + delta;
		int key = waitKey(30);
		//pause at anykey
		if (key != -1){
			break;
		} 
	}
}


int main(){
	init();
	while (gameOn){
		loop();
		if (dist >= maxDistance){
			// end game
			view.drawSolution();
			int k = waitKey(0);
			if (k == 27){
				//exit
				gameOn = false;
				break;
			} else if (k != -1){
				//restart game
				dist = 0;
				lastFrame = clock();
				view = ViewController();
			}
		} else {
			// game paused
			view.drawPause();
			int k = waitKey(0);
			if (k == 27){
				//exit
				break;
			}
			// go on
		}
	}
	return 0;
}