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
		void insertInto(cv::Mat &viewImage);
	private:
		int x;
		int y;
		cv::Mat image;
		cv::Mat mask;
		void createMask();
};
#endif