#ifndef STEUERUNG_H
#define STEUERUNG_H
#include <opencv2/opencv.hpp>

class Steuerung{
public:
	Steuerung();
	~Steuerung();
	bool initialize(); //"Controller-Erkennung" geschieht hier (?)
	float getXPositionChange(); //gibt Änderung der x-Position zurück. Positiver Wert => Verschiebung nach rechts, Negativer Wert => Verschiebung nach links
	float getXPosition(); //gibt aktuelle X-Position zurück. Diese Berechnet sich aus dem Mittelwert der Positionen der weißen Pixel in der Binärmaske.
	boolean process(); //Ein Frame wird verarbeitet. "Main-Loop" dieser Klasse.
protected:
	cv::VideoCapture videoCapture; //Zum Capturen von der Webcam
private:
	float xPositionMax; //maximale xPosition (=Breite des Spielfelds)
	float xPositionPrev;//XPosition im letzten loop-Durchlauf
	float xPosition; //aktuelle horizontale Position des Controllers
	float xPositionChange;//horizontale Positionsänderung seit dem letzten Frame. Kann positiv oder negativ sein.
	int frameWidth;
	int frameHeight;
	void eliminateFlawedAreas(cv::Mat videoFrameBin);
	cv::Point centroidOfWhitePixels(const cv::Mat& image); //Berechnet den "Mittelpunkt" der weißen Pixel in der Binärmaske und gibt seine Position zurück (als Point-Objekt)
	void drawGreenCross(cv::Mat videoFrame, cv::Point centroid);
};
#endif