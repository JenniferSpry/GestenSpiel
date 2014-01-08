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
{}

//Destruktor (gibt Ressourcen wieder frei)
Steuerung::~Steuerung(){

}

bool Steuerung::initialize(){
	videoCapture.open(0); //Default-Kamera öffnen

	if (videoCapture.isOpened()){
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

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
	}else if(xPosition >= 350 ){ //Maximale xPosition der Biene (Breite Spielfeld - Breite Biene = 350)
		xPosition = 350;
	}
	return xPosition;
}

//Eventuell unnötig
float Steuerung::getXPositionChange(){
	//XpositionChange ergibt sich durch XPos - XPosPrev.
	xPositionChange = xPosition - xPositionPrev;
	return xPositionChange;
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
		//Alle weißen Flächen im Binärbild bestimmen und in einem Vector speichern
		//Alle Areas bis auf die größte (maxArea) schwarz einfärben
		
		//Es muss eine Kopie der Binärmaske erstellt werden, da findContours() das untersuchte Bild zerstört
		Mat copyOfVideoFrameBin(frameWidth, frameHeight, CV_8UC1);
		//Im Vektor contours werden alle Konturen gespeichert
		vector<vector<Point>> contours;
		
		videoFrameBin.copyTo(copyOfVideoFrameBin);
		//Konturen finden und in contours speichern
		findContours(copyOfVideoFrameBin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		
		vector<int> areaSizes; //Vektor mit allen Areagrößen
		int maxArea = 0;
		for(int i = 0; i < contours.size(); i++){
			vector<Point> contour = contours[i];
			double area = contourArea(contour); //Könnte es hier und in Zeile 98 zu Problemen kommen wegen typecast bzw Ungenauigkeit von double?
			//Prüfen, ob Area größer als ein vorgegebener Wert, da sonst auch kleinste Reflektionen das Spiel beeinflussen können
			cout << "Area: " << area << endl;
			//if(area > 5){
				if(area > maxArea){
					maxArea = area;
				}
				areaSizes.push_back(area);//area ans Ende von areaSizes hinzufügen
			//}
		}

		//Jetzt alle Areas < maxArea aus areaSizes schwarz färben
		if(areaSizes.size() >= 2){ //gibt es mehr als eine Areagröße in areaSizes?
			for(int j = 0; j < areaSizes.size(); j++){
				if(areaSizes[j] < maxArea){
					drawContours(videoFrameBin, contours, j, Scalar(0,0,0), CV_FILLED);
				}
			}
		}

		//imshow("BinaerCopy", copyOfVideoFrameBin); 
}

void Steuerung::drawGreenCross(Mat videoFrame, Point centroid){
	//grüne Linie vertikal in Originalvideo zeichnen (mit centroid als Mittlepunkt)
	Point startPunktVert(centroid.x, centroid.y-10);
	Point endPunktVert(centroid.x, centroid.y+10);
	line(videoFrame, startPunktVert, endPunktVert, Scalar(0,255,0), 2);

	//grüne Linie horizontal in Originalvideo zeichnen
	Point startPunktHor(centroid.x-10, centroid.y);
	Point endPunktHor(centroid.x+10, centroid.y);
	line(videoFrame, startPunktHor, endPunktHor, Scalar(0,255,0), 2);
}

boolean Steuerung::process(){ 
		Mat videoFrame; //Originalvideo, in dem der Spieler zu sehen ist
		Mat videoFrameBin; //Binärmaske

		if (videoCapture.read(videoFrame) == false){ 
			return false;
		} 

		videoFrameBin = Mat(frameWidth, frameHeight, CV_8UC1);  //Binärmaske

		flip(videoFrame,videoFrame,1); //Spiegelt den Frame an der X-Achse (letzter Parameter = 1 bedeutet X-Achsenspiegelung)

		Scalar white(255,255,255);
		//Problem: Some facial areas sometimes get detected as being white, especially when moving the controller outside the trackable area
		inRange(videoFrame, white, white, videoFrameBin); //Binärmaske vom Originalvideo erzeugen, in der nur weiße Pixel als weiß dargestellt werden
		//Working with a few flaws for a cell-phone light
		
		//Jetzt Opening (reduziert die weiße Fläche) zur Behebung von Pixelfehlern
		Mat binaryMaskOpened(frameWidth, frameHeight, CV_8UC1);
		erode(videoFrameBin, binaryMaskOpened, MORPH_RECT);
		dilate(binaryMaskOpened, videoFrameBin, MORPH_RECT);

		//Durch den Median Blur werden kleinere (weiß) reflektierende Gebiete im Bild eliminiert
		medianBlur(videoFrameBin, videoFrameBin, 3);

		//Fehlerbehebung auf der Binärmaske, Nähere Erklärung siehe Methode
		eliminateFlawedAreas(videoFrameBin); 




		//Zentralen Punkt finden:
		Point centroid = centroidOfWhitePixels(videoFrameBin);
		//XPositionPrev auf aktuelle XPos setzen
		xPositionPrev = xPosition;
		xPosition = centroid.x;
		
		//Grünes Kreuz mit "centroid" als Mittelpunkt in Originalvideo zeichnen
		drawGreenCross(videoFrame, centroid);

		imshow("Originalvideo", videoFrame);
		//imshow("Binaer", videoFrameBin);

		return true;
}