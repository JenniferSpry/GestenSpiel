#ifndef STEUERUNG_H
#define STEUERUNG_H
#include <opencv2/opencv.hpp>

class Steuerung{
public:
	Steuerung();
	~Steuerung();
	bool initialize(); //"Controller-Erkennung" geschieht hier (?)
	float getXPositionChange(); //gibt �nderung der x-Position zur�ck. Positiver Wert => Verschiebung nach rechts, Negativer Wert => Verschiebung nach links
	float getXPosition(); //gibt aktuelle X-Position zur�ck. Diese Berechnet sich aus dem Mittelwert der Positionen der wei�en Pixel in der Bin�rmaske.
	boolean process(); //Ein Frame wird verarbeitet. "Main-Loop" dieser Klasse.
protected:
	cv::VideoCapture videoCapture; //Zum Capturen von der Webcam
private:
	float xPositionMax; //maximale xPosition (=Breite des Spielfelds)
	float xPositionPrev;//XPosition im letzten loop-Durchlauf
	float xPosition; //aktuelle horizontale Position des Controllers
	float xPositionChange;//horizontale Positions�nderung seit dem letzten Frame. Kann positiv oder negativ sein.
	int frameWidth;
	int frameHeight;
	void eliminateFlawedAreas(cv::Mat videoFrameBin);
	cv::Point centroidOfWhitePixels(const cv::Mat& image); //Berechnet den "Mittelpunkt" der wei�en Pixel in der Bin�rmaske und gibt seine Position zur�ck (als Point-Objekt)
	void drawGreenCross(cv::Mat videoFrame, cv::Point centroid);
};
#endif