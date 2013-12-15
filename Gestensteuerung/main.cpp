#include <opencv2\opencv.hpp>
#include <string>
#include "Steuerung.h"
using namespace cv;
using namespace std;

Mat bg;
Steuerung steuerung;

void init(){
	steuerung.initialize();
	bg = imread("img/bg.png", 1);
	namedWindow( "Bienchen & Blümchen", 1 ); 	
}

void move(){
	Mat temp; 
	bg.copyTo(temp);
	for (int x = 0; x < (bg.rows-1); x++){
		temp.row(x).copyTo(bg.row(x+1));
	}
	temp.row(bg.rows-1).copyTo(bg.row(0));
}

void loop(){
	while(true){
		if (!steuerung.process()){
			break;
		}
		move();
		imshow( "Bienchen & Blümchen", bg );
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
	//Steuerung.process();
	return 0;
}