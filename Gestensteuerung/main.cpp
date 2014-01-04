#include <opencv2\opencv.hpp>
#include <string>
#include <ctime>
#include "Steuerung.h"
#include "ViewController.h"
using namespace cv;
using namespace std;

Steuerung steuerung;
clock_t lastFrame;
int dist = 0;
const int maxDistance = 2000;
ViewController view;
bool gameOn = true;
int key;

double getDelta() {
	long currentTime = clock();
	double delta = (double) currentTime - (double) lastFrame;
	lastFrame = clock();
	return delta;
}


void loop(){
	// Game Loop
	lastFrame = clock();
	while(dist < maxDistance){
		if (!steuerung.process()){ //game stops if there is a problem with the camera
			break;
		}
		float xPos = steuerung.getXPosition();//Schon für die Breite des "Spielfelds" angepasste xPosition erfragen
		int delta = getDelta()*0.1;
		//Auch xPos an view übergeben
		view.draw(delta, xPos); //hier wird alles gezeichnet (inkl Biene)
		dist = dist + delta;
		key = waitKey(30);
		//pause at anykey
		if (key != -1){
			break;
		} 
	}
}

void startLoop(){
	// Loop to just move the bee
	lastFrame = clock();
	while (true){
		if (!steuerung.process()){ //stops if there is a problem with the camera
			break;
			gameOn = false;
		}
		//steuerung.process();
		float xPos = steuerung.getXPosition();//Schon für die Breite des "Spielfelds" angepasste xPosition erfragen
		//Auch xPos an view übergeben
		view.drawStart(xPos);
		key = waitKey(30);
		if (key == 27){
			//exit
			gameOn = false;
			break;
		} else if (key != -1) {
			break;
		}
	}
}


int main(){

	// waiting for the webcam
	while (!steuerung.initialize()) {
		view.drawCamSearch();
		key = waitKey(0);
		if (key == 27){ // esc
			return 0;
		}
	}
	cout << "Webcam found!" << endl;

	// let the player see how it works
	startLoop();

	// start the game
	while (gameOn){
		loop();
		if (dist >= maxDistance){
			// end game
			view.drawSolution();
			key = waitKey(0);
			if (key == 27){
				return 0;
			} else if (key != -1){
				//restart game
				dist = 0;
				view = ViewController();
			}
		} else {
			// game paused
			view.drawPause();
			key = waitKey(0);
			if (key == 27){
				return 0;
			}
			// go on
		}
	}
	return 0;
}