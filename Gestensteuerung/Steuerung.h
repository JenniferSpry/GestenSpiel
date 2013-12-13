#ifndef STEUERUNG_H
#define STEUERUNG_H

class Steuerung{
public:
	Steuerung();
	~Steuerung();
	void initialize(); //"Controller-Erkennung" geschieht hier (?)
	float getXPositionChange(); //gibt �nderung der x-Position zur�ck. Positiver Wert => Verschiebung nach rechts, Negativer Wert => Verschiebung nach links
	float getXPosition(); //gibt aktuelle X-Position zur�ck. Diese Berechnet sich aus dem Mittelwert der Positionen der wei�en Pixel in der Bin�rmaske.
	void convertToBinary(cv::Mat videoFrame, cv::Mat& processedFrame); //Konvertiert jedes Frame in ein Bin�rframe, wobei der "Controller" wei� ist, der Hintergrund schwarz.
	cv::Point centroidOfWhitePixels(const cv::Mat& image); //Berechnet den "Mittelpunkt" der wei�en Pixel in der Bin�rmaske und gibt seine Position zur�ck (als Point-Objekt)
	void process(); //Ein Frame wird verarbeitet. "Main-Loop" dieser Klasse.
private:
	float xPosition; //aktuelle horizontale Position des Controllers
	float xPositionChange;//horizontale Positions�nderung seit dem letzten Frame. Kann positiv oder negativ sein.
	cv::Mat controllerFrame;//von der Webcam aufgenommene Frames
	cv::Mat controllerBinFrame;//von der Webcam aufgenommene Frames als Bin�rbilder
	cv::Mat lastFrame; //das zuvor aufgenommene Frame in Graustufen. Dient zum Erstellen des Bin�rbilds.
	int frameNumber;

};
#endif