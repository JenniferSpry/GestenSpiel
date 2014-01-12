#ifndef STEUERUNG_H
#define STEUERUNG_H
#include <opencv2/opencv.hpp>

class Steuerung{
public:
	Steuerung();
	~Steuerung();
	bool initialize(); //"Controller-Erkennung" geschieht hier (?)
	float getXPosition(); //gibt aktuelle X-Position zur�ck. Diese Berechnet sich aus dem Mittelwert der Positionen der wei�en Pixel in der Bin�rmaske.
	boolean process(); //Ein Frame wird verarbeitet. "Main-Loop" dieser Klasse.
protected:
	cv::VideoCapture videoCapture; //Zum Capturen von der Webcam
private:
	float xPositionMax; //maximale xPosition (= Breite des Spielfelds - Breite Biene)
	float xPositionPrev;//XPosition im letzten loop-Durchlauf
	float xPosition; //aktuelle horizontale Position des Controllers
	int frameWidth; //Breite eines von Webcam aufgenommenen Frames
	int frameHeight; //H�he eines von Webcam aufgenommenen Frames
	void eliminateFlawedAreas(cv::Mat videoFrameBin); //Pixelfehler im Bin�rbild beheben
	cv::Point centroidOfWhitePixels(const cv::Mat& image); //Berechnet den "Mittelpunkt" der wei�en Pixel in der Bin�rmaske und gibt seine Position zur�ck (als Point-Objekt)
	void drawGreenCross(cv::Mat videoFrame, cv::Point centroid); //Zeichnet gr�nes Kreuz in Spieler-Video
};
#endif