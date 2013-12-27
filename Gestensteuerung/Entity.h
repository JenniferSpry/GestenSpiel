#ifndef Entity_H 
#define Entity_H
#include <opencv2/opencv.hpp>
#include <string>

class Entity{
	public:
		Entity(int posx, int posy, std::string name);
		virtual ~Entity();
		void setX(int entryX);
		int getX() const;
		int getY() const;
		void insertInto(cv::Mat &viewImage);
	protected:
		int x;
		int y;
		cv::Mat image;
		cv::Mat mask;
		void createMask();
};
#endif