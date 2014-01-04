#include <opencv2/opencv.hpp>
#include <vector>
#include "Steuerung.h"

using namespace cv;
using namespace std;

//Konstruktor
Steuerung::Steuerung() 
	: xPosition(180.0)
	, xPositionMax(400.0)
	, xPositionPrev(0.0)
	, xPositionChange(0.0)
	//, videoCapture(0) //Darf nicht im Konstruktor initialisiert werden, da Video sonst nicht angezeigt wird
	, frameNumber(0)
	, bluePenColour(105,0,0)
{}

//Destruktor (gibt Ressourcen wieder frei)
Steuerung::~Steuerung(){

}

bool Steuerung::initialize(){
	videoCapture.open(0); //Default-Kamera öffnen

	if (videoCapture.isOpened()){
	
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

		//processedFrame = Mat(frameWidth, frameHeight, CV_8UC3);

		//namedWindow("Blue Testframe");
		namedWindow("Originalvideo");
		return true;
	} else {
		return false;
	}
}

float Steuerung::getXPosition(){
	//Breite Spielfeld: 400px, Breite Videocapture: 640 px, Verhältnis:  1 : 1,6
	xPosition /= 1.6;
	if(xPosition <= 0){ //Minimale xPosition der Biene
		xPosition = 0;
	}else if(xPosition >= 350){ //Maximale xPosition der Biene (Breite Spielfeld - Breite Biene = 350)
		xPosition = 350;
	}
	return xPosition;
}

//Eventuell unnötig
float Steuerung::getXPositionChange(){
	//XpositionChange ergibt sich durch XPos - XPosPrev.
	//Dieser Wert ist positiv bei einer Verschiebung des Controllers nach rechts (d.h. Xpos >= XPosPrev)
	//und negativ bei einer Verschiebung nach links (XPos < XPosPrev).
	xPositionChange = xPosition - xPositionPrev;
	return xPositionChange;
}

void Steuerung::convertToBinary(cv::Mat videoFrame, cv::Mat& processedFrame){

}

void Steuerung::convertToHSV(cv::Mat videoFrame, cv::Mat& processedFrame){

}

Point Steuerung::centroidOfWhitePixels(const cv::Mat& image){
	int sumx = 0;
    int sumy = 0;
	int count = 0;
    for(int x = 0; x < image.cols; x++){
        for (int y = 0; y < image.rows; y++){
			if (image.at<uchar>(y,x) == 255){
				sumx += x;
				sumy += y;
				count++;
			}
		}
	}
    if (count > 0){
		return Point(sumx/count, sumy/count);
    }
    else {
		return Point(-1,-1);
    }
}

void Steuerung::eliminateFlawedAreas(cv::Mat videoFrameBin){
		//Jetzt alle weißen Flächen bestimmen und in einem Vector speichern
		//Diesen Vektor dann nach Größe sortieren
		//Alle Areas bis auf die größte schwarz einfärben
		Mat copyOfVideoFrameBin(frameWidth, frameHeight, CV_8UC1);
		vector<vector<Point>> contours;
		
		videoFrameBin.copyTo(copyOfVideoFrameBin);
		findContours(copyOfVideoFrameBin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		
		vector<int> areaSizes;
		int maxArea = 0;
		for(int i = 0; i < contours.size(); i++){
			vector<Point> contour = contours[i];
			double area = contourArea(contour);
			if(area > maxArea){
				maxArea = area;
			}
			areaSizes.push_back(area);
		}

		//Jetzt in areaSizes alle areas < maxArea schwarz färben
		if(areaSizes.size() >= 2){
			for(int j = 0; j < areaSizes.size(); j++){
				if(areaSizes[j] < maxArea){
					//drawContours(copyOfVideoFrameBin, contours, j, Scalar(0,0,0), CV_FILLED);
					drawContours(videoFrameBin, contours, j, Scalar(0,0,0), CV_FILLED);
				}
			}
		}

		imshow("BinaerCopy", copyOfVideoFrameBin);
}


boolean Steuerung::process(){ 
	//Waren mal vor der Funktion
		Mat videoFrame;
		//Mat blueFrame; 
		Mat videoFrameHSV;
		Mat videoFrameBin; //Binärmaske

		if (videoCapture.read(videoFrame) == false){ 
			return false;
		} 


		//videoFrameHSV = Mat(frameWidth, frameHeight, CV_8UC3); //HSV Bild
		videoFrameBin = Mat(frameWidth, frameHeight, CV_8UC1);  //Binärmaske
		//Mat copyOfVideoFrameBin(frameWidth, frameHeight, CV_8UC1); //Braucht man, da findContours das Bild zerstört
		//blueFrame = bluePenColour;

		flip(videoFrame,videoFrame,1); //Spiegelt den Frame an der X-Achse (letzter Parameter = 1 bedeutet X-Achsenspiegelung)

		Scalar white(255,255,255);
		//Problem: Some facial areas sometimes get detected as being white, especially when moving the controller outside the trackable area
		inRange(videoFrame, white, white, videoFrameBin); //Working with a few flaws for a cell-phone light

		//Jetzt alle weißen Flächen bestimmen und in einem Vector speichern
		//Diesen Vektor dann nach Größe sortieren
		//Alle Areas bis auf die größte schwarz einfärben
		
		eliminateFlawedAreas(videoFrameBin); //tut das selbe wie der im folgenden auskommentierte code, wird noch verändert

		/*
		vector<vector<Point>> contours;
		
		videoFrameBin.copyTo(copyOfVideoFrameBin);
		findContours(copyOfVideoFrameBin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		
		vector<int> areaSizes;
		int maxArea = 0;
		for(int i = 0; i < contours.size(); i++){
			vector<Point> contour = contours[i];
			double area = contourArea(contour);
			if(area > maxArea){
				maxArea = area;
			}
			areaSizes.push_back(area);
		}

		//Jetzt in areaSizes alle areas < maxArea schwarz färben
		if(areaSizes.size() >= 2){
			for(int j = 0; j < areaSizes.size(); j++){
				if(areaSizes[j] < maxArea){
					//drawContours(copyOfVideoFrameBin, contours, j, Scalar(0,0,0), CV_FILLED);
					drawContours(videoFrameBin, contours, j, Scalar(0,0,0), CV_FILLED);
				}
			}
		}
		*/


		//Jetzt Opening
		Mat binaryMaskOpened(frameWidth, frameHeight, CV_8UC1);
		erode(videoFrameBin, binaryMaskOpened, MORPH_RECT);
		dilate(binaryMaskOpened, videoFrameBin, MORPH_RECT);

		//Zentralen Punkt finden:
		Point centroid = centroidOfWhitePixels(videoFrameBin);
		//XPositionPrev auf aktuelle XPos setzen
		xPositionPrev = xPosition;
		//aktuelle xPosition auf x-Pos des centroids setzen
		xPosition = centroid.x;

		//Dient nur zur Überprüfung der Funktionen:

		//grüne Linie vertikal auf Maskenkopie zeichnen (mit berechnetem Schwerpunkt als Mittlepunkt)
		Point startPunktVert(centroid.x, centroid.y-10);
		Point endPunktVert(centroid.x, centroid.y+10);
		line(videoFrame, startPunktVert, endPunktVert, Scalar(0,255,0), 2);

		//grüne Linie horizontal auf Maskenkopie zeichnen
		Point startPunktHor(centroid.x-10, centroid.y);
		Point endPunktHor(centroid.x+10, centroid.y);
		line(videoFrame, startPunktHor, endPunktHor, Scalar(0,255,0), 2);



		imshow("Originalvideo", videoFrame);
		//imshow("HSV", videoFrameHSV);
		imshow("Binaer", videoFrameBin);
		//imshow("BinaerCopy", copyOfVideoFrameBin);

		return true;
}