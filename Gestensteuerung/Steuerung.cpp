#include <opencv2/opencv.hpp>
#include "Steuerung.h"

using namespace cv;
using namespace std;

//Konstruktor
Steuerung::Steuerung() 
	: xPosition(0.0)
	, xPositionChange(0.0)
	//, videoCapture(0) //Darf nicht im Konstruktor initialisiert werden, da Video sonst nicht angezeigt wird
	, frameNumber(0)
{}

//Destruktor (gibt Ressourcen wieder frei)
Steuerung::~Steuerung(){

}

void Steuerung::initialize(){
	videoCapture.open(0); //Default-Kamera öffnen
	frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

	namedWindow("Originalvideo");
}

float Steuerung::getXPosition(){
	return xPosition;
}

float Steuerung::getXPositionChange(){
	return xPositionChange;
}

void Steuerung::convertToBinary(cv::Mat videoFrame, cv::Mat& processedFrame){

}

Point Steuerung::centroidOfWhitePixels(const cv::Mat& image){
	return Point(0,0); //Nur als Dummy-Wert eingefügt, da der Compiler sonst meckert
}

void Steuerung::process(){
	while(true){
		Mat videoFrame; 
		if (videoCapture.read(videoFrame) == false){ 
			break; 
		} 
		frameNumber++; 
		cout << "Framenumber: " << frameNumber << endl;

		videoFrame.copyTo(previousFrame);  
		imshow("Originalvideo", videoFrame);

		waitKey(30);
	}
}