#include <opencv2\opencv.hpp>
#include <string>
#include "Steuerung.h"
using namespace cv;
using namespace std;

/*public void loop(){
	//do stuff
	//comment
	//blaaaaa
}*/


int main(){
	//loop();
	Steuerung Steuerung;
	Steuerung.initialize();
	Steuerung.process();

	return 0;
}