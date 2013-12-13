#ifndef STEUERUNG_H
#define STEUERUNG_H
#include <opencv2/opencv.hpp>

class Steuerung{
public:
	Steuerung();
	~Steuerung();
	void initialize(); //"Controller-Erkennung" geschieht hier (?)
	float getXPositionChange(); //gibt Änderung der x-Position zurück. Positiver Wert => Verschiebung nach rechts, Negativer Wert => Verschiebung nach links
	float getXPosition(); //gibt aktuelle X-Position zurück. Diese Berechnet sich aus dem Mittelwert der Positionen der weißen Pixel in der Binärmaske.
	void convertToBinary(cv::Mat videoFrame, cv::Mat& processedFrame); //Konvertiert jedes Frame in ein Binärframe, wobei der "Controller" weiß ist, der Hintergrund schwarz.
	cv::Point centroidOfWhitePixels(const cv::Mat& image); //Berechnet den "Mittelpunkt" der weißen Pixel in der Binärmaske und gibt seine Position zurück (als Point-Objekt)
	void process(); //Ein Frame wird verarbeitet. "Main-Loop" dieser Klasse.
protected:
	cv::VideoCapture videoCapture; //Zum Capturen von der Webcam
private:
	float xPosition; //aktuelle horizontale Position des Controllers
	float xPositionChange;//horizontale Positionsänderung seit dem letzten Frame. Kann positiv oder negativ sein.
	//cv::Mat controllerFrame;//von der Webcam aufgenommene Frames
	//cv::Mat controllerBinFrame;//von der Webcam aufgenommene Frames als Binärbilder
	cv::Mat previousFrame; //das zuvor aufgenommene Frame in Graustufen. Dient zum Erstellen des Binärbilds.
	int frameWidth;
	int frameHeight;
	int frameNumber;


};
#endif