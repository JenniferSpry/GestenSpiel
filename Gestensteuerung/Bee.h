#ifndef BEE_H
#define BEE_H
#include <opencv2/opencv.hpp>

class Bee{
	public:
		Bee();
		~Bee();
		void init();
		void setX(int entryX);
		int getX();
		int getY();
		cv::Mat insertInto(cv::Mat viewImage);
	private:
		int x;
		int y;
		cv::Mat image;
		void overlayImage(const cv::Mat &background, const cv::Mat &foreground, cv::Mat &output, cv::Point2i location);
};
#endif