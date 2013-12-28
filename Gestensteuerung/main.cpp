#include <opencv2\opencv.hpp>
#include <string>
#include "Steuerung.h"
#include "Bee.h"
using namespace cv;
using namespace std;

Mat bg;
Mat viewImage;
Steuerung steuerung;
Bee bee;

void init(){
	steuerung.initialize();
	bee.init();
	bg = imread("img/bg.png", 1);
	namedWindow( "Bienchen & Blümchen", 1 ); 	
}

void moveBG(){
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
		moveBG();
		bg.copyTo(viewImage);
		imshow( "Bienchen & Blümchen", bee.insertInto(viewImage));
		// end
		
		int key = waitKey(30);
		/*
		if (key != -1){
			break;
		}
		*/
	}
}



int main(){
	init();
	loop();
	steuerung.process();
	return 0;
}