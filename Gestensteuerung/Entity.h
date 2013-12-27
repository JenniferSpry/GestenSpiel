#ifndef Entity_H 
#define Entity_H
#include <opencv2/opencv.hpp>
#include <string>

class Entity{
	public:
		Entity(int posx, int posy, int maximumX, int maximumY, std::string name);
		Entity();
		virtual ~Entity();
		void setX(int entryX);
		void setY(int entryY);
		int getX() const;
		int getY() const;
		void insertInto(cv::Mat &viewImage);
	protected:
		int maxX;
		int maxY;
		int x;
		int y;
		cv::Mat image;
		cv::Mat mask;
		void createMask();
};
#endif