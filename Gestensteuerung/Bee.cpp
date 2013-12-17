#include <opencv2/opencv.hpp>
#include "Bee.h"

using namespace cv;
using namespace std;

Bee::Bee():
	x(300),
	y(500)
{}

Bee::~Bee(){}

void Bee::init(){
	image = imread("img/bee.png", 1);
}

int Bee::getX(){
	return x;
}

int Bee::getY(){
	return y;
}

void Bee::setX(int enterX){
	x = enterX;
}

Mat Bee::insertInto(Mat viewImage){
	Mat output;
	viewImage.copyTo(output);
	Rect roi(Point(x, y), image.size()); //region of interest
	Mat destinationROI = output(roi);
	image.copyTo(destinationROI);


	//for(int i = x, n = 0; i < (image.cols-1); i++, n++){
	//	for(int j = y, m = 0; j < (image.rows-1); j++, m++){
	//		//Mat.data gives a pointer which refers to the original data matrix
	//		//cout << (m * image.step + n * image.channels() + 3) << endl;
	//		double opacity = ((double)image.data[n * image.step + m * image.channels() + 3]) / 255.;
	//		/*for(int c = 0; opacity > 0 && c < output.channels(); ++c) {
	//			unsigned char foregroundPx = image.data[fY * image.step + fX * image.channels() + c];
	//			unsigned char backgroundPx = viewImage.data[y * viewImage.step + x * viewImage.channels() + c];
	//			output.data[y*output.step + output.channels()*x + c] = backgroundPx * (1.-opacity) + foregroundPx * opacity;
	//		}*/
	//	}
	//}
	//overlayImage(viewImage, image, output, Point2i(x,y));
	return output;
}

void Bee::overlayImage(const Mat &background, const Mat &foreground, Mat &output, Point2i location){
  background.copyTo(output);

  // start at the row indicated by location, or at row 0 if location.y is negative.
  for(int y = std::max(location.y , 0); y < background.rows; ++y) {
    int fY = y - location.y; // because of the translation

    // we are done of we have processed all rows of the foreground image.
    if(fY >= foreground.rows) break;

    // start at the column indicated by location, 

    // or at column 0 if location.x is negative.
    for(int x = std::max(location.x, 0); x < background.cols; ++x) {
      int fX = x - location.x; // because of the translation.

      // we are done with this row if the column is outside of the foreground image.
      if(fX >= foreground.cols) break;

      // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
      double opacity = ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255.;

      // and now combine the background and foreground pixel, using the opacity, 

      // but only if opacity > 0.
      for(int c = 0; opacity > 0 && c < output.channels(); ++c) {
        unsigned char foregroundPx = foreground.data[fY * foreground.step + fX * foreground.channels() + c];
        unsigned char backgroundPx = background.data[y * background.step + x * background.channels() + c];
        output.data[y*output.step + output.channels()*x + c] = backgroundPx * (1.-opacity) + foregroundPx * opacity;
      }
    }
  }
}