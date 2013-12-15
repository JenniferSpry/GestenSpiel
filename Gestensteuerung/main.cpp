#include <opencv2\opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

Mat bg;

void init(){
	bg = imread("img/bg.png", 1);
	namedWindow( "Bienchen & Blümchen", 1 ); 	
}

void move(){
	Mat temp; 
	bg.copyTo(temp);
	Vec3b blue(0, 0, 255);
	bg.at<Vec3b>(50, 50) = blue;
	for (int x = 0; x < (bg.rows-1); x++){
		temp.row(x).copyTo(bg.row(x+1));
	}
	temp.row(bg.rows-1).copyTo(bg.row(0));
}

void loop(){
	while(true){
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
	return 0;
}